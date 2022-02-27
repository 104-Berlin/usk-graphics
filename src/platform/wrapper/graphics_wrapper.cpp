#include "graphics_wrapper.h"
#include "imgui_internal.h"

#ifdef G_USE_OPENGL
#include "graphics_opengl.h"
#include "backends/imgui_impl_opengl3.h"
#endif
#ifdef G_USE_GLFW
#include "graphics_glfw.h"
#include "backends/imgui_impl_glfw.h"
#endif

using namespace Graphics;

/**
 * 
 * Default 3D Shader
 * 
 */

const char* default_3d_vertex_shader = R"(
#version 330 core

layout(location = 0) in vec3 vPosition;

out vec3 currentPos;

uniform mat4 vp_matrix;

void main()
{
    gl_Position = vp_matrix * vec4(vPosition, 1.0);
    currentPos = vPosition;
}
)";

const char* default_3d_fragment_shader = R"(
#version 330 core

in vec3 currentPos;

layout(location = 0) out vec4 fColor;

void main()
{
    if (int(currentPos.x / 10) % 10 == 0 || int(currentPos.z / 10) % 10 == 0)
    {
        fColor = vec4(1, 0.5, 1, 1);
    }
    else 
    {
        fColor = vec4(0, 0.5, 0, 1);
    }
}
)";

static GShader* default_3d_shader = nullptr;


static ImGuiContext* imguiContext = nullptr;
static GContext* mainContext = nullptr;

void SetCustomColorStyle()
{
    ImGuiStyle* style = &ImGui::GetStyle();
    style->WindowRounding = 0;
    style->WindowBorderSize = 0;
    style->FrameRounding = 0;
    style->FrameBorderSize = 0;
    style->FramePadding = {4.0f, 4.0f};
    style->TabBorderSize = 0;
    style->TabRounding = 0;
    style->TabMinWidthForCloseButton = FLT_MAX;
    style->WindowMenuButtonPosition = ImGuiDir_Right;

    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled]           = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
	colors[ImGuiCol_ChildBg]                = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_WindowBg]               = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_PopupBg]                = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_Border]                 = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
	colors[ImGuiCol_BorderShadow]           = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_FrameBg]                = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
	colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
	colors[ImGuiCol_FrameBgActive]          = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
	colors[ImGuiCol_TitleBg]                = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
	colors[ImGuiCol_TitleBgActive]          = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
	colors[ImGuiCol_MenuBarBg]              = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
	colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
	colors[ImGuiCol_CheckMark]              = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
	colors[ImGuiCol_SliderGrab]             = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
	colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
	colors[ImGuiCol_Button]                 = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
	colors[ImGuiCol_ButtonHovered]          = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
	colors[ImGuiCol_ButtonActive]           = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
	colors[ImGuiCol_Header]                 = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	colors[ImGuiCol_HeaderHovered]          = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
	colors[ImGuiCol_HeaderActive]           = ImVec4(0.76f, 0.76f, 0.76f, 0.77f);
	colors[ImGuiCol_Separator]              = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
	colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
	colors[ImGuiCol_SeparatorActive]        = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
	colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
	colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.25f, 0.25f, 0.25f, 0.9f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 0.9f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.43f, 0.43f, 0.43f, 0.9f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.11f, 0.11f, 0.11f, 0.6f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.34f, 0.34f, 0.34f, 0.6f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.45f, 0.45f, 0.45f, 0.6f);        // Preview overlay color when about to docking something
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.15f, 0.15f, 0.15f, 0.7f);
}

ImGuiContext* Wrapper::GetCurrentImGuiContext()
{
    return imguiContext;
}

GContext* Wrapper::GetMainContext() 
{
    return mainContext;
}

void Wrapper::RunApplicationLoop(std::function<void(GContext* context)> OnInit, std::function<void()> RenderCallback, std::function<void()> RenderImGui, std::function<void()> CleanUp, void(*SetImGuiContext)(ImGuiContext*))
{
    GWindow* window = nullptr;
    mainContext = nullptr;
#ifdef G_USE_GLFW
    window = new GLFW::GLFWWindow();
#endif
#ifdef G_USE_OPENGL
    mainContext = new GL::GLContext();
#endif    
    if (!window)
    {
        printf("Could not create window. Please select window API");
        return;
    }
    if (!mainContext)
    {
        printf("Could not create context. Please select rendering API");
        return;
    }

    window->Create("My Test window", 1270, 720);
    window->CreateContext(mainContext);


    default_3d_shader = CreateShader();
    default_3d_shader->Compile(default_3d_vertex_shader, default_3d_fragment_shader);

    

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    imguiContext = ImGui::GetCurrentContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigWindowsMoveFromTitleBarOnly = true;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    //ImGui::StyleColorsLight();
    SetCustomColorStyle();

    // Setup Platform/Renderer backends
#ifdef G_USE_GLFW 
#ifdef G_USE_OPENGL
    ImGui_ImplGlfw_InitForOpenGL(((GLFW::GLFWWindow*)window)->GetGlfwWindow(), true);
    ImGui_ImplOpenGL3_Init();
#endif
#endif


    if (SetImGuiContext)
    {
        SetImGuiContext(imguiContext);
    }
    if (OnInit)
    {
        OnInit(mainContext);
    }

#ifdef G_USE_OPENGL
    ImGui_ImplOpenGL3_CreateFontsTexture(); // Need this to work with my renderer
#endif

    while (window->IsOpen())
    {
        window->PollEvents();

        if (RenderCallback)
        {
            RenderCallback();
        }
        
#ifdef G_USE_GLFW 
        ImGui_ImplGlfw_NewFrame();
#endif

        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
        
        static bool p_open;

        static bool opt_fullscreen_persistant = true;
        static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
        bool opt_fullscreen = opt_fullscreen_persistant;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y - 32));
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }


        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &p_open, window_flags);
        ImGui::PopStyleVar();


        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Dockspace		         
        ImGuiIO& io = ImGui::GetIO();		        
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {		
            ImGuiID dockspace_id = ImGui::GetID("MyDockspace");		
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);		
        }

        if (RenderImGui)
        {
            RenderImGui();
        }
        ImGui::End();

        ImGui::Render(); // Needs to go after

#ifdef G_USE_GLFW 
#ifdef G_USE_OPENGL
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        
        int display_w;
        int display_h;
        glfwGetFramebufferSize(((GLFW::GLFWWindow*)window)->GetGlfwWindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

#endif
#endif
        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        // Swap the renderer
        window->SwapBuffer();
    }     

#ifdef G_USE_OPENGL
    ImGui_ImplOpenGL3_Shutdown();
#endif  
#ifdef G_USE_GLFW
    ImGui_ImplGlfw_Shutdown();
#endif
    ImGui::DestroyContext();   

    if (CleanUp)
    {
        CleanUp();
    }

    delete default_3d_shader;
    delete mainContext;
    Renderer::RRenderCommandQueue::Get().Execute();

    window->Destroy();
    delete window;
}

GVertexArray* Wrapper::CreateVertexArray() 
{
#ifdef G_USE_OPENGL
return new GL::GLVertexArray();
#else
return nullptr;
#endif
}

GVertexBuffer* Wrapper::CreateVertexBuffer() 
{
#ifdef G_USE_OPENGL
return new GL::GLVertexBuffer();
#else
return nullptr;
#endif
}

GIndexBuffer* Wrapper::CreateIndexBuffer() 
{
#ifdef G_USE_OPENGL
return new GL::GLIndexBuffer();
#else
return nullptr;
#endif
}

GFrameBuffer* Wrapper::CreateFrameBuffer(unsigned int width, unsigned int height, GFrameBufferFormat format) 
{
#ifdef G_USE_OPENGL
return new GL::GLFrameBuffer(width, height, format);
#else
return nullptr;
#endif
}

G_API GShader* Wrapper::CreateShader() 
{
#ifdef G_USE_OPENGL
return new GL::GLShader();
#else
return nullptr;
#endif
}

G_API GTexture2D* Wrapper::CreateTexture() 
{
#ifdef G_USE_OPENGL
return new GL::GLTexture2D();
#else
return nullptr;
#endif
}

G_API GShader* Wrapper::GetDefault3DShader() 
{
    return default_3d_shader;    
}