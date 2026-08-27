# ⚙️ The C Crucible — Da Fundição ao Kernel

[![C Standard](https://img.shields.io/badge/standard-C99%2FC17-blue)](https://en.wikipedia.org/wiki/C99)
[![Build](https://img.shields.io/badge/build-Wall_Wextra_Werror-red)](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html)
[![Memory](https://img.shields.io/badge/memory-Valgrind%20%7C%20Sanitizers-purple)](https://valgrind.org/)
[![License](https://img.shields.io/badge/license-MIT-green)](./LICENSE)
[![Progress](https://img.shields.io/badge/exerc%C3%ADcios-133%2F775-darkgrey)](./)

---

## 🧬 Filosofia do Projeto

> *"A maioria programa para que o código funcione. Eu programo para entender por que cada bit está onde está."*

**The C Crucible** não é um repositório de exercícios. É o **diário de bordo de uma descida ao metal**. Aqui, cada linha de código é uma declaração de guerra contra a ignorância, cada `malloc` é um voto de responsabilidade, cada `segfault` resolvido é uma cicatriz que o sistema operacional me deixou — e que eu agradeço.

### Os Cinco Mandamentos do Ourives

1. **Zero warnings, sempre.** Se o compilador falou, o código está errado. Ponto final.
2. **Memória é sagrada.** Nenhum byte alocado sem destino. Nenhum ponteiro órfão. `valgrind` limpo é a lei.
3. **O "porquê" > o "como".** Comentários explicam a decisão de engenharia, não a sintaxe. O futuro eu agradecerá.
4. **Sem atalhos.** `goto` é permitido — se tu souberes exatamente por que o está usando.
5. **Beleza no código.** Um algoritmo correto também pode ser elegante. A elegância é respeito pelo leitor.

---

## 🗺️ O Plano Diretor — 775 Exercícios em 16 Semanas

A jornada simula um aprendizado **geológico**: do átomo ao sistema. Cada bloco é uma camada de rocha que só se forma depois que a anterior está sólida.

### A Descida ao Metal

```
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 0] Fundição do Ferro (170)                        │
│    Tipos, ponteiros, memória → "Eu controlo cada byte"      │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        ▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 1] Estruturas Lineares e Memória Dinâmica (130)   │
│    Listas, pilhas, filas, ownership → "Eu moldo o fluxo"    │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        ▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 2] Raciocínio Algorítmico, Recursão, Ordenação (80)│
│    Backtracking, Big-O, ordenação → "Eu penso antes"        │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        ▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 3] Árvores e Hierarquias (120)                    │
│    BST, AVL, Heap, Trie → "Eu domino a hierarquia"          │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        ▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 4] Tabelas Hash, Conjuntos e Mapas (65)           │
│    Hash, colisões, rehash → "Eu transformo chaves em ouro"  │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        ▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 5] Grafos e Algoritmos em Grafos (100)            │
│    BFS, DFS, Dijkstra, MST → "Eu conecto o mundo"           │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        ▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 6] Alocadores, Layout e Engenharia (115)          │
│    Arenas, pools, profiling → "Eu sou o engenheiro"         │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        ▼
┌─────────────────────────────────────────────────────────────┐
│    [Projeto Final] kernel_sim                               │
│    O Magnum Opus → "Eu sou o arquiteto da máquina"          │
└─────────────────────────────────────────────────────────────┘
```

### Distribuição por Nível de Dificuldade

| Nível | Quantidade | Percentual | Objetivo |
|:------|:----------|:-----------|:---------|
| 🟢 **Fixação** | 155 | 20% | Memória muscular. Repetição sagrada. |
| 🔵 **Fácil** | 155 | 20% | Aplicação direta de conceitos. |
| 🟡 **Médio** | 194 | 25% | Combina dois ou mais conceitos. |
| 🟠 **Difícil** | 194 | 25% | Exige insight, modelos não óbvios. |
| 🔴 **Desafio** | 77 | 10% | Nível olimpíada. Prova de teoremas ou sistemas complexos. |
| **Total** | **775** | **100%** | |

---

## 🔨 Os Blocos de Forja

Cada bloco contém exercícios e um **projeto integrador** que consolida o aprendizado em um sistema real.

### 🪨 BLOCO 0 — Fundição do Ferro (170)

> *"Se você não entende ponteiros, você não entende C."*

| Subtema | Qtd | O que é forjado |
|:--------|:---|:----------------|
| Tipos, variáveis, operadores | 20 | Declarações, overflow/underflow, promoções implícitas, operadores bitwise em signed/unsigned. |
| Controle de fluxo (`if`, `switch`, loops) | 15 | Loops aninhados, Duff's device, loops sem corpo, `goto` controlado. |
| Funções e escopo | 20 | Passagem por valor e por referência (com ponteiros), recursão simples, pilha de chamada, funções variádicas. |
| Arrays e strings | 20 | Arrays unidimensionais/multidimensionais, aritmética de ponteiros, strings null-terminated, recriação da `string.h`. |
| Ponteiros (o diabo) | 35 | `void*`, ponteiros para função, `char **argv`, alinhamento, casts, diferença array vs ponteiro. |
| Alocação dinâmica | 25 | `malloc`/`free`/`realloc`, `memcpy`, `memmove`, double-free, dangling pointers, vazamentos. |
| Arquivos e I/O | 15 | `fopen`, `fread`, `fwrite`, `fseek`, streams binários vs texto, bufferização. |
| Pré-processador | 10 | Macros, `#ifdef`, include guards, compilação condicional, token pasting. |
| Depuração | 10 | GDB, breakpoints, watchpoints, análise de core dumps. |

> **🏗️ Projeto: `memalloc` — Alocador de Memória Customizado**
>
> Implementa um alocador próprio usando `sbrk`/`mmap` (simulado), com gerenciamento de blocos livres, coalescência e detecção de double-free. Inclui relatório de fragmentação e performance. *Nada como construir sua própria `malloc` para nunca mais usá-la de forma leviana.*

---

### 🔗 BLOCO 1 — Estruturas Lineares e Memória Dinâmica (130)

> *"Dados fluem. Quem controla a estrutura e a memória, controla o sistema."*

| Estrutura | Qtd | Foco |
|:----------|:---|:-----|
| Arrays dinâmicos (vector) | 15 | Redimensionamento, inserção/remoção no meio, capacidade vs tamanho, estratégias de crescimento, `realloc` seguro. |
| Lista Encadeada Simples | 30 | Inserção, remoção, busca, inversão iterativa/recursiva, detecção de ciclos (Floyd), merge de listas, merge sort, ownership de nós. |
| Lista Duplamente Encadeada | 20 | Inserção/remoção, inversão, cursor, conversão para árvore binária, remoção sem ponteiro anterior. |
| Lista Circular | 10 | Inserção, remoção, problema de Josephus, ordenação circular, destruição segura. |
| Pilha (Stack) | 20 | Implementações com array e lista, avaliador de expressões posfixa/infixa, balanceamento, undo/redo, chamadas de função simuladas. |
| Fila (Queue) | 20 | Fila com array circular, fila com lista, BFS básico, fila de prioridade simples, análise de desperdício. |
| Deque | 10 | Duas implementações (lista dupla e array circular), sliding window máximo. |
| Integração e debugging de memória | 15 | Misturas de pilha+fila, simulação de cache LRU, análise de vazamentos, double free, dangling pointers, heap corruption. |
| Reforço e extensões | 10 | Estruturas lineares aplicadas, combinação de múltiplas estruturas, listas com nós sentinelas, otimização. |

> **🏗️ Projeto: `textedit` — Editor de Texto em Terminal**
>
> Editor minimalista estilo Vim, com buffer duplamente encadeado de linhas, undo/redo com pilha, busca com lista, realocação dinâmica. Salva e carrega arquivos. *O teu primeiro software de verdade.*

---

### 🔁 BLOCO 2 — Raciocínio Algorítmico, Recursão e Ordenação (80)

> *"Pensar antes de agir. Medir antes de otimizar."*

| Tema | Qtd |
|:-----|:---|
| Recursão básica e stack | 10 |
| Recursão em strings e arrays | 15 |
| Backtracking (N-rainhas, labirinto, sudoku) | 20 |
| Algoritmos de ordenação (Bubble, Merge, Quick, etc.) | 20 |
| Análise de complexidade integrada (Big-O, Ω, Θ) | 15 |

> **🏗️ Projeto: `solver` — Resolvedor de Labirintos e Sudoku**
>
> Lê labirinto de arquivo, resolve com DFS recursivo, exibe caminho. Implementa também força bruta para Sudoku. Relatório de complexidade e análise de memória da stack.

---

### 🌳 BLOCO 3 — Árvores e Hierarquias (120)

> *"Tudo é hierarquia. Quem entende a árvore, entende o sistema."*

| Estrutura | Qtd | Foco |
|:----------|:---|:-----|
| Árvore Binária | 20 | Travessias, altura, contagem, espelhamento, simetria, reconstrução. |
| BST | 25 | Inserção, remoção, busca, predecessor/sucessor, k-ésimo, validação. |
| AVL | 20 | Rotações simples/duplas, inserção e remoção com balanceamento, testes de estresse. |
| Red-Black Tree | 10 | Inserção, remoção, propriedades, comparação empírica com AVL. |
| Heap (min/max) | 20 | Heapify, heapsort, fila de prioridade, heap de medianas, k-th largest. |
| Trie | 15 | Inserção, busca, autocomplete, contagem de prefixos, compressão. |
| Integração e conversões | 10 | Converter lista → BST, heap em array, árvore para lista dupla. |

> **🏗️ Projeto: `filesys` — Sistema de Arquivos em Memória**
>
> Simula um sistema de arquivos hierárquico com diretórios, arquivos, caminhos e permissões. Comandos: `mkdir`, `touch`, `ls`, `cd`, `rm -r`. Usa árvore n-ária. *O teu próprio "mini kernel" de armazenamento.*

---

### 🧪 BLOCO 4 — Tabelas Hash, Conjuntos e Mapas (65)

> *"A função hash é o coração; a resolução de colisões é a alma."*

| Tema | Qtd |
|:-----|:---|
| Funções hash (djb2, sdbm, murmur, FNV) | 8 |
| Encadeamento separado | 15 |
| Endereçamento aberto (linear, quadrático, duplo hash) | 15 |
| Hash dinâmica (rehash, fator de carga) | 10 |
| Aplicações (cache LRU, conjunto, mapa) | 12 |
| Extensões e otimizações | 5 |

> **🏗️ Projeto: `dict` — Dicionário e Corretor Ortográfico**
>
> Dicionário baseado em Trie e Hash, carrega wordlist, busca palavras, sugere correções (distância de Levenshtein com poda). Compara performance entre as estruturas.

---

### 🕸️ BLOCO 5 — Grafos e Algoritmos em Grafos (100)

> *"O mundo é um grafo. Agora eu posso navegá-lo."*

| Algoritmo | Qtd | Foco |
|:----------|:---|:-----|
| Representação (matriz, lista adj.) | 15 | Conversão entre formatos, densos vs esparsos. |
| BFS | 20 | Menor caminho em arestas não ponderadas, componentes conexas, bipartição. |
| DFS | 20 | Detecção de ciclos, ordenação topológica, componentes fortemente conexas. |
| Dijkstra | 20 | Com e sem heap, caminho mínimo, restauração de caminho. |
| Árvore geradora mínima (Kruskal/Prim) | 15 | MST, Union-Find como auxiliar. |
| Algoritmos extras | 5 | Bellman-Ford, Floyd-Warshall, pesos negativos. |
| Problemas integrados | 10 | Rede de colaboração, mapa de voos, labirinto. |

> **🏗️ Projeto: `metromap` — Planejador de Rotas de Metrô**
>
> Carrega mapa de metrô de arquivo, calcula rota mais curta (Dijkstra), rota com menos baldeações (BFS em grafo transformado), estações alcançáveis (DFS). Interface interativa no terminal.

---

### ⚡ BLOCO 6 — Alocadores, Layout de Memória e Engenharia de Sistemas (115)

> *"O verdadeiro engenheiro não apenas usa a memória — ele a projeta."*

| Tema | Qtd |
|:-----|:---|
| Layout de memória e representação | 15 |
| Alocadores customizados (pools, arenas, freelists) | 25 |
| Debugging avançado de memória | 10 |
| Modularização e APIs | 10 |
| Performance e otimização | 15 |
| **Projeto Final Integrador** (`c_forge`) | 40 |

> **🏗️ Projeto Final do Bloco: `c_forge` — Sistema de Gerenciamento de Dados com Cache e Alocadores**
>
> Um sistema completo (mini banco de dados chave-valor ou servidor de cache) que integra alocadores customizados, estruturas de dados otimizadas, APIs bem projetadas e análise de performance. É a prova final de que dominas a memória e a engenharia de software em C.

---

### 👑 PROJETO FINAL: `kernel_sim` — Simulador de Kernel Minimalista (opcional, mas glorioso)

> [!warning] Simulador minimalista de kernel em C puro: gerenciador de processos (lista circular), escalonador (heap), sistema de arquivos virtual (árvore), tabela de páginas (hash), grafo de dependências. O teu _Magnum Opus_. Coloca no GitHub e faz os recrutadores chorarem.

---

# 🛡️ Dicionário das Flags de Compilação

## O Paredão Atual (Sub-Bloco 04 em diante)

Todo código neste repositório é compilado com as seguintes flags:

```bash
gcc -std=c99 -Wall -Wextra -Werror -pedantic \
    -Wshadow -Wconversion -Wsign-conversion \
    -Wformat=2 -Warray-bounds -Wmissing-prototypes \
    -Wnull-dereference -Wstrict-prototypes -Wold-style-definition \
    -Wcast-qual -Wwrite-strings -Wstrict-aliasing=3 \
    -fno-common \
    fonte.c -o binario
```

## Evolução do Paredão

| Sub-Bloco | Flags Adicionadas |
|:----------|:------------------|
| 01 — Tipos, Variáveis e Operadores | `-std=c99 -Wall -Wextra -Werror -pedantic` |
| 03 — Funções e Escopo | `-Wshadow -Wconversion -Wsign-conversion -Wformat=2 -Wmissing-prototypes` |
| 04 — Arrays e Strings | `-Warray-bounds` |
| 05 — Ponteiros | `-Wnull-dereference -Wstrict-prototypes -Wold-style-definition -Wcast-qual -Wwrite-strings -Wstrict-aliasing=3 -fno-common` |
| 06 — Alocação Dinâmica | *(mantido)* |

## Glossário

| Flag | O que faz |
|------|----------|
| `-std=c99` | Força o padrão ISO C99. Sem extensões GNU. |
| `-Wall` | Habilita a maioria dos warnings. |
| `-Wextra` | Warnings adicionais. |
| `-Werror` | Transforma warnings em erros. |
| `-pedantic` | Rejeita código fora do padrão ISO. |
| `-Wshadow` | Proíbe variáveis com mesmo nome em escopos aninhados. |
| `-Wconversion` | Proíbe conversões implícitas entre tipos. |
| `-Wsign-conversion` | Conversões entre signed/unsigned. |
| `-Wformat=2` | Verifica `printf`/`scanf`. |
| `-Warray-bounds` | Detecta acesso fora dos limites de arrays. |
| `-Wmissing-prototypes` | Exige protótipos para todas as funções. |
| `-Wnull-dereference` | Alerta sobre possível dereferência de ponteiro nulo. |
| `-Wstrict-prototypes` | Exige protótipos completos (ex: `int f(void)`). |
| `-Wold-style-definition` | Proíbe definições de funções no estilo K&R. |
| `-Wcast-qual` | Alerta quando cast remove `const`. |
| `-Wwrite-strings` | Força strings literais como `const char[]`. |
| `-Wstrict-aliasing=3` | Regras rigorosas de aliasing. |
| `-fno-common` | Evita múltiplas definições de variáveis globais. |

## Sanitizers (Sob Demanda)

```bash
gcc -g -fsanitize=address,undefined fonte.c -o binario
```

## Valgrind (Obrigatório a partir do Sub-Bloco 06)

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./binario
```

Resultado obrigatório: `All heap blocks were freed -- no leaks are possible`

---
## 📊 Progresso Atual

| Bloco | Exercícios | Projeto | Status |
|:------|:----------|:--------|:-------|
| 0 — Fundição | 148 / 170 | `memalloc` | 🔄 **Em Andamento** 🟩🟩🟩🟩🟩🟩🟩🟩🟩⬜ 87% |
| 1 — Lineares e Memória | 0 / 130 | `textedit` | ⬛ Planejado |
| 2 — Raciocínio Algorítmico | 0 / 80 | `solver` | ⬛ Planejado |
| 3 — Árvores | 0 / 120 | `filesys` | ⬛ Planejado |
| 4 — Hash | 0 / 65 | `dict` | ⬛ Planejado |
| 5 — Grafos | 0 / 100 | `metromap` | ⬛ Planejado |
| 6 — Alocadores e Engenharia | 0 / 115 | `c_forge` | ⬛ Planejado |
| **Final** | — | `kernel_sim` | ⬛ Planejado |
| **TOTAL** | **148 / 775** | | 🟩🟩🟩🟩🟩🟩🟩🟩⬜⬜ 19% |
---

## 🧠 Por que C? Por que Agora?

> *"Frameworks passam. O hardware fica."*

Programar em C sem abstrações:
- **Força a compreensão da memória:** stack, heap, endereçamento, alinhamento.
- **Expõe o custo real das operações:** cada laço, cada chamada, cada indireção de ponteiro.
- **Conecta software e hardware:** o C é o dialeto comum entre o kernel e o ferro.
- **Constrói disciplina permanente:** os hábitos adquiridos com `-Wall -Wextra -Werror` se refletem em qualquer outra linguagem.

Após 775 exercícios neste regime, abrir o código-fonte do CPython, do Linux ou de qualquer banco de dados não será um choque — será como entrar em casa.

---

## 📚 Apêndice: Ferramentas, Livros e Influências

### Ferramentas do Ofício
- **Compilador:** GCC (MinGW no Windows, nativo no Linux)
- **Depurador:** GDB
- **Analisador de memória:** Valgrind
- **Editor:** VS Code com Code Runner e Error Lens
- **Versionamento:** Git + GitHub (cada exercício aprovado é um commit)

### Livros de Cabeceira
- *The C Programming Language* — Kernighan & Ritchie (a bíblia)
- *Understanding and Using C Pointers* — Richard Reese
- *Expert C Programming: Deep C Secrets* — Peter van der Linden
- *Algorithms in C* — Robert Sedgewick

### Influências
- Alan Turing, por me ensinar que o pensamento pode ser máquina.
- Bjarne Stroustrup, pela frase que é um lembrete diário do perigo e da responsabilidade.
- Cada professor que me olhou com ceticismo e me deu mais um motivo para continuar.

---

> *"C makes it easy to shoot yourself in the foot; C++ makes it harder, but when you do, it blows your whole leg off."*
>
> — Bjarne Stroustrup
>
> Este repositório é meu treinamento para nunca, jamais, puxar o gatilho. E se um dia eu precisar fazê-lo, que seja com consciência absoluta do estrago.

---

**Forjado por Enkel (Neto) © 2026**
*"Do átomo ao kernel. Sem atalhos. Sem warnings. Sem desculpas."*