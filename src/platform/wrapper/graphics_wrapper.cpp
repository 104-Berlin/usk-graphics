#include "graphics_wrapper.h"


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

void main()
{
    gl_Position = vec4(vPosition, 1.0);
}
)";

const char* default_3d_fragment_shader = R"(
#version 330 core

layout(location = 0) out vec4 fColor;

void main()
{
    fColor = vec4(1, 0, 0, 1);
}
)";

static GShader* default_3d_shader = nullptr;


static ImGuiContext* imguiContext = nullptr;

void Wrapper::ResetImGuiContext()
{
    SetImGuiContext(imguiContext);
}

void Wrapper::RunApplicationLoop(void(*OnInit)(GContext* context), void(*RenderCallback)(), void(*RenderImGui)(), void(*CleanUp)(), void(*SetImGuiContext)(ImGuiContext*))
{
    GWindow* window = nullptr;
    GContext* context = nullptr;
#ifdef G_USE_GLFW
    window = new GLFW::GLFWWindow();
#endif
#ifdef G_USE_OPENGL
    context = new GL::GLContext();
#endif    
    if (!window)
    {
        printf("Could not create window. Please select window API");
        return;
    }
    if (!context)
    {
        printf("Could not create context. Please select rendering API");
        return;
    }

    window->Create("My Test window", 1270, 720);
    window->CreateContext(context);


    default_3d_shader = CreateShader();
    default_3d_shader->Compile(default_3d_vertex_shader, default_3d_fragment_shader);

    

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    imguiContext = ImGui::GetCurrentContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
#ifdef G_USE_GLFW 
#ifdef G_USE_OPENGL
    ImGui_ImplGlfw_InitForOpenGL(((GLFW::GLFWWindow*)window)->GetGlfwWindow(), true);
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplOpenGL3_CreateFontsTexture(); // Need this to work with my renderer
#endif
#endif

    if (SetImGuiContext)
    {
        SetImGuiContext(imguiContext);
    }
    if (OnInit)
    {
        OnInit(context);
    }

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

        static bool p_open;

        static bool opt_fullscreen_persistant = true;
        static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
        bool opt_fullscreen = opt_fullscreen_persistant;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->Pos);
            ImGui::SetNextWindowSize(viewport->Size);
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

        ImGui::Render();

#ifdef G_USE_GLFW 
#ifdef G_USE_OPENGL
        G_RENDERCMD1(window, {
            ImGuiIO& io = ImGui::GetIO();
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            
            int display_w;
            int display_h;
            glfwGetFramebufferSize(((GLFW::GLFWWindow*)window)->GetGlfwWindow(), &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
        })
#endif
#endif


        // Swap the renderer
        Renderer::RRenderCommandQueue::Get().Execute();
        window->SwapBuffer();
    }     

#ifdef G_USE_GLFW
    ImGui_ImplGlfw_Shutdown();
#endif
#ifdef G_USE_OPENGL
    ImGui_ImplOpenGL3_Shutdown();
#endif  
    ImGui::DestroyContext();   

    if (CleanUp)
    {
        CleanUp();
    }

    delete default_3d_shader;
    delete context;
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


G_API GShader* Wrapper::GetDefault3DShader() 
{
    return default_3d_shader;    
}
