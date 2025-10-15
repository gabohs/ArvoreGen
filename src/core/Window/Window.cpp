#include "Window.h"

#include <iostream>

Window::Window(const DadosJanela& dadosJ)
	: m_Dados(dadosJ)
{
}

Window::~Window()
{
	Destroy();
}

void Window::Create()
{
    if (!glfwInit())
    {
        std::cerr << "Falha ao inicializar biblioteca GLFW\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Handle = glfwCreateWindow(
        m_Dados.Width,
        m_Dados.Height,
        m_Dados.Nome.c_str(),
        nullptr,
        nullptr
    );

    if (!m_Handle)
    {
        std::cerr << "Falha ao inicializar janela\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_Handle);
    glfwSwapInterval(1); // Enable VSync
}   

void Window::Destroy()
{
    if (m_Handle)
		glfwDestroyWindow(m_Handle);

	m_Handle = nullptr;
}

void Window::Update()
{
    glfwSwapBuffers(m_Handle);
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_Handle);
}

void Window::LimpaFundo()
{
    int display_w, display_h;
    glfwGetFramebufferSize(this->GetHandle(), &display_w, &display_h);
    
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
