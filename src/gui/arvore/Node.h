#pragma once

#include "../../backend/Pessoa.h"
#include "imgui.h"

struct NodeArvore
{   
    Pessoa* m_Pessoa;
    NodeArvore(Pessoa* pessoa);

    const float largura = 100.f;
    const float altura = 100.f;    
    const float marginX = 75.f;
    const float marginY = 150.f;

    const float arredondamento = 10.f;

    ImU32 cor;
};