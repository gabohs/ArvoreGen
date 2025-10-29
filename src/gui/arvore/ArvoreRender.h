#pragma once

#include "../../backend/Pessoa.h"
#include "../../backend/ArvoreGenealogica.h"
#include "Node.h"

#include <imgui.h>

class ArvoreRender
{
public:
    ArvoreRender(ArvoreGenealogica& arvore);

    void desenhaArvoreAPartirDeAncestral(const std::string& nomeAncestral);

private:
    void desenhaNodeRecursivo(ImDrawList* drawList, Pessoa* pessoa, float x, float y, int depth);

    void infoNode(const ImVec2& VIRect, const ImVec2& VFRect, const std::string& nome) const; // ao passar o mouse sobre um node da arvore, mostrar o nome completo da pessoa

private:
    ArvoreGenealogica& m_Arvore;
};
