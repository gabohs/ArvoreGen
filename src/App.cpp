#include "App.h"

#include "GUI/Theme/Font/JETBRAINSMONONL-BOLD.h"

App::App() : window_(nullptr) 
{ 
}

App::~App() 
{
    shutdown();
}

bool App::init() 
{
    if (!initializeGLFW()) 
    {
        return false;
    }
    if (!initializeImGui()) 
    {
        return false;
    }
    return true;
}

bool App::initializeGLFW() 
{
    if (!glfwInit()) 
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    window_ = glfwCreateWindow(mode->width, mode->height, "ArvoreGen", nullptr, nullptr);

    if (!window_) 
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1); // Enable vsync
    return true;
}

bool App::initializeImGui() 
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    ImGui::StyleColorsDark();

    ImFontConfig font_cfg;
    font_cfg.FontDataOwnedByAtlas = false;

    io.Fonts->AddFontFromMemoryTTF(JetBrainsMonoNL, FontSize, 22.0f, &font_cfg);


    if (!ImGui_ImplGlfw_InitForOpenGL(window_, true)) 
    {
        std::cerr << "Failed to initialize ImGui GLFW backend" << std::endl;
        return false;
    }
    if (!ImGui_ImplOpenGL3_Init("#version 330")) 
    {
        std::cerr << "Failed to initialize ImGui OpenGL3 backend" << std::endl;
        return false;   
    }
    return true;
}

void App::setup()
{
    setStyle::Dark();
}

void App::run() 
{   
    setup();

    while (!glfwWindowShouldClose(window_)) 
    {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window_, GLFW_ICONIFIED) && glfwGetWindowAttrib(window_, GLFW_FOCUSED))
            glfwRestoreWindow(window_);

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Renderiza os painéis
        if (gui.shouldRender())  
            gui.render(); 
        else
            glfwSetWindowShouldClose(window_, true);

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window_, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window_);
    }
}

void App::shutdown() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (window_) 
    {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
    glfwTerminate();
}