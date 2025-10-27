#pragma once

#include <vector>

#include "Pessoa.h"

class ArvoreGenealogica
{
public:
    Pessoa* buscaPessoa(const std::string& nome) const;

    void addPessoa(Pessoa* pessoa);
    void printPessoas();

    const std::vector<Pessoa*>& getPessoas() const;

private:
    std::vector<Pessoa*> m_Pessoas;
};