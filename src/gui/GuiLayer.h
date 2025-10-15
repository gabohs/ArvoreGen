#pragma once

#include <imgui.h>

#include <memory>
#include <vector>
#include <string>

class IJanela
{
public:
    virtual ~IJanela() = default;

    virtual void Renderiza() = 0;

    virtual const std::string& GetNome() const = 0;

    virtual bool IsOpen() const = 0;
    virtual void SetOpen(bool open) = 0;
};

class GuiLayer
{
public:
    GuiLayer();
    ~GuiLayer() = default;

    void Begin();
    void End();

    void Render();

    void RenderizaJanelas();

    void AddJanela(std::shared_ptr<IJanela> janela);

private:
    void setupDockspace();

    std::vector<std::shared_ptr<IJanela>> m_Janelas;
};