#pragma once

#include <vector>

#include "Pessoa.h"

class ArvoreGenealogica
{
public:
    Pessoa* buscaPessoa(std::string& nome);

    void addPessoa(Pessoa* pessoa);
    void printPessoas();

    const std::vector<Pessoa*>& getPessoas() const;

private:
    std::vector<Pessoa*> m_Pessoas;
};