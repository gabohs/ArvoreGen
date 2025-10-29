#include "JanelaVisualiza.h"

#include "../theme/colors.h"

JVisualizacao::JVisualizacao(ArvoreGenealogica &arvore)
    : m_aRender(arvore)
{
}

void JVisualizacao::Renderiza()
{
    ImGui::Begin(m_Nome.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar);

    ImGui::SetWindowFontScale(1.5f);
    ImGui::TextColored(Colors::DarkBlue, "Desenho da Arvore");
    ImGui::SetWindowFontScale(1.f);

    static char nome[256]{};
    static bool desenhar = false;

    ImGui::TextColored(Colors::Gray, "Ancestral principal:");
    ImGui::InputText("##AncestralPrincipal", nome, sizeof(nome));

    ImGui::SameLine();
    

    if (!desenhar)
    {   
        ImGui::PushStyleColor(ImGuiCol_Button, Colors::Green);
        if (ImGui::Button("Desenhar"))
            desenhar = true;
        ImGui::PopStyleColor();
    }
    else
    {   
        ImGui::PushStyleColor(ImGuiCol_Button, Colors::BrightRed);
        if (ImGui::Button("Limpar"))
            desenhar = false;
        ImGui::PopStyleColor();
    }

    

    ImGui::BeginChild("Canvas", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);
    if (desenhar)
        m_aRender.desenhaArvoreAPartirDeAncestral(nome);
    ImGui::EndChild();

    ImGui::End();
}