#include "JanelaVisualiza.h"

JVisualizacao::JVisualizacao(ArvoreGenealogica &arvore)
    : m_aRender(arvore)
{
}

void JVisualizacao::Renderiza()
{
    ImGui::Begin(m_Nome.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar);

    ImGui::BeginChild("Canvas", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
    m_aRender.desenhaArvore();
    ImGui::EndChild();

    ImGui::End();
}