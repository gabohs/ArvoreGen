#pragma once

#include <GLFW/glfw3.h>
#include <string>

struct DadosJanela
{
    std::string Nome;
    uint32_t Width = 1920;
	uint32_t Height = 1080;
};


class Window
{
public:
    Window(const DadosJanela& specification = DadosJanela());
	~Window();

    void Create();
	void Destroy();

	void Update();

    bool ShouldClose() const;

    void LimpaFundo();

    GLFWwindow* GetHandle() const { return m_Handle; }

private:
    DadosJanela m_Dados;

	GLFWwindow* m_Handle = nullptr;
};