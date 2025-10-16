#pragma once

#include "Window/Window.h"
#include "../gui/GuiLayer.h"

#include "../backend/ArvoreGenealogica.h"

#include <memory>

struct DadosApp
{
    std::string nome = "ArvoreGen";
    DadosJanela dJanela;
};

class App
{
public:
    App(const DadosApp& specification = DadosApp());
	~App();

    void Run();
    void Stop();

private:
    bool initImgui();
    void shutdown();

    ArvoreGenealogica m_Arvore;

    std::shared_ptr<Window> m_Janela;
    std::unique_ptr<GuiLayer> m_GuiLayer;
    
    bool m_Rodando = false;
};

