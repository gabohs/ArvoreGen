#pragma once

#include "../GuiLayer.h"
#include "../../backend/ArvoreGenealogica.h"
#include "../../backend/Pessoa.h"

#include <string>

class JControles : public IJanela
{
public:
    JControles(ArvoreGenealogica& arvore);

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
    void secaoAdicionaPessoa();
    void secaoDefineRelacao();

    void secaoBusca();
    void abrePainelInfoPessoa(const Pessoa* pessoa);

    void popupsErro();
    void secaoDebug();

    void AddPessoaGui(Pessoa* pessoa);

    void secaoExporta();

private:
    std::string m_Nome = "Controles";
    bool m_JanelaAberta = true;

    bool m_PainelInfoPessoaAberto = false; // provavelmente n eh a solucao mais elegante pra controlar a janela de infoBusca, mas funciona

    ArvoreGenealogica& m_Arvore;

    
};