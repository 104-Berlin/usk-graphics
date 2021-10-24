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

static GContext* globContext = nullptr;
static Renderer::RRenderer3D* renderer = nullptr;
static GFrameBuffer* frameBuffer = nullptr;
static RMesh* mesh = new RMesh();
static RCamera camera(ECameraMode::ORTHOGRAPHIC);
static RScene* scene = new RScene();

void Init(GContext* context)
{
    globContext = context;
    frameBuffer = Wrapper::CreateFrameBuffer(1270, 720, Graphics::GFrameBufferFormat::RGBA16F);
    renderer = new RRenderer3D(context, frameBuffer);

    mesh->SetData(vertices, indices);
    
    scene->Add(mesh);
}

void CleanUp()
{
    delete frameBuffer;
    delete mesh;
    delete scene;
    delete renderer;
}

void Render();
void RenderImGui();


void xmain(int argc, const char** argv)
{
    Wrapper::RunApplicationLoop(&Init, &Render, &RenderImGui, &CleanUp, &Wrapper::SetImGuiContext);
}


void Render() 
{
    globContext->Clear(1.0f, 0.0f, 0.0f, GCLEAROPTION_COLOR_BUFFER | GCLEAROPTION_DEPTH_BUFFER);

    //renderer->Render(scene, &camera);
}

void RenderImGui()
{
    ImGui::Begin("Test Frame");
    ImVec2 contentRegion = ImGui::GetContentRegionAvail();
    frameBuffer->Resize(contentRegion.x, contentRegion.y, GFrameBufferFormat::RGBA8);
    ImGui::Image((ImTextureID)(unsigned long long)(unsigned long)frameBuffer->GetColorAttachment(), contentRegion);
    ImGui::End();
}