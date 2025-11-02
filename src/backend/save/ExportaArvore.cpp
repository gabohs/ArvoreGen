#include "ExportaArvore.h"
#include <sstream>
#include <iostream>

ExportaArvore::ExportaArvore(const std::string& caminho, ArvoreGenealogica* arvore)
    : m_input(caminho), m_output(caminho), m_arvore(arvore)
{
    
}

bool ExportaArvore::salvaArvore()
{
    if(!m_output.is_open() || !m_arvore) return false;

    for (Pessoa* p : m_arvore->getPessoas())
    {
        const InfoPessoa& info = p->getInfo();
        
        std::string pai = "";
        if(p->getPai())
            pai = p->getPai()->getInfo().nome;

        std::string mae = "";
        if(p->getMae())
            mae = p->getMae()->getInfo().nome;   
            
        m_output << info.nome << ","
                << info.anoNascimento << ","
                << info.genero << ","
                << pai << ","
                << mae;

        for (Pessoa* filho : p->getFilhos())
        {
            m_output << "," << filho->getInfo().nome;
        }

        m_output << "\n";
    }

    std::cout << "Arvore salva com sucesso! \n";

    return true;
}

bool ExportaArvore::carregaArvore()
{
    if (!m_input.is_open() || !m_arvore) return false;

    std::string linha;
    while (std::getline(m_input, linha))
    {
        auto partes = divideLinha(linha);
        if (partes.size() < 3) continue;

        InfoPessoa info
        {
            partes[0], 
            std::stoi(partes[1]), 
            partes[2]
        };
        Pessoa* nova = new Pessoa(info);
        m_arvore->addPessoa(nova);

        // nome do pai
        if(partes.size() > 3 && !partes[3].empty())
        {
            Pessoa* pai = m_arvore->buscaPessoa(partes[3]);
            if (pai)
            {
                nova->setPai(pai);
                pai->addFilho(nova);
            }
        }
        
        // nome da mae
        if (partes.size() > 4 && !partes[4].empty())
        {
            Pessoa* mae = m_arvore->buscaPessoa(partes[4]);
            if (mae)
            {
                nova->setMae(mae);
                mae->addFilho(nova);
            }
        }

        for (size_t i = 5; i < partes.size(); ++i)
        {
            Pessoa* filho = m_arvore->buscaPessoa(partes[i]);
            if (filho)
                nova->addFilho(filho);
        }
    }

    std::cout << "Arvore carregada! \n";
    
    return true;
}

std::vector<std::string> ExportaArvore::divideLinha(const std::string& linha)
{
    std::vector<std::string> partes;
    std::stringstream ss(linha);
    std::string item;

    while (std::getline(ss, item, ','))
    {
        partes.push_back(item);
    }
    
    return partes;
}
