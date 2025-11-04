#include "truncaNome.h"

#include "imgui.h"

namespace utils
{
    const std::string& truncaNome(const std::string& nome, const int larguraMax)
    {   
        float tamanhoNomeX = ImGui::CalcTextSize(nome.c_str()).x;

        if (tamanhoNomeX < larguraMax)
            return nome;

        std::string nomeTruncado = nome;
        while (!nome.empty() && ImGui::CalcTextSize((nome + "...").c_str()).x > larguraMax)
        {
            nomeTruncado.pop_back();
        }
        nomeTruncado+= "...";
        
        return nomeTruncado;
    }
}

