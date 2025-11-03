# Documentação completa do Projeto Arvore Genealógica

## 1. Do Processo de desenvolvimento

- O processo de desenvolvimento foi iniciado no dia 15 de outubro de 2025.
   
- Para facilitar a colaboração, a criaçao de diferentes branches foi necessária.

## 2. As branches

### 2.1 main

> [!NOTE]
> É a Branch principal, contendo o projeto que funciona de fato. Não possui a pasta build


### 2.2 dev

> [!NOTE]
> É a branch mais abrangente de desenvolvimento

### 2.3 Build

> [!NOTE]
> Similar a main, mas possui a pasta build

- O objetivo dessa branch é poupar o professor de ter que buildar o projeto do zero, visto que esse processo em c++ é uma desgraça. Tanto o executável `debug` quanto o `release` estão localizados em `build\Debug\Debug\ArvoreGen.exe` e `build\Release\Release\ArvoreGen.exe`, respectivamente.


### 2.4 As demais branches

> [!NOTE]
> São as branches para implementar uma feature específica. Quando a feature está pronta, é feito o merge com a branch dev

## 3. A estrutura geral do projeto

### 3.1 Pasta `src`

- Contêm os arquivos .cpp e .h do projeto

### src/backend

- Implementação das estruturas `Pessoa` e `ArvoreGenealogica` (mais detalhes na próxima seção). Também possui a lógica de save e export da árvore.

### src/core

- Classe `Window`, que é apenas uma espécie de wrapper de uma janela glfw
- Classe `App`. Assim como um maestro coordena uma orquestra, a classe App coordena o projeto. É aqui que tudo se conecta. A função-membro `App::Run` é implementada em um arquivo separado, achei melhor fazer assim pois é nela que a parte mais importante da aplicação acontece: o loop principal.

- O `main.cpp` apenas chama a função-membro `App::Run`. A linha de código bizarra no topo do main serve para o console não aparecer no modo release.

> [!NOTE]
> Essa pasta foi bastante inspirada no vídeo do The Cherno sobre arquitetura de software em c++: https://www.youtube.com/watch?v=rUxZ5N77M5E (Ref. 1)
>
> Esse vídeo foi útil também: https://www.youtube.com/watch?v=U1BnzWX194Q (Ref. 2)
>
> E esse também: https://www.youtube.com/watch?v=OYQp0GuoByM (Ref. 3)

### src/gui

- `gui/arvore`: Contêm a ArvoreRender, responsável pelos algorítmos de renderização, com base na árvore do backend.

- `gui/janelas`: São os dois painéis da aplicação, o JControles é o do lado esquerdo, e o JanelaVisualiza é a parte maior na direita. O que cada uma faz é autoexplicativo pelos nomes.

- `gui/theme`: Configurações de cores, arredondamento das janelas, etc. 

> [!IMPORTANT]
> Tema foi inspirado (roubado) dos fóruns do ImGui: https://github.com/ocornut/imgui/issues/707#issuecomment-2832090282 (Ref. 6)

- `gui/utils`: Algumas utilidades usadas na interface de usuário.


### 3.2 Pasta `vendor`

- Um *Vendor* é um adjetivo em inglês atribuido à uma pessoa ou empresa, indicando que esta vende serviços para clientes.
- A programação se apropria desse conceito e o utiliza para nomear uma pasta que contêm bibliotecas third-party. 


## 4. As bibliotecas usadas

### 4.1 [ImGui](https://github.com/ocornut/imgui)

- ImGui significa Immediate Mode Graphical user interface. As interfaces immediate mode diferem das "normais" (retained mode). Elas podem ser menos eficientes, pois redesenham a interface sempre (a cada frame), mas se tornam muito mais simples de utilizar.

- As janelas do ImGui são desenhadas em cima de uma janela gerada por um backend.
- Existe uma branch do ImGui chamada docking, que permite fazer com que as janelas "grudem" na janela de fundo e sejam redimensionadas e reajeitadas na interface.
- Uma coisa legal do ImGui é a possibilidade de escolher o backend. Você pode utilizar vulkan, opengl, sdl, sfml, directX... 

- Nesse projeto utilizamos OpenGL, com glfw.

> [!IMPORTANT]
> Tutorial completo das funcionalidades da biblioteca ImGui: https://www.youtube.com/watch?v=790aMkbsBm8 (Ref. 4)

### 4.2 [GLFW](https://github.com/glfw/glfw)

- Facilita a criação do contexto OpenGL, providenciado a criação simples de uma janela, input handling e eventos.   


## 5. Detalhamento da Estrutura do Projeto

- Adendo: Não detalharei os getters e setters das classes (autoexplicativos), nem seu constructor e destructor, que são usados como normalmente sempre são (para inicialização e cleanup respectivamente).

### 5.1 a função main

> Localização: src/core/main.cpp

- Começaremos nossa análise no main.cpp

- A main instancia a classe `App` e chama seu método `Run`, que contêm o loop principal. 

### 5.2 a classe App

- Coordenadora do projeto
- As informações do app são armazenadas na struct InfoApp

> Definição: src/core/App.h
> 
> Implementação: src/core/App.cpp

#### Métodos públicos:

#### `void Run()`

- Contêm o loop principal da aplicacao

#### `void Stop()`

- Para o main loop setando a variável m_Rodando para `false`

#### Métodos privados:

#### `bool initImgui()`

- Boilerplate para inicializar o ImGui

#### `void shutdown()`

- Finaliza o ImGui e a Janela

#### Membros privados

- `ArvoreGenealogica m_Arvore`: instância da classe `ArvoreGenealogica` (src/backend/ArvoreGenealogica.h). Ela é passada no constructor das janelas.

- `std::unique_ptr<Window> m_Janela`: pointer para a janela (contexto opengl via glfw)
- `std::unique_ptr<GuiLayer> m_GuiLayer`: pointer para a classe `GuiLayer` (src/gui/GuiLayer.h)

const float tamFonte = 17.f: tamanho da fonte

bool m_Rodando = false: controla se o app esta rodando ou não. Após início do programa, quando false, essa variável encerra o main loop.

### 5.3 A interface IJanela

- É herdada por ambas as janelas (paineis) (JControles e JVisualizacao)

> Definição: src/gui/GuiLayer.h
> 
> Implementação: src/gui/GuiLayer.cpp

### 5.4 A classe GuiLayer

- É dona de todas as janelas, armazenada em um vector. 
- Possui tanto boilerplate do ImGui, quanto código para renderizar as janelas

> Definição: src/gui/GuiLayer.h
> 
> Implementação: src/gui/GuiLayer.cpp

#### Métodos públicos

#### `void Begin()`

- Mais boilerplate do ImGui

#### `void End()`

- Finaliza ImGui

#### `void Render()`

- Boilerplate que precisa ser chamado antes de renderizar as janelas de fato (ir para o proximo frame)

#### `void RenderizaJanelas()`

- chama a função Renderiza() de todas as janelas

#### `void AddJanela(std::shared_ptr<IJanela> janela)`

- Adiciona janela do vector de janelas
- Chamada no constructor classe App

#### Métodos privados

#### `void setupDockspace()`

- Boilerplate para o dockspace, explicado em 4.1.

#### Membros privados

- `std::vector<std::shared_ptr<IJanela>> m_Janelas`: É o vector que armazena todas as janelas. Como todas as janelas herdam a interface IJanela, podemos criar um vector de shared pointers IJanela que apontam para cada respectiva janela.

### 5.5 A classe Pessoa

- Seguindo o mesmo padrão da classe App, também temos uma struct com as informações da pessoa (InfoPessoa)
- Essa classe é a representação de uma pessoa da árvore genealógica.

> Definição: src/backend/Pessoa.h
> 
> Implementação: src/backend/Pessoa.cpp

#### Métodos públicos

- A maioria dos métodos são getters e setters. Veja a implementação deles em Pessoa.cpp

#### `void addFilho(Pessoa* filho)`
- Adiciona um filho no vector m_Filhos.
- Verifica se o filho já existe. Se já estiver no vector, simplesmente não o adiciona novamente.

#### Membros privados

- `InfoPessoa m_Info`: é a instanciação da struct que contêm as informações da pessoa (nome, ano de nascimento e gênero). Cada pessoa tem esses 3 atributos

- `Pessoa* m_Pai`: pointer para o pai
- `Pessoa* m_Mae`: pointer para a mãe

- `std::vector<Pessoa*> m_Filhos`: vector de pointers para todos os filhos


### 5.6 A classe ArvoreGenealogica

- É a representação da Arvore Genealógica.
- Utiliza um vector de Pessoa* para armazenar todas as pessoas da árvore

> Definição: src/backend/ArvoreGenealogica.h
> 
> Implementação: src/backend/ArvoreGenealogica.cpp

#### Métodos públicos

#### `Pessoa* buscaPessoa(const std::string& nome) const`

- Busca uma pessoa na árvore. Se ela existir, retorna um ponteiro para ela. Se não existir, simplesmente retorna nullptr.

#### `void addPessoa(Pessoa* pessoa)`

- Adiciona uma pessoa no vector m_Pessoas;

#### `void printPessoas()`

- Printa todas as pessoas no vector no terminal. Só para debug

#### Membros privados

- `std::vector<Pessoa*> m_Pessoas`: vector de pointers para todas as pessoas da árvore


### 5.7 A classe ArvoreRender

- Contêm as funções usadas na renderização da árvore.
- É instanciada posteriormente na Janela de Visualização (JVisualizacao), e seus métodos são chamados por lá.
- Armazena uma referência para ArvoreGenealogica, pois obviamente para desenhar é preciso ter as informações da árvore

> Definição: src/gui/arvore/ArvoreRender.h
> 
> Implementação: src/gui/arvore/ArvoreRender.cpp

#### Métodos públicos

#### `void desenhaArvoreAPartirDeAncestral(const std::string& nomeAncestral, const ImVec2& origem)`

- Desenha a árvore a partir de um ancestral
- Chama a função recursiva desenhaDescendentes

#### `void desenhaArvoreAscendentesEDescendentes(const std::string& nomePessoa, const ImVec2& origem)`

- Desenha os ascendentes e descendentes de uma pessoa
- Chama as funções recursivas desenhaAscendentes() e desenhaDescendentes()

#### Métodos privados

#### `void desenhaAscendentes(ImDrawList* drawList, Pessoa* pessoa, float x, float y, int depth)`

- Função recursiva que desenha os ascendentes de uma pessoa e os conecta com linhas

#### void `desenhaDescendentes(ImDrawList* drawList, Pessoa* pessoa, float x, float y, int depth)`

- Função recursiva que desenha os descendentes de uma pessoa e os conecta com linhas

#### `void infoNode(const ImVec2& VIRect, const ImVec2& VFRect, const std::string& nome) const`

- Função que mostra uma tooltip com o nome completo da pessoa ao passar o mouse em cima de um node (node é a representação visual de uma pessoa)

#### Membros privados

- `ArvoreGenealogica& m_Arvore`: Referência para a arvore genealógica. É passada para a classe pelo constructor, em sua instância em JVisualização

### 5.8 A classe NodeArvore

- Assim como as outras, existe uma struct NodeAttr para armazenar as informações de um Node
- Um Node representa uma pessoa visualmente. É um quadrado que possui o nome da pessoa, seu ano de nascimento e gênero.
- Node recebe um ponteiro da pessoa que ele representa pelo constructor

> Definição: src/gui/arvore/Node.h
> 
> Implementação: src/gui/arvore/ArvoreRender.cpp

#### Métodos públicos

#### `void desenha(ImDrawList* drawList, ImVec2 verticeInicial, ImVec2 verticeFinal)`

- desenha o node

#### Membros privados

- `Pessoa* m_Pessoa`: Ponteiro para a pessoa que o node está representando
    
- `NodeAttr m_Attr`: instância da struct com informações do node

- `ImU32 cor`: cor do node


### 5.9 A classe JControles

- Herda a interface IJanela
- É a janela da esquerda, com os controles do aplicativo (adicionar pessoa, buscar pessoa, etc)

> Definição: src/gui/janelas/JanelaControles.h
> 
> Implementação: src/gui/janelas/JanelaControles.cpp

#### Métodos públicos

- Todos os da IJanela, em especial o Renderiza()

#### Métodos privados

- A maioria dos métodos privados dessa classe servem para separar as partes da interface de usuário. Cada método renderiza sua parte, e todos eles são posteriormente chamados na funcao Renderiza()

#### `void AddPessoaGui(Pessoa* pessoa)` 

- Executa ao clicar no botão de adicionar pessoa, e adiciona a pessoa no vetor da ArvoreGenealogica

#### Membros privados

- `std::string m_Nome = "Controles"`: Nome da janela
- `bool m_JanelaAberta = true`: controla se a janela esta aberta ou não

- `bool m_PainelInfoPessoaAberto = false`: controla se o painelzinho de info da pessoa esta aberto ou não

- `ArvoreGenealogica& m_Arvore`: Referência para a ArvoreGenealogica

### 5.10 A classe JVisualiza

- É a classe da janela que fica na direita, com a visualização da árvore

> Definição: src/gui/janelas/JanelaVisualiza.h
> 
> Implementação: src/gui/janelas/JanelaVisualiza.cpp

#### Métodos públicos

- Todos os da IJanela, em especial o Renderiza()

#### Métodos privados

- `std::string m_Nome = "Visualização"`: nome da janela
- `bool m_JanelaAberta = true`: controla se a janela está aberta

- `ArvoreRender m_aRender`: instância da classe ArvoreRender, com as funções de renderização da árvore

### 5.11 As utils

- Utilidades usadas no código de interface gráfica

> Localização: src/gui/utils

- `centralizaScroll`: centraliza o scroll no canvas de visualização
- `mouseDentroDeRect`: checa se o cursor do mouse está dentro de um rect (um rect é a forma geométrica de um Node). Serve para mostar o tooltip quando o mouse está sobre o node
- `truncaNome`: retorna o nome de uma pessoa truncado com "..." no final indicando que ele continua. Serve para o nome não ficar maior que o node.

### 5.12 A pasta theme

- `colors.cpp e .h`: contêm algumas cores no padrão da biblioteca ImGui que podem ser usadas na interface

- `font.h`: Fonte utilizada carregada na memória

- `StyleManager.cpp e .h`: Estilos de cores, arredondamentos, etc

### 5.13 A classe ExportaArvore

- É a classe que cuida da exportação e importação da árvore.

> Definição: src/backend/save/ExportaArvore.h
> 
> Implementação: src/backend/save/ExportaArvore.cpp

### 5.14 A classe Window

- É um wrapper de uma glfwWindow, para ficar mais organizado

> Definição: src/core/Window/Window.h
> 
> Implementação: src/core/Window/Window.cpp

## REFERÊNCIAS

- Ref. 1: [Arquitetura básica do core (src/core) do projeto inspirados nesse vídeo](https://youtu.be/rUxZ5N77M5E?si=_ugWfWMr2I2oKDth)

- Ref. 2: [Outro vídeo que inspirou a arquitetura do projeto](https://www.youtube.com/watch?v=U1BnzWX194Q)

- Ref. 3: [Outro vídeo usado como referencia na arquitetura das classes App, GuiLayers e dos demais paineis](https://www.youtube.com/watch?v=OYQp0GuoByM)

- Ref. 4: [Tutorial da biblioteca ImGui](https://www.youtube.com/watch?v=790aMkbsBm8)

- Ref. 5: [Video Aulas/Referência C++](https://youtube.com/playlist?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&si=oqrA-v2s35nsTVAZ) - Conceitos como os abordados nos vídeos 26-29, 35 e 43 da playlist foram utilizados, mas não foram vistos ainda em aula

## CRÉDITOS

- Tema: https://github.com/ocornut/imgui/issues/707#issuecomment-2832090282