#pragma once

#include "../GuiLayer.h"

#include "../../backend/ArvoreGenealogica.h"
#include "../arvore/ArvoreRender.h"

class JVisualizacao : public IJanela
{
public:
    JVisualizacao(ArvoreGenealogica& arvore);

    const std::string& GetNome() const override
    {
        return m_Nome;
    }

    bool IsOpen() const override
    { 
        return m_JanelaAberta; 
    }
    void SetOpen(bool open) override
    { 
        m_JanelaAberta = open; 
    }

    void Renderiza() override;

private:
    std::string m_Nome = "Visualização";
    bool m_JanelaAberta = true;

    ArvoreRender m_aRender;
};