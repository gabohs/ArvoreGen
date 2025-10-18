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
    App(const DadosApp& dApp = DadosApp());
	~App();

    void Run();
    void Stop();

private:
    bool initImgui();
    void shutdown();

    ArvoreGenealogica m_Arvore;

    std::shared_ptr<Window> m_Janela;
    std::unique_ptr<GuiLayer> m_GuiLayer;
    
    const float tamFonte = 17.f;

    bool m_Rodando = false;
};

