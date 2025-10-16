#pragma once

#include <vector>

#include "Pessoa.h"

class ArvoreGenealogica
{
public:
    Pessoa* buscaPessoa(std::string& nome);

    void addPessoa(Pessoa* pessoa);
    void printPessoas();

private:
    std::vector<Pessoa*> m_Pessoas;
};