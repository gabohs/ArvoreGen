#include "JanelaVisualiza.h"

#include "../theme/colors.h"

#include "../utils/centralizaScroll.h"

JVisualizacao::JVisualizacao(ArvoreGenealogica &arvore)
    : m_aRender(arvore)
{
}

void JVisualizacao::Renderiza()
{
    ImGui::Begin(m_Nome.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar);

    ImGui::SetWindowFontScale(1.5f);
    ImGui::TextColored(Colors::Gray, "Desenho da Arvore");
    ImGui::SetWindowFontScale(1.f);

    static char nome[256]{};
    static bool desenhar = false;

    const char* tiposRenderizacao[2] = {"A partir de ancestral", "Ascendentes e Descendentes"};

    static int tipoSelecionado = 0;

    static bool renderizou1vez = false;

    ImGui::TextColored(Colors::DarkBlue, "Configurações: ");
    ImGui::Combo("Tipo Render", &tipoSelecionado, tiposRenderizacao, IM_ARRAYSIZE(tiposRenderizacao));

    ImGui::TextColored(Colors::DarkBlue, "Pessoa inicial:");
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
        {
            desenhar = false;
            renderizou1vez = false;
        }
            
        ImGui::PopStyleColor();
    }
    
    ImGui::BeginChild("Canvas", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);

    if (desenhar)
    {   
        ImVec2 tamanhoCanvas(4000, 4000);
        ImGui::Dummy(tamanhoCanvas); // para poder scrollar

        if (tipoSelecionado == 0)
        {   
            ImGui::SetCursorPos(ImVec2(tamanhoCanvas.x / 2.0f, 150.f)); // cursor no topo
            m_aRender.desenhaArvoreAPartirDeAncestral(nome, ImGui::GetCursorScreenPos());

            if (!renderizou1vez) // roda apenas na primeira vez
            {
                utils::centralizaScrollEmX(); 
                renderizou1vez = true;
            }        
        }
            
        else if (tipoSelecionado == 1)
        {
            ImGui::SetCursorPos(ImVec2(tamanhoCanvas.x / 2.f, tamanhoCanvas.y / 2.f)); // cursor no meio
            m_aRender.desenhaArvoreAscendentesEDescendentes(nome, ImGui::GetCursorScreenPos());

            if (!renderizou1vez)
            {
                utils::centralizaScrollEmXY(); // tambem roda apenas uma vez
                renderizou1vez = true;
            }   
        }
    }
    
    ImGui::EndChild();

    ImGui::End();
}