#include "ArvoreRender.h"


#include "../theme/colors.h"

#include "../utils/mouse.h"

#include <iostream>

ArvoreRender::ArvoreRender(ArvoreGenealogica &arvore)
    : m_Arvore(arvore)
{
}

void ArvoreRender::desenhaArvoreAPartirDeAncestral(const std::string& nomeAncestral)
{
    Pessoa* ancestral = m_Arvore.buscaPessoa(nomeAncestral); 
    
    if (!ancestral)
        return;

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 origem = ImGui::GetCursorScreenPos();

    float startX = origem.x + ImGui::GetWindowSize().x / 2; 
    float startY = origem.y + 50.f;   

    desenhaDescendentes(drawList, ancestral, startX, startY, 0);
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

    float totalWidth = (filhos.size() - 1) * attr.marginX;

    float startX = x - totalWidth / 2;
    float nextY = y + attr.altura + attr.marginY;

    for (size_t i = 0; i < filhos.size(); ++i)
    {
        float childX = startX + i * attr.marginX;
        float childY = nextY;

        drawList->AddLine(
            ImVec2(x, y + attr.altura),
            ImVec2(childX, childY),
            ImGui::ColorConvertFloat4ToU32(Colors::Gray),
            2.0f
        );

        desenhaDescendentes(drawList, filhos[i], childX, childY, depth + 1);
    }
}

void ArvoreRender::desenhaAscendentes(ImDrawList *drawList, Pessoa *pessoa, float x, float y, int depth)
{
}

void ArvoreRender::infoNode(const ImVec2& VIRect, const ImVec2& VFRect, const std::string& nome) const
{
    if (utils::mouseDentroDeRect(VIRect, VFRect))
    {
        ImGui::BeginTooltip();
        ImGui::TextUnformatted(nome.c_str());
        ImGui::EndTooltip();
    }
}
