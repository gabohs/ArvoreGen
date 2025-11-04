#include "JanelaControles.h"

#include "../theme/colors.h"

#include "../../backend/save/ExportaArvore.h"

#include <string>

JControles::JControles(ArvoreGenealogica& arvore)
    : m_Arvore(arvore)
{
}

void JControles::Renderiza()
{
    ImGui::Begin(m_Nome.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar);

        secaoAdicionaPessoa();
        ImGui::Dummy(ImVec2(0, 5));

        secaoDefineRelacao();
        ImGui::Dummy(ImVec2(0, 5));

        secaoBusca();
        ImGui::Dummy(ImVec2(0, 10));

        secaoExporta();
        ImGui::Dummy(ImVec2(0, 10));

        popupsErro();
        secaoDebug();

    ImGui::End();
}

// -----------------------------------------------------------------------------------

void JControles::secaoAdicionaPessoa()
{
    ImGui::SeparatorText("Adicionar Pessoa");
    ImGui::Dummy(ImVec2(0, 5));

    static char nome[256]{};
    static int anoNasc = 2000;
    static const char* genero;

    static bool m, f;

    ImGui::Text("Nome:");
    ImGui::InputText("##Nome", nome, sizeof(nome));

    ImGui::Text("Ano de Nascimento:");
    ImGui::InputInt("##AnoNasc", &anoNasc);

    ImGui::Text("Gênero:");
    // ImGui::InputText("##Genero", genero, sizeof(genero));

    const char* generos[] = {"Masc.", "Fem.", "Outro"};

    static int genSelecionado = 0;
    ImGui::Combo("##selecoes_genero", &genSelecionado, generos, IM_ARRAYSIZE(generos));
    genero = generos[genSelecionado];
    
    ImGui::Dummy(ImVec2(0, 5));

    if (ImGui::Button("Adicionar Pessoa"))
    {
        InfoPessoa infoP;
        infoP.nome = nome;
        infoP.anoNascimento = anoNasc;
        infoP.genero = genero;

        Pessoa* p = new Pessoa(infoP); 

        AddPessoaGui(p);
    }
}

void JControles::secaoDefineRelacao()
{
    ImGui::SeparatorText("Definir Relações");

    static char nome[256]{};
    static char nomeMae[256]{};
    static char nomePai[256]{};
    

    ImGui::TextColored(Colors::DarkBlue, "Nome da pessoa:");
    ImGui::InputText("##NomeDR", nome, sizeof(nome));

    ImGui::TextColored(Colors::DarkBlue, "Nome da mãe: ");
    ImGui::InputText("##NomeMae", nomeMae, sizeof(nomeMae));

    ImGui::SameLine();

    if (ImGui::SmallButton("Definir Mae"))
    {   
        Pessoa* pSelecionada = m_Arvore.buscaPessoa(std::string(nome));
        Pessoa* mae = m_Arvore.buscaPessoa(std::string(nomeMae));

        if (pSelecionada == nullptr)
            ImGui::OpenPopup("AvisoPNE"); // PNE = pessoa n encontrada ;)
        else if (mae == nullptr)
            ImGui::OpenPopup("AvisoMaeNE");
        else 
        {   
            pSelecionada->setMae(mae);
            mae->addFilho(pSelecionada);

            ImGui::OpenPopup("RelacaoSucesso");
        }
    }

    ImGui::TextColored(Colors::DarkBlue, "Nome do pai: ");
    ImGui::InputText("##NomePai", nomePai, sizeof(nomePai));

    ImGui::SameLine();

    if (ImGui::SmallButton("Definir Pai"))
    {   
        Pessoa* pSelecionada = m_Arvore.buscaPessoa(std::string(nome));
        Pessoa* pai = m_Arvore.buscaPessoa(std::string(nomePai));

        if (pSelecionada == nullptr)
            ImGui::OpenPopup("AvisoPNE"); // PNE = pessoa n encontrada ;)
        else if (pai == nullptr)
            ImGui::OpenPopup("AvisoPaiNE");
        else
        {   
            pSelecionada->setPai(pai);
            pai->addFilho(pSelecionada);
            ImGui::OpenPopup("RelacaoSucesso");
        }
    }
}

void JControles::secaoBusca()
{
    ImGui::SeparatorText("Buscar Pessoa");

    static char nome[256]{};

    ImGui::TextColored(Colors::DarkBlue, "Nome:");
    ImGui::InputText("##NomeBusca", nome, sizeof(nome));
    ImGui::SameLine();

    static Pessoa* pSelecionada = nullptr; 

    if (ImGui::Button("Buscar"))
    {
        pSelecionada = m_Arvore.buscaPessoa(std::string(nome));
        
        if (pSelecionada == nullptr)
            ImGui::OpenPopup("AvisoPNE");
        else
            m_PainelInfoPessoaAberto = true;
    }

    if (m_PainelInfoPessoaAberto && pSelecionada != nullptr)
        abrePainelInfoPessoa(pSelecionada);    
}

void JControles::secaoExporta()
{
    ImGui::SeparatorText("Salvar/Carregar Árvore");

    static char nomeArquivo[256] = "arvore";

    ImGui::TextColored(Colors::DarkBlue, "Caminho do arquivo:");
    ImGui::InputText("##NomeArquivo", nomeArquivo, sizeof(nomeArquivo));
    ImGui::SameLine();
    ImGui::Text(".csv");

    if (ImGui::Button("Salvar Árvore", ImVec2(150, 0)))
    {   
        std::string arquivo = std::string(nomeArquivo) + ".csv";
        ExportaArvore exportador(arquivo, &m_Arvore);

        if (exportador.salvaArvore())
            ImGui::OpenPopup("ArquivoSalvo");
        else
            ImGui::OpenPopup("ErroSalvar");
    }

    ImGui::SameLine();

    if (ImGui::Button("Carregar Árvore", ImVec2(150, 0)))
    {   
        std::string arquivo = std::string(nomeArquivo) + ".csv";
        ExportaArvore exportador(arquivo, &m_Arvore);

        if (exportador.carregaArvore())
            ImGui::OpenPopup("ArquivoCarregado");
        else
            ImGui::OpenPopup("ErroCarregar");
    }

    ImGui::Dummy(ImVec2(0, 10));
}

void JControles::abrePainelInfoPessoa(const Pessoa* pessoa)
{   
    // gambiarra do krai pra abrir janelinha de busca
    
    ImGui::SetNextWindowSize(ImVec2(350, 350));
    ImGui::Begin("InfoPessoa", &m_PainelInfoPessoaAberto, ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::TextColored(Colors::Green, "Informações de %s", pessoa->getInfo().nome.c_str());
        ImGui::Separator();

        ImGui::TextColored(Colors::Gray, "Nome Completo: ");
        ImGui::SameLine();
        ImGui::Text(pessoa->getInfo().nome.c_str());

        ImGui::TextColored(Colors::Gray, "Gênero: ");
        ImGui::SameLine();
        ImGui::Text(pessoa->getInfo().genero.c_str());

        ImGui::TextColored(Colors::Gray, "Ano de nascimento: ");
        ImGui::SameLine();
        ImGui::Text( std::to_string(pessoa->getInfo().anoNascimento).c_str() );

        ImGui::Dummy(ImVec2(0, 2));

        ImGui::TextColored(Colors::Gray, "Pai: ");
        ImGui::SameLine();

        if (pessoa->getPai() != nullptr)
            ImGui::Text( pessoa->getPai()->getInfo().nome.c_str() );
        else 
            ImGui::TextColored(Colors::Red, "Não registrado");

        ImGui::TextColored(Colors::Gray, "Mãe: ");
        ImGui::SameLine();

        if (pessoa->getMae() != nullptr)
            ImGui::Text( pessoa->getMae()->getInfo().nome.c_str() );
        else
            ImGui::TextColored(Colors::Red, "Não registrada");

        ImGui::TextColored(Colors::Gray, "Filhos: ");

        if (pessoa->getFilhos().empty())
            ImGui::TextColored(Colors::Red, "Nenhum Filho registrado!");
        else
        {   
            ImGui::BeginChild("Filhos", ImVec2(0, 100), true);
            for (const Pessoa* p : pessoa->getFilhos())
            {   
                ImGui::Text(p->getInfo().nome.c_str());
            }
            ImGui::EndChild();
        }

    ImGui::End();
}

void JControles::popupsErro()
{
    // popups
    if (ImGui::BeginPopup("PessoaAdc"))
    {
        ImGui::TextColored(Colors::Green, "Pessoa adicionada com sucesso!");

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("ErroAdc"))
    {
        ImGui::TextColored(Colors::Red, "Pessoa já está na arvore!");

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("AvisoPNE")) 
    {
        ImGui::TextColored(Colors::Red, "Pessoa não encontrada!");

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("AvisoMaeNE"))
    {
        ImGui::TextColored(Colors::Red, "Mae não encontrada!");

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("AvisoPaiNE"))
    {
        ImGui::TextColored(Colors::Red, "Pai não encontrado!");

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("RelacaoSucesso"))
    {
        ImGui::TextColored(Colors::Green, "Relação definida com sucesso!");

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("ArquivoSalvo"))
    {
        ImGui::TextColored(Colors::Green, "Árvore salva com sucesso!");
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("ArquivoCarregado"))
    {
        ImGui::TextColored(Colors::Green, "Árvore carregada com sucesso!");
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("ErroSalvar"))
    {
        ImGui::TextColored(Colors::Red, "Erro ao salvar a árvore!");
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("ErroCarregar"))
    {
        ImGui::TextColored(Colors::Red, "Erro ao carregar a árvore!");
        ImGui::EndPopup();
    }
}

void JControles::secaoDebug()
{
    ImGui::SeparatorText("DEBUG");

    if (ImGui::Button("[DEBUG] Printar Arvore"))
    {
        m_Arvore.printPessoas();
    }
}

void JControles::AddPessoaGui(Pessoa* pessoa)
{
    if (!m_Arvore.buscaPessoa(pessoa->getInfo().nome))
    {
        m_Arvore.addPessoa(pessoa);
        ImGui::OpenPopup("PessoaAdc");
    }
    else
    {
        ImGui::OpenPopup("ErroAdc");
    }     
}
