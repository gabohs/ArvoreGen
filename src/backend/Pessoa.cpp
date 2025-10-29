#include "Pessoa.h"

Pessoa::Pessoa(InfoPessoa& iP)
    : m_Info(iP), m_Pai(nullptr), m_Mae(nullptr)
{}

void Pessoa::setPai(Pessoa* p)
{
    m_Pai = p;
}

void Pessoa::setMae(Pessoa *m)
{
    m_Mae = m;
}

Pessoa* Pessoa::getMae() const
{
    return m_Mae;
}

Pessoa* Pessoa::getPai() const
{
    return m_Pai;
}

const std::vector<Pessoa*>& Pessoa::getFilhos() const
{
    return m_Filhos;
}

void Pessoa::addFilho(Pessoa* filho)
{   
    for (Pessoa* f : m_Filhos)
    {
        if (f == filho)
            return;
    }

    m_Filhos.push_back(filho);
}

const InfoPessoa& Pessoa::getInfo() const
{
    return m_Info;
}
