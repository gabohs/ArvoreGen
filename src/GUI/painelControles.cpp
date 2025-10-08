#include "GUI.h"

void GUI::renderComponentsPanel()
{
    ImGui::Begin("Controles", nullptr, ImGuiWindowFlags_NoTitleBar);
    
    ImGui::Text("Adicionar pessoa");
    ImGui::Dummy(ImVec2(0, 5));

    char nome[256]{};
    char d[10]{};
    char gen = 'M';

    static bool m, f;

    ImGui::TextColored(Colors::Gray, "Nome:");
    ImGui::InputText("##Nome", nome, sizeof(nome));

    ImGui::TextColored(Colors::Gray, "Data Nascimento:");
    ImGui::InputText("##DataNasc", d, sizeof(d));

    ImGui::TextColored(Colors::Gray, "Gênero:");
    ImGui::Checkbox("Homem", &m);
    ImGui::SameLine();
    ImGui::Checkbox("Mulher", &f);

    ImGui::Dummy(ImVec2(0, 5));

    if (ImGui::Button("Adicionar Pessoa"))
    {
        // ADICIONAR PESSOA
    }

    ImGui::Separator();

    ImGui::End();
}