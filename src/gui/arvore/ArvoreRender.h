#pragma once

#include "../../backend/Pessoa.h"
#include "../../backend/ArvoreGenealogica.h"
#include "Node.h"

#include <imgui.h>

class ArvoreRender
{
public:
    ArvoreRender(ArvoreGenealogica& arvore);

    void desenhaArvoreAPartirDeAncestral(const std::string& nomeAncestral, const ImVec2& origem);
    void desenhaArvoreAscendentesEDescendentes(const std::string& nomePessoa, const ImVec2& origem);

private:
    void desenhaAscendentes(ImDrawList* drawList, Pessoa* pessoa, float x, float y, int depth);
    void desenhaDescendentes(ImDrawList* drawList, Pessoa* pessoa, float x, float y, int depth);
    
    void infoNode(const ImVec2& VIRect, const ImVec2& VFRect, const std::string& nome) const; // ao passar o mouse sobre um node da arvore, mostrar o nome completo da pessoa

private:
    ArvoreGenealogica& m_Arvore;
};
