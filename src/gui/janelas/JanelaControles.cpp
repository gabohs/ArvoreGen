#include "JanelaControles.h"

JControles::JControles(ArvoreGenealogica& arvore)
    : m_Arvore(arvore)
{
}



void JControles::Renderiza()
{
    ImGui::Begin(m_Nome.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar);
    
    ImGui::Text("Adicionar pessoa");
    ImGui::Dummy(ImVec2(0, 5));

    static char nome[256]{};
    static int anoNasc = 2000;
    static char genero[32]{ "Masculino" };

    static bool m, f;

    ImGui::Text("Nome:");
    ImGui::InputText("##Nome", nome, sizeof(nome));

    ImGui::Text("Ano de Nascimento:");
    ImGui::InputInt("##AnoNasc", &anoNasc);

    ImGui::Text("Gênero:");
    ImGui::InputText("##Genero", genero, sizeof(genero));

    ImGui::Dummy(ImVec2(0, 5));

    if (ImGui::Button("Adicionar Pessoa"))
    {
        InfoPessoa infoP;
        infoP.nome = nome;
        infoP.anoNascimento = anoNasc;
        infoP.genero = genero;

        Pessoa* p = new Pessoa(infoP); 

        AddPessoaGui(p);
    }

    ImGui::Separator();

    if (ImGui::Button("[DEBUG] Printar Arvore"))
    {
        m_Arvore.printPessoas();
    }

    ImGui::End();
}

void JControles::AddPessoaGui(Pessoa* pessoa)
{
    m_Arvore.addPessoa(pessoa);
}
