#include "../GuiLayer.h"

#include <string>

class JControles : public IJanela
{
public:
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
};