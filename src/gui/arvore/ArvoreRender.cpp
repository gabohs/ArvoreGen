#include "ArvoreRender.h"

#include "Node.h"
#include "../theme/colors.h"

#include <iostream>

ArvoreRender::ArvoreRender(ArvoreGenealogica &arvore)
    : m_Arvore(arvore)
{
}

void ArvoreRender::desenhaArvore()
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos(); // posicao do cursor relativa à tela
    ImVec2 cursorPos = ImGui::GetCursorPos(); // posicao do cursor relativa à janela atual
    
    ImVec2 pos (
        cursorScreenPos.x + cursorPos.x, 
        cursorScreenPos.y + cursorPos.y
    );

    const uint8_t qpc = 8; // quadrados por coluna

    int i = 0;
    for (Pessoa* pessoa : m_Arvore.getPessoas())
    {   
        NodeArvore node(pessoa);

        ImVec2 verticeInicial(
            pos.x + (i % qpc) * (node.largura + node.marginX),
            pos.y + (i / qpc) * (node.altura + node.marginY) 
        );

        ImVec2 verticeFinal(
            verticeInicial.x + node.largura,
            verticeInicial.y + node.altura
        );

        drawList->AddRectFilled(
            verticeInicial,
            verticeFinal,
            ImGui::ColorConvertFloat4ToU32(Colors::Aqua),
            node.arredondamento
        );

        std::string nome = pessoa->getInfo().nome;
        float tamanhoNomeX = ImGui::CalcTextSize(nome.c_str()).x;

        // evita que a string do nome seja maior que o node
        const int larguraMax = node.largura - 10;
        
        if (tamanhoNomeX > larguraMax)
        {
            while (!nome.empty() && ImGui::CalcTextSize((nome + "...").c_str()).x > larguraMax)
            {
                nome.pop_back();
            }
            nome += "...";
        }
        
        drawList->AddText(
            ImVec2( verticeInicial.x + ( (node.largura - ImGui::CalcTextSize(nome.c_str()).x) / 2), verticeInicial.y + 15 ), 
            ImGui::ColorConvertFloat4ToU32(Colors::DarkGray),
            nome.c_str()
        );

        std::string genero = "G: " + pessoa->getInfo().genero;
        drawList->AddText(
            ImVec2( verticeInicial.x + ((node.largura - ImGui::CalcTextSize(genero.c_str()).x) / 2), verticeInicial.y + 40 ),
            ImGui::ColorConvertFloat4ToU32(Colors::DarkYellow),
            genero.c_str()
        );

        std::string nascimento = "Nasc: " + std::to_string(pessoa->getInfo().anoNascimento);
        drawList->AddText(
            ImVec2( verticeInicial.x + ((node.largura - ImGui::CalcTextSize(nascimento.c_str()).x) / 2), verticeFinal.y - 30 ),
            ImGui::ColorConvertFloat4ToU32(Colors::Yellow),
            nascimento.c_str()
        );
        
        i++;
    }

    if (!m_Arvore.getPessoas().empty())
    {
        NodeArvore node(nullptr); // so para acessar as propriedades de dimensao do node
        float alturaTotalCanvas = ((m_Arvore.getPessoas().size() / qpc) + 1) * (node.altura + node.marginY);
        ImGui::Dummy(ImVec2(qpc * (node.largura + node.marginX), alturaTotalCanvas));
    }    
}