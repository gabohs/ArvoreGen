# Aplicativo de Árvore Genealógica

- Projeto feito por Emanuel e Gabriel para a disciplina de Linguagem de Programação do curso de ADS no IFRS

## Enunciado do Trabalho

```

Objetivo: Implementar um sistema em C++ para representar e manipular uma árvore genealógica, aplicando estruturas de dados hierárquicas, como árvores, ou listas e filas.

Implementar um sistema em C++ para representar e manipular uma árvore genealógica, aplicando estruturas de dados hierárquicas, como árvores, ou listas e filas.

#### Funcionalidades obrigatórias

- Adicionar pessoa (nome, ano de nascimento, gênero).

- Definir relação entre duas pessoas (pai/mãe e filho).

- Exibir descendentes e ascendentes de uma pessoa.

- Listar toda a árvore a partir de um ancestral principal.

- Buscar pessoa por nome.

#### Funcionalidades opcionais

- Exibir nível de parentesco entre duas pessoas (distância em nós).

- Contar o número de descendentes diretos e indiretos.

- Mostrar gerações separadas por nível.

- Gravar e carregar a árvore de um arquivo texto (opcional, não obrigatório).
```

---

## Como Rodar o Projeto

- **Visando facilitar o processo para o professor, foi feito o upload da pasta build com o executável já buildado aqui no repositório.**

Então, faça o download do projeto, [clicando aqui!](https://github.com/gabohs/ArvoreGen/archive/refs/heads/main.zip)

se o link não funcionar, clique no botão azul `Code` e depois em `Download ZIP`

![DownloadBotao](imagens/botaoDownload.png)

ou, clone com o git rodando no terminal o comando:

```sh
git clone --recursive https://github.com/gabohs/ArvoreGen.git
```
<small> <small>OBS: --recursive é necessário para clonar também o repositório do GLFW (biblioteca usada para gerenciar o contexto OpenGL), que é tratado como um submódulo neste projeto</small> </small>

Após isso, vá até:

> build\Debug\Debug\
 
ou, se quiser a versão release:

> build\Release\Release\

e rode **ArvoreGen.exe**

### Rodando do zero

> [!WARNING] REQUISITOS
> Para realizar o processo de build do zero é necessário ter [CMake](https://cmake.org/download/) instalado

1. Faça o download do projeto como mostrado acima.
2. Rode os scripts .bat em ordem: (**s1**; depois o **s2**; e depois rode o **s3** desejado)

## Estrutura do Projeto

Aqui ser

### 

## Recursos que foram usados no desenvolvimento

- [Arquitetura básica do core (src/core) do projeto inspirados nesse vídeo](https://youtu.be/rUxZ5N77M5E?si=_ugWfWMr2I2oKDth)

- [Outro vídeo que inspirou a arquitetura do projeto](https://www.youtube.com/watch?v=U1BnzWX194Q)

-[Outro vídeo usado como referencia na arquitetura das classes App, GuiLayers e dos demais paineis](https://www.youtube.com/watch?v=OYQp0GuoByM)

- [Tutorial da biblioteca ImGui](https://www.youtube.com/watch?v=790aMkbsBm8)

- [Video Aulas C++](https://youtube.com/playlist?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&si=oqrA-v2s35nsTVAZ) - Conceitos como os abordados nos vídeos 26-29, 35 e 43 da playlist foram utilizados, mas não foram vistos ainda em aula

### Créditos

- Estilo (cores): https://github.com/ocornut/imgui/issues/707#issuecomment-2832090282