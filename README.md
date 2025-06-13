# Estrutura de Dados (ADS)

Este repositório é dedicado ao curso de **Estrutura de Dados** do curso de Análise e Desenvolvimento de Sistemas (ADS). Ele serve como um arquivo central para todos os materiais de estudo, códigos-fonte e projetos desenvolvidos ao longo da disciplina, utilizando principalmente as linguagens **C e C++**.

O conteúdo está organizado em pastas que correspondem aos períodos da faculdade, como `First Period` e `Third Period`, refletindo a progressão dos estudos.

-----

## 🏗️ Estruturas Implementadas

O foco principal deste repositório é a implementação e o estudo prático das estruturas de dados fundamentais. Abaixo estão as principais estruturas que você encontrará aqui:

* **Listas:** Implementações de listas lineares, incluindo variações como listas simplesmente encadeadas, duplamente encadeadas e circulares. São a base para estruturas mais complexas.
* **Pilhas (Stacks):** Estruturas que operam no princípio LIFO (Last-In, First-Out). Ideais para resolver problemas como inversão de sequências e gerenciamento de chamadas de funções.
* **Filas (Queues):** Estruturas que seguem o princípio FIFO (First-In, First-Out). Usadas em cenários de gerenciamento de tarefas, processos e em algoritmos de busca em largura.
* **Árvores (Trees):** Estruturas hierárquicas não lineares, com implementações prováveis de Árvores Binárias de Busca (BST). São essenciais para buscas eficientes, organização de dados hierárquicos e algoritmos de ordenação.

-----

## 📂 Estrutura do Repositório

O repositório está organizado da seguinte forma para facilitar a navegação:

``` Bash
.
├── 📁 First Period/
│   └── (Projetos e códigos do primeiro período)
│
├── 📁 Third Period/
│   └── (Projetos e códigos do terceiro período)
│
├── .gitignore
└── README.md
```

-----

## ⚙️ Como Compilar e Executar

Os projetos foram desenvolvidos em **C e C++** e não possuem um sistema de build unificado. Você precisará de um compilador como o **GCC (para C) ou G++ (para C++)** para compilar os arquivos manualmente.

### Passo a Passo

1. **Clone o Repositório:**

    ```bash
    git clone https://github.com/NicolasRaf/Estrutura_de_Dados-ADS.git
    ```

2. **Navegue até a Pasta do Projeto:**

    ```bash
    cd Estrutura_de_Dados-ADS/Third\ Period/NomeDoProjeto/
    ```

3. **Compile o Código:**

    * Para um projeto em **C**:

    ```bash
    gcc -o executavel main.c funcoes.c
    ```

    * Para um projeto em **C++**:

    ```bash
    g++ -o executavel main.cpp funcoes.cpp
    ```

4. **Execute o Programa**  

    ```bash
    ./executavel
    ```