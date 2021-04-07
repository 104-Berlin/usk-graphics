#include "graphics_wrapper.h"

using namespace Graphics;
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

static Renderer::RRenderer3D renderer;
static GFrameBuffer* frameBuffer = nullptr;
static GVertexArray* vertexArray = nullptr;

void Init(GContext* context)
{
    renderer = Wrapper::Create3DRenderer(context);
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
}

void Render();
void RenderImGui();


int main()
{
    Wrapper::RunApplicationLoop(&Init, &Render, &RenderImGui);
}


void Render() 
{
    renderer.Begin(frameBuffer);
    renderer.Submit(vertexArray);
    renderer.End();
}

void RenderImGui()
{
    ImGui::Begin("Test Frame");
    ImVec2 contentRegion = ImGui::GetContentRegionAvail();
    frameBuffer->Resize(contentRegion.x, contentRegion.y, GFrameBufferFormat::RGBA8);
    ImGui::Image((ImTextureID)(unsigned long)frameBuffer->GetColorAttachment(), contentRegion);
    ImGui::End();
}