#include "ArvoreRender.h"


#include "../theme/colors.h"

#include "../utils/mouse.h"

#include <iostream>

ArvoreRender::ArvoreRender(ArvoreGenealogica &arvore)
    : m_Arvore(arvore)
{
}

void ArvoreRender::desenhaArvoreAPartirDeAncestral(const std::string& nomeAncestral, const ImVec2& origem)
{
    Pessoa* ancestral = m_Arvore.buscaPessoa(nomeAncestral); 
    
    if (!ancestral)
        return;

    ImDrawList* drawList = ImGui::GetWindowDrawList();

    float startX = origem.x; 
    float startY = origem.y;   

    desenhaDescendentes(drawList, ancestral, startX, startY, 0);
}

void ArvoreRender::desenhaArvoreAscendentesEDescendentes(const std::string &nomePessoa, const ImVec2& origem)
{
    Pessoa* pInicial = m_Arvore.buscaPessoa(nomePessoa);

    if (!pInicial)
        return;

    ImDrawList* drawList = ImGui::GetWindowDrawList(); 

    NodeArvore nodeInicial(pInicial);
    const NodeAttr& attr = nodeInicial.getAttr();

    ImVec2 vi(origem.x - attr.largura / 2, origem.y);
    ImVec2 vf(origem.x + attr.largura / 2, origem.y + attr.altura);

    nodeInicial.desenha(drawList, vi, vf);
    infoNode(vi, vf, pInicial->getInfo().nome);

    // desenhar ascendentes em baixo
    const auto& filhos = pInicial->getFilhos();
    if (!filhos.empty())
    {
        float larguraTotal = (filhos.size() - 1) * attr.marginX;
        float startX = origem.x - larguraTotal / 2;
        float nextY = origem.y + attr.altura + attr.marginY;

        for (size_t i = 0; i < filhos.size(); ++i)
        {
            float childX = startX + i * attr.marginX;
            
            drawList->AddLine(
                ImVec2(origem.x, origem.y + attr.altura),
                ImVec2(childX, nextY),
                ImGui::ColorConvertFloat4ToU32(Colors::Gray),
                2.0f
            );

            desenhaDescendentes(drawList, filhos[i], childX, nextY, 1);
        }
    }

    // ascendentes
    Pessoa* mae = pInicial->getMae();
    Pessoa* pai = pInicial->getPai();

    if (mae || pai)
    {
        int ascendentesRegistrados = 0;
        if (mae) ascendentesRegistrados++;
        if (pai) ascendentesRegistrados++;

        float larguraTotal = (ascendentesRegistrados - 1) * attr.marginX;
        float startX = origem.x - larguraTotal / 2.f;
        float nextY = origem.y - attr.altura - attr.marginY;

        int idx = 0;

        if (mae)
        {
            float parentX = startX + idx * attr.marginX;

            drawList->AddLine(
                ImVec2(origem.x, origem.y),
                ImVec2(parentX, nextY + attr.altura),
                ImGui::ColorConvertFloat4ToU32(Colors::Gray),
                2.0f
            );

            desenhaAscendentes(drawList, mae, parentX, nextY, 1);
            idx++;
        }

        if (pai)
        {
            float parentX = startX + idx * attr.marginX;

            drawList->AddLine(
                ImVec2(origem.x, origem.y),
                ImVec2(parentX, nextY + attr.altura),
                ImGui::ColorConvertFloat4ToU32(Colors::Gray),
                2.0f
            );

            desenhaAscendentes(drawList, pai, parentX, nextY, 1);
        }
    }

    
}

void ArvoreRender::desenhaAscendentes(ImDrawList* drawList, Pessoa* pessoa, float x, float y, int depth)
{
    NodeArvore node(pessoa);
    const NodeAttr& attr = node.getAttr();

    ImVec2 vi(x - attr.largura / 2, y);             
    ImVec2 vf(x + attr.largura / 2, y + attr.altura); 
    
    node.desenha(drawList, vi, vf);
    infoNode(vi, vf, pessoa->getInfo().nome);

    Pessoa* mae = pessoa->getMae();
    Pessoa* pai = pessoa->getPai();

    if (!mae && !pai)
        return;

    int ascendentesRegistrados = 0;

    if (mae) ascendentesRegistrados++;
    if (pai) ascendentesRegistrados++;

    int larguraTotal = (ascendentesRegistrados - 1) * attr.marginX;

    float startX = x - larguraTotal / 2.f;
    float nextY = y - attr.altura - attr.marginY;

    int idx = 0;

    if (mae)
    {
        float parentX = startX + idx * attr.marginX;
        float parentY = nextY;

        // desenha linha de conexao
        drawList->AddLine(
            ImVec2(x, y),                              // topo do nó atual
            ImVec2(parentX, nextY + attr.altura),      // base da mãe (nextY + altura = fundo do retângulo da mãe)
            ImGui::ColorConvertFloat4ToU32(Colors::Gray),
            2.0f
        );

        desenhaAscendentes(drawList, mae, parentX, nextY, depth + 1);
        idx++;
    }

    if (pai)
    {
        float parentX = startX + idx * attr.marginX;
        float parentY = nextY;

        // desenha linha de conexao
        drawList->AddLine(
            ImVec2(x, y),                              // topo do nó atual
            ImVec2(parentX, nextY + attr.altura),      // base do pai
            ImGui::ColorConvertFloat4ToU32(Colors::Gray),
            2.0f
        );

        desenhaAscendentes(drawList, pai, parentX, nextY, depth + 1);
    }
}   

void ArvoreRender::desenhaDescendentes(ImDrawList* drawList, Pessoa* pessoa, float x, float y, int depth)
{
    NodeArvore node(pessoa);
    const NodeAttr& attr = node.getAttr();

    ImVec2 vi(x - attr.largura / 2, y);
    ImVec2 vf(x + attr.largura / 2, y + attr.altura);

    node.desenha(drawList, vi, vf);
    infoNode(vi, vf, pessoa->getInfo().nome);

    const auto& filhos = pessoa->getFilhos();
    if (filhos.empty())
        return;

    float larguraTotal = (filhos.size() - 1) * attr.marginX;

    float startX = x - larguraTotal / 2;
    float nextY = y + attr.altura + attr.marginY;

    for (size_t i = 0; i < filhos.size(); ++i)
    {
        float childX = startX + i * attr.marginX;
        float childY = nextY;

        // desenha linha de conexao
        drawList->AddLine(
            ImVec2(x, y + attr.altura),
            ImVec2(childX, childY),
            ImGui::ColorConvertFloat4ToU32(Colors::Gray),
            2.0f
        );

        desenhaDescendentes(drawList, filhos[i], childX, childY, depth + 1);
    }
}

void ArvoreRender::infoNode(const ImVec2& VIRect, const ImVec2& VFRect, const std::string& nome) const
{
    if (utils::mouseDentroDeRect(VIRect, VFRect))
    {
        ImGui::BeginTooltip();
        ImGui::TextUnformatted(nome.c_str());
        ImGui::TextColored(Colors::LightBlue, "Clique para copiar!");
        ImGui::EndTooltip();

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            ImGui::SetClipboardText(nome.c_str());
            ImGui::OpenPopup("NomeCopiado");
        }
    }

    if (ImGui::BeginPopup("NomeCopiado"))
    {
        ImGui::TextColored(Colors::Green, "Nome completo copiado!");
        ImGui::EndPopup();
    }
}

