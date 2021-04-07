#include "graphics_wrapper.h"

using namespace Graphics;

const char* vertexSource = R"(
#version 330 core

layout(location = 0) in vec3 vPosition;

void main()
{
    gl_Position = vec4(vPosition, 1.0);
}
)";

const char* fragmentSource = R"(
#version 330 core

layout(location = 0) out vec4 fColor;

void main()
{
    fColor = vec4(1, 0, 0, 1);
}
)";

struct Vertex
{
    glm::vec3 position;
};


const std::vector<Vertex> vertices = {
    {{-0.5f, 0.5f, 0.0f}},
    {{ 0.5f, 0.5f, 0.0f}},
    {{ 0.0f, -0.5f, 0.0f}},
};

const std::vector<unsigned int> indices = {
    0, 1, 2
};

static Renderer::RRenderer3D* renderer = nullptr;
static GFrameBuffer* frameBuffer = nullptr;
static GVertexArray* vertexArray = nullptr;
static GShader* shader=nullptr;

void Init(GContext* context)
{
    renderer = new Renderer::RRenderer3D(context);
    frameBuffer = Wrapper::CreateFrameBuffer(1270, 720, Graphics::GFrameBufferFormat::RGBA16F);

    vertexArray = Wrapper::CreateVertexArray();
    vertexArray->Bind();

    GVertexBuffer* vb = Wrapper::CreateVertexBuffer();
    vb->SetData((unsigned char*) vertices.data(), vertices.size() * sizeof(Vertex));
    vb->SetLayout({Graphics::GBufferElement(Graphics::GShaderDataType::Float3, "POSITION")});

    GIndexBuffer* ib = Wrapper::CreateIndexBuffer();
    ib->SetData((unsigned char*)indices.data(), indices.size() * sizeof(unsigned int), sizeof(unsigned int));
    
    vertexArray->AddVertexBuffer(vb);
    vertexArray->SetIndexBuffer(ib);
    

    shader = Wrapper::CreateShader();
    shader->Compile(vertexSource, fragmentSource);
}

void Render();
void RenderImGui();


int main()
{
    Wrapper::RunApplicationLoop(&Init, &Render, &RenderImGui);
}


void Render() 
{
    renderer->Begin(frameBuffer);
    renderer->Submit(vertexArray, shader);
    renderer->End();
}

void RenderImGui()
{
    ImGui::Begin("Test Frame");
    ImVec2 contentRegion = ImGui::GetContentRegionAvail();
    frameBuffer->Resize(contentRegion.x, contentRegion.y, GFrameBufferFormat::RGBA8);
    ImGui::Image((ImTextureID)(unsigned long)frameBuffer->GetColorAttachment(), contentRegion);
    ImGui::End();
}