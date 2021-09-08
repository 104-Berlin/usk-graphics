#include "graphics_wrapper.h"
#include "graphics_renderer.h"

using namespace Graphics;
using namespace Renderer;



const std::vector<GMesh::Vertex> vertices = {
    {{-0.5f, 0.5f, 0.0f}},
    {{ 0.5f, 0.5f, 0.0f}},
    {{ 0.0f, -0.5f, 0.0f}},
};

const std::vector<unsigned int> indices = {
    0, 1, 2
};

static Renderer::RRenderer3D* renderer = nullptr;
static GFrameBuffer* frameBuffer = nullptr;
static GMesh* mesh = new GMesh();
static RCamera camera(ECameraMode::ORTHOGRAPHIC);
static GScene* scene = new GScene();

void Init(GContext* context)
{
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


int main()
{
    Wrapper::RunApplicationLoop(&Init, &Render, &RenderImGui, &CleanUp, &Wrapper::SetImGuiContext);
}


void Render() 
{
    renderer->Render(scene, &camera);
}

void RenderImGui()
{
    ImGui::Begin("Test Frame");
    ImVec2 contentRegion = ImGui::GetContentRegionAvail();
    frameBuffer->Resize(contentRegion.x, contentRegion.y, GFrameBufferFormat::RGBA8);
    ImGui::Image((ImTextureID)(unsigned long long)(unsigned long)frameBuffer->GetColorAttachment(), contentRegion);
    ImGui::End();
}