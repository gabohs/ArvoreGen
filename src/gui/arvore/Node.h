#pragma once

#include "../../backend/Pessoa.h"
#include "imgui.h"

struct NodeAttr // atributos do node
{
    const float largura = 100.f;
    const float altura = 100.f;    
    const float marginX = 200.f;
    const float marginY = 150.f;

    const float arredondamento = 10.f;
};

class NodeArvore
{   
public:
    NodeArvore(Pessoa* pessoa);

    void desenha(ImDrawList* drawList, ImVec2 verticeInicial, ImVec2 verticeFinal); 
    // - [gabriel]: resolvi passar o drawList como parametro, mas poderia ter sido inicializado na classe
    // [update] inclusive acho que isso seja até melhor, mas agora n da tempo de mudar

    const Pessoa* getPessoa() const
    {
        return m_Pessoa;
    }

    const NodeAttr getAttr() const
    {
        return m_Attr;
    }

private:
    Pessoa* m_Pessoa;
    
    NodeAttr m_Attr;

    ImU32 cor;
};