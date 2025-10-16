#include "ArvoreGenealogica.h"

#include <iostream>

Pessoa* ArvoreGenealogica::buscaPessoa(std::string& nome)
{   
    for (Pessoa* pessoa : m_Pessoas)
    {
        if (pessoa->getInfo().nome == nome)
            return pessoa;
    }

    return nullptr;
}

void ArvoreGenealogica::addPessoa(Pessoa *pessoa)
{
    m_Pessoas.push_back(pessoa);
}

void ArvoreGenealogica::printPessoas()
{   
    std::cout << "==== [ESTRUTURA ATUAL DA ARVORE] ====" << std::endl;
    for (Pessoa* p : m_Pessoas)
    {   
        std::cout << p->getInfo().nome << "   ";
        std::cout << p->getInfo().anoNascimento << "   ";
        std::cout << "G: " << p->getInfo().genero << std::endl;   
    }
    std::cout << "=====================================" << std::endl << std::endl;
}
