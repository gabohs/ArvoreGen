#include "App.h"

#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


#include "../gui/theme/font.h"

#include "../gui/janelas/JanelaControles.h"
#include "../gui/janelas/JanelaVisualiza.h"


App::App(const DadosApp& dApp)
{
    m_Janela = std::make_shared<Window>(dApp.dJanela);
    m_Janela->Create();

    if (!initImgui())
    {
        std::cerr << "Erro ao inicializar biblioteca ImGui.\n";
        return;
    }

    m_GuiLayer = std::make_unique<GuiLayer>();
    m_GuiLayer->AddJanela( std::make_shared<JControles>(m_Arvore) );
    m_GuiLayer->AddJanela( std::make_shared<JVisualizacao>(m_Arvore) );

    std::cout << dApp.nome << " iniciado com sucesso!\n";
}

App::~App()
{
    shutdown();
}

bool App::initImgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImFontConfig font_cfg;
    font_cfg.FontDataOwnedByAtlas = false;

    io.Fonts->AddFontFromMemoryTTF(JetBrainsMonoNL, FontSize, tamFonte, &font_cfg);
    
    if (!ImGui_ImplGlfw_InitForOpenGL(m_Janela->GetHandle(), true))
    {
        std::cerr << "[ImGui] Falha ao inciar backends GLFW.\n";
        return false;
    }

    if (!ImGui_ImplOpenGL3_Init("#version 330"))
    {
        std::cerr << "[ImGui] Falha ao inciar backends OPENGL.\n";
        return false;
    }

    std::cout << "[ImGui] Inicaido com sucesso!.\n";
    return true;
}

void App::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (m_Janela)
        m_Janela->Destroy();

    glfwTerminate();
}
