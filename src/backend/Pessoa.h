#pragma once

#include <vector>
#include <string>

struct InfoPessoa
{
    std::string nome;
    int anoNascimento;
    std::string genero;
};

class Pessoa
{
public:
    Pessoa(InfoPessoa& iP);

    void setPai(Pessoa* p);
    void setMae(Pessoa* m);

    void addFilho(Pessoa* filho);

    const InfoPessoa& getInfo() const;

private:
    InfoPessoa m_Info;

    Pessoa* m_Pai;
    Pessoa* m_Mae;

    std::vector<Pessoa*> m_Filhos;
};