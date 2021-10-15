#include "graphics_renderer.h"


const char* default_3d_vertex_shader = R"(
#version 330 core

layout(location = 0) in vec3 vPosition;

out vec3 currentPos;

uniform mat4 vp_matrix;
uniform mat4 ml_matrix;

void main()
{
    gl_Position = vp_matrix * ml_matrix * vec4(vPosition, 1.0);
    currentPos = vPosition;
}
)";

const char* default_3d_fragment_shader = R"(
#version 330 core

in vec3 currentPos;

layout(location = 0) out vec4 fColor;

void main()
{
    fColor = vec4(1.0, 1.0, 1.0, 1);
}
)";


using namespace Renderer;


RRenderer3D::RRenderer3D(Graphics::GContext* context, Graphics::GFrameBuffer* frameBuffer) 
    : RRendererBase(context), fFrameBuffer(frameBuffer), fViewProjectionMatrix(), fDefaultShader(Graphics::Wrapper::CreateShader())
{
    assert(context);
    assert(frameBuffer);

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

    fFrameBuffer->Bind();
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
