#pragma once

#include "../../backend/Pessoa.h"
#include "../../backend/ArvoreGenealogica.h"
#include <imgui.h>

class ArvoreRender
{
public:
    ArvoreRender(ArvoreGenealogica& arvore);
    void desenhaArvore();

private:
    ArvoreGenealogica& m_Arvore;
};
