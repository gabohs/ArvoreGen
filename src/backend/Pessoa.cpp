#include "Pessoa.h"

Pessoa::Pessoa(InfoPessoa& iP)
    : m_Info(iP)
{}

void Pessoa::setPai(Pessoa* p)
{
    m_Pai = p;
}

void Pessoa::setMae(Pessoa *m)
{
    m_Mae = m;
}

void Pessoa::addFilho(Pessoa *filho)
{   
    m_Filhos.push_back(filho);
}

const InfoPessoa& Pessoa::getInfo() const
{
    return m_Info;
}
