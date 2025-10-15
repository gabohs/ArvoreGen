#include "JanelaVisualiza.h"

void JVisualizacao::Renderiza()
{
    ImGui::Begin(m_Nome.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar);

    ImGui::Text("Ola mundo!");

    ImGui::End();
}