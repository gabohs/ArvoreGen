#include "Node.h"

#include "../theme/colors.h"
#include "../utils/truncaNome.h"

NodeArvore::NodeArvore(Pessoa *pessoa)
    : m_Pessoa(pessoa), cor(ImGui::ColorConvertFloat4ToU32(Colors::Aqua))
{   
}

void NodeArvore::desenha(ImDrawList* drawList, ImVec2 verticeInicial, ImVec2 verticeFinal)
{
    if (m_Pessoa->getInfo().genero == "Fem.")
        cor = ImGui::ColorConvertFloat4ToU32(Colors::Purple);
    else if (m_Pessoa->getInfo().genero == "Outro")
        cor = ImGui::ColorConvertFloat4ToU32(Colors::Gray);

    drawList->AddRectFilled(
        verticeInicial,
        verticeFinal,
        cor,
        m_Attr.arredondamento
    );

    std::string nome = m_Pessoa->getInfo().nome;
    std::string nomeTruncado = utils::truncaNome(nome, (m_Attr.largura - 10) );

    drawList->AddText(
        ImVec2( verticeInicial.x + ( (m_Attr.largura - ImGui::CalcTextSize(nomeTruncado.c_str()).x) / 2), verticeInicial.y + 15 ), 
        ImGui::ColorConvertFloat4ToU32(Colors::DarkGray),
        nomeTruncado.c_str()
    );

    std::string genero = "G: " + m_Pessoa->getInfo().genero;
    drawList->AddText(
        ImVec2( verticeInicial.x + ((m_Attr.largura - ImGui::CalcTextSize(genero.c_str()).x) / 2), verticeInicial.y + 40 ),
        ImGui::ColorConvertFloat4ToU32(Colors::BrightRed),
        genero.c_str()
    );

    std::string nascimento = "Nasc: " + std::to_string(m_Pessoa->getInfo().anoNascimento);
    drawList->AddText(
        ImVec2( verticeInicial.x + ((m_Attr.largura - ImGui::CalcTextSize(nascimento.c_str()).x) / 2), verticeFinal.y - 30 ),
        ImGui::ColorConvertFloat4ToU32(Colors::Yellow),
        nascimento.c_str()
    );
}
