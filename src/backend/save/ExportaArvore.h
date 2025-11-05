#pragma once

#include "../ArvoreGenealogica.h"
#include "../Pessoa.h"

#include <string>
#include <vector>
#include <fstream>

class ExportaArvore
{
public:
    ExportaArvore(const std::string& caminho, ArvoreGenealogica* arvore);

    bool salvaArvore();
    bool carregaArvore();
    
private:
    std::vector <std::string> divideLinha(const std::string& linha);

private:
    std::string m_caminho;
    std::ifstream m_input;
    std::ofstream m_output;
    ArvoreGenealogica* m_arvore;
};