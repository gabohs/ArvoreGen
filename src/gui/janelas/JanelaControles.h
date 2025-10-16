#include "../GuiLayer.h"
#include "../../backend/ArvoreGenealogica.h"
#include "../../backend/Pessoa.h"

#include <string>

class JControles : public IJanela
{
public:
    JControles(ArvoreGenealogica& arvore);

    const std::string& GetNome() const override
    {
        return m_Nome;
    }

    bool IsOpen() const override
    { 
        return m_JanelaAberta; 
    }
    void SetOpen(bool open) override
    { 
        m_JanelaAberta = open; 
    }

    void Renderiza() override;

private:
    std::string m_Nome = "Controles";
    bool m_JanelaAberta = true;

    ArvoreGenealogica& m_Arvore;

    void AddPessoaGui(Pessoa* pessoa);
};