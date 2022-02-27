#include "graphics_renderer.h"


const char* default_3d_vertex_shader = R"(
#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

out vec3 currentPos;
out vec3 currentNormal;

uniform mat4 vp_matrix;
uniform mat4 ml_matrix;

void main()
{
    mat3 normal_mat = mat3(ml_matrix);
    currentNormal = normal_mat * vNormal;

    gl_Position = vp_matrix * ml_matrix * vec4(vPosition, 1.0);
    currentPos = vPosition;
}
)";

const char* default_3d_fragment_shader = R"(
#version 330 core

in vec3 currentPos;
in vec3 currentNormal;

layout (location = 0) out vec4 fColor;
layout (location = 1) out vec3 fNormal;

const vec3 light_direction = vec3(0.0, 0.0, -1.0);

void main()
{
    float diffuse = max(dot(normalize(currentNormal), normalize(light_direction)), 0.2);
    fColor = vec4((vec3(1.0, 1.0, 1.0) * diffuse), 1);
    fNormal = (normalize(currentNormal) + vec3(1.0, 1.0, 1.0)) / 2.0;
}
)";


using namespace Renderer;


RRenderer3D::RRenderer3D(Graphics::GContext* context, Graphics::GFrameBuffer* frameBuffer) 
    : RRendererBase(context), fFrameBuffer(frameBuffer), fViewProjectionMatrix(), fDefaultShader(Graphics::Wrapper::CreateShader())
{
    assert(context);
    assert(fFrameBuffer);

    fDefaultShader->Compile(default_3d_vertex_shader, default_3d_fragment_shader);
}

RRenderer3D::~RRenderer3D() 
{
    if (fDefaultShader)
    {
        delete fDefaultShader;
    }
}

void RRenderer3D::Render(RScene* scene, RCamera* camera) 
{
    assert(fContext);
    assert(fFrameBuffer);

    if (!scene || !camera)  
    {
        printf("ERROR: Renderer3D::Renderer called with NULL argument. Can't proceed!\n");
        return;
    }

    fContext->SetFaceCullingMode(Graphics::GCullMode::BACK);
    fFrameBuffer->Bind();
    fContext->EnableDepthTest(true);
    fContext->Clear();
    fDefaultShader->Bind();
    glm::mat4 viewProjection = camera->GetProjectionMatrix(fFrameBuffer->GetWidth(), fFrameBuffer->GetHeight()) * camera->GetViewMatrix();   
    fDefaultShader->SetUniformMat4("vp_matrix", viewProjection);


    scene->Traverse([this](RObject* object){
        fDefaultShader->SetUniformMat4("ml_matrix", object->GetModelMatrix());
        object->Render(fContext);
    });

    fDefaultShader->Unbind();
    fFrameBuffer->Unbind();
}
