#include "App.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void App::Run()
{
    m_Rodando = true;

    while(m_Rodando)
    {
        glfwPollEvents();

        if (m_Janela->ShouldClose())
		{
			Stop();
			break;
		}

        m_Janela->LimpaFundo();

        m_GuiLayer->Begin();
        m_GuiLayer->RenderizaJanelas();
        m_GuiLayer->End();

        m_GuiLayer->Render();
        m_Janela->Update();
    }
}

void App::Stop()
{
    m_Rodando = false;
}
