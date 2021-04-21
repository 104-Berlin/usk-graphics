#include "graphics_wrapper.h"
#include "graphics_renderer.h"

using namespace Graphics;
using namespace Renderer;



const std::vector<RMesh::Vertex> vertices = {
    {{-0.5f, 0.5f, 0.0f}},
    {{ 0.5f, 0.5f, 0.0f}},
    {{ 0.0f, -0.5f, 0.0f}},
};

const std::vector<unsigned int> indices = {
    0, 1, 2
};

static Renderer::RRenderer3D renderer;
static GFrameBuffer* frameBuffer = nullptr;
static RMesh* mesh = new RMesh();
static RCamera camera(ECameraMode::ORTHOGRAPHIC);

void Init(GContext* context)
{
    renderer = RRenderer3D(context);
    frameBuffer = Wrapper::CreateFrameBuffer(1270, 720, Graphics::GFrameBufferFormat::RGBA16F);

    mesh->SetData(vertices, indices);
}

void CleanUp()
{
    delete frameBuffer;
    delete mesh;
}

void Render();
void RenderImGui();


int main()
{
    Wrapper::RunApplicationLoop(&Init, &Render, &RenderImGui, &CleanUp, &Wrapper::SetImGuiContext);
}


void Render() 
{
    renderer.Begin(frameBuffer, &camera);
    renderer.Submit(mesh);
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