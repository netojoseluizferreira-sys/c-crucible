# ⚙️ The C Crucible — Da Fundição ao Kernel

> *"Python me mostrou o que é possível. C me mostrou o que é real."*
>
> — Enkel, ourives do silício

[![C Standard](https://img.shields.io/badge/standard-C99%2FC17-blue)](https://en.wikipedia.org/wiki/C99)
[![Build](https://img.shields.io/badge/build-Wall_Wextra_Werror-red)](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html)
[![Memory](https://img.shields.io/badge/memory-Valgrind%20%7C%20Sanitizers-purple)](https://valgrind.org/)
[![License](https://img.shields.io/badge/license-MIT-green)](./LICENSE)
[![Progress](https://img.shields.io/badge/exerc%C3%ADcios-0%2F750-darkgrey)](./)

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

## 🗺️ O Plano Diretor — 750 Exercícios em 16 Semanas

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
│    [Bloco 1] Estruturas Lineares (200)                      │
│    Listas, pilhas, filas → "Eu moldo o fluxo de dados"      │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        ▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 2] Recursão & Complexidade (50)                   │
│    Backtracking, Big-O → "Eu penso antes de executar"       │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        ▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 3] Árvores & Hierarquias (150)                    │
│    BST, AVL, Heap → "Eu domino a hierarquia"                │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        ▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 4] Hashing (50)                                   │
│    Tabelas hash, colisões → "Eu transformo chaves em ouro"  │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        ▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 5] Grafos (100)                                   │
│    BFS, Dijkstra, Kruskal → "Eu conecto o mundo"            │
└───────────────────────┬─────────────────────────────────────┘
                        │
                        ▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 6] Estruturas Avançadas (30)                      │
│    Segment Tree, Union-Find → "Eu enfrento o competitivo"   │
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
| 🟢 **Fixação** | 150 | 20% | Memória muscular. Repetição sagrada. |
| 🔵 **Fácil** | 150 | 20% | Aplicação direta de conceitos. |
| 🟡 **Médio** | 187 | 25% | Combina dois ou mais conceitos. |
| 🟠 **Difícil** | 187 | 25% | Exige insight, modelos não óbvios. |
| 🔴 **Desafio** | 76 | 10% | Nível olimpíada. Prova de teoremas ou sistemas complexos. |
| **Total** | **750** | **100%** | |

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

### 🔗 BLOCO 1 — Estruturas Lineares (200)

> *"Dados fluem. Quem controla a estrutura, controla o sistema."*

| Estrutura | Qtd | Foco |
|:----------|:---|:-----|
| Arrays dinâmicos (vector) | 15 | Redimensionamento, inserção/remoção no meio, capacidade vs tamanho. |
| Lista Encadeada Simples | 30 | Inserção, remoção, busca, inversão iterativa/recursiva, detecção de ciclos (Floyd), merge de listas, merge sort. |
| Lista Duplamente Encadeada | 20 | Inserção/remoção, inversão, cursor, conversão para árvore binária. |
| Lista Circular | 10 | Inserção, remoção, problema de Josephus, ordenação circular. |
| Pilha (Stack) | 20 | Implementações com array e lista, avaliador de expressões posfixa/infixa, balanceamento de parênteses/HTML, undo/redo genérico. |
| Fila (Queue) | 20 | Fila com array circular, fila com lista, BFS básico (preparação para grafos), fila de prioridade simples. |
| Fila Circular | 10 | Buffer circular, ring buffer para streaming. |
| Deque | 10 | Duas implementações (lista dupla e array circular), sliding window máximo. |
| Exercícios Integradores | 65 | Misturas de pilha+fila, simulação de cache LRU, preparação para hashing. |

> **🏗️ Projeto: `textedit` — Editor de Texto em Terminal**
>
> Editor minimalista estilo Vim, com buffer duplamente encadeado de linhas, undo/redo com pilha, busca com lista, realocação dinâmica. Salva e carrega arquivos. *O teu primeiro software de verdade.*

---

### 🔁 BLOCO 2 — Recursão & Complexidade (50)

> *"Pensar antes de agir. Medir antes de otimizar."*

| Tema | Qtd |
|:-----|:---|
| Recursão básica (fatorial, Fibonacci) | 5 |
| Recursão em arrays e strings | 10 |
| Backtracking (N-rainhas, labirinto, sudoku) | 15 |
| Análise de complexidade (Big-O, Ω, Θ) | 20 |

> **🏗️ Projeto: `solver` — Resolvedor de Labirintos**
>
> Lê labirinto de arquivo, resolve com DFS recursivo, exibe caminho. Implementa também força bruta para Sudoku. Relatório de complexidade para cada algoritmo.

---

### 🌳 BLOCO 3 — Árvores & Hierarquias (150)

> *"Tudo é hierarquia. Quem entende a árvore, entende o sistema."*

| Estrutura | Qtd | Foco |
|:----------|:---|:-----|
| Árvore Binária | 20 | Travessias (pré, em, pós), altura, contagem, espelhamento, simetria, reconstrução. |
| BST | 25 | Inserção, remoção, busca, predecessor/sucessor, k-ésimo, validação. |
| AVL | 20 | Rotações simples/duplas, inserção e remoção com balanceamento, testes de estresse. |
| Red-Black Tree | 15 | Inserção, remoção, propriedades, comparação empírica com AVL. |
| Heap (min/max) | 25 | Heapify, heapsort, fila de prioridade, heap de medianas, k-th largest. |
| Trie | 15 | Inserção, busca, autocomplete, contagem de prefixos, compressão. |
| Exercícios Cruzados | 30 | Converter lista → árvore, árvore → array, heap em árvore, etc. |

> **🏗️ Projeto: `filesys` — Sistema de Arquivos em Memória**
>
> Simula um sistema de arquivos hierárquico com inodes, diretórios, caminhos, permissões. Comandos: `mkdir`, `touch`, `ls`, `cd`, `rm -r`. Tudo manipulado com árvores. *O teu próprio "mini kernel" de armazenamento.*

---

### 🧪 BLOCO 4 — Hashing (50)

> *"A função hash é o coração; a resolução de colisões é a alma."*

| Tema | Qtd |
|:-----|:---|
| Funções hash (djb2, sdbm, murmur) | 5 |
| Encadeamento separado | 15 |
| Endereçamento aberto (linear, quadrático, duplo hash) | 15 |
| Hash dinâmica (rehash, fator de carga) | 5 |
| Aplicações (cache LRU, conjunto, mapa) | 10 |

> **🏗️ Projeto: `dict` — Dicionário e Corretor Ortográfico**
>
> Dicionário baseado em Trie e Hash, carrega wordlist, busca palavras, sugere correções (distância de Levenshtein com poda). Compara performance entre as estruturas.

---

### 🕸️ BLOCO 5 — Grafos (100)

> *"O mundo é um grafo. Agora eu posso navegá-lo."*

| Algoritmo | Qtd | Foco |
|:----------|:---|:-----|
| Representação (matriz, lista adj.) | 10 | Conversão entre formatos. |
| BFS | 15 | Menor caminho em arestas não ponderadas, componentes conexas. |
| DFS | 15 | Detecção de ciclos, ordenação topológica, componentes fortemente conexas (Kosaraju/Tarjan). |
| Dijkstra | 20 | Com e sem heap, caminho mínimo, restauração de caminho. |
| Kruskal & Prim | 15 | Árvore geradora mínima, Union-Find como auxiliar. |
| Algoritmos extras | 10 | Bellman-Ford, Floyd-Warshall, grafos com pesos negativos. |
| Problemas integrados | 15 | Rede de colaboração, mapa de voos, labirinto. |

> **🏗️ Projeto: `metromap` — Planejador de Rotas de Metrô**
>
> Carrega mapa de metrô de arquivo, calcula rota mais curta (Dijkstra), rota com menos baldeações (BFS em grafo transformado), estações alcançáveis (DFS). Interface interativa no terminal.

---

### ⚡ BLOCO 6 — Estruturas Avançadas & Competitivas (30)

> *"Para problemas que exigem o melhor de ti."*

| Estrutura | Qtd |
|:----------|:---|
| Union-Find (Disjoint Set) | 10 |
| Segment Tree | 10 |
| Fenwick Tree (BIT) | 10 |

> **🏗️ Projeto: `rangequery` — Motor de Consultas em Intervalos**
>
> Carrega array massivo e responde queries de soma/máximo/mínimo em intervalo, com atualizações pontuais e lazy propagation. Compara Segment Tree vs Fenwick vs Força Bruta.

---

### 👑 PROJETO FINAL: `kernel_sim` — Simulador de Kernel Minimalista

> *"A coroação. O Magnum Opus."*

Componentes:
- **Gerenciador de processos:** lista circular com estados (pronto, executando, bloqueado)
- **Escalonador:** heap de prioridades com aging
- **Sistema de arquivos virtual:** árvore n-ária com inodes
- **Tabela de páginas:** hash table simulando TLB
- **Grafo de dependências:** módulos que comunicam entre si

Tudo em C puro. Sem bibliotecas externas. Compilado com o Paredão. *Este projeto resume 4 anos de Ciência da Computação em um único binário.*

---

## 🛡️ O Regime de Compilação — O Paredão

Nenhum código neste repositório é aceito sem passar pelo paredão. Cada flag é um portão que só se abre se o código for digno.

### Flags de Guerra — Linha de Comando

```bash
gcc -std=c99 -Wall -Wextra -Werror -pedantic \
    -Wshadow -Wconversion -Wsign-conversion \
    -Wformat=2 \
    fonte.c -o binario
```

### Dicionário das Bandeiras

| Flag | Significado | Por que é inegociável |
|:-----|:------------|:----------------------|
| `-std=c99` | Força o padrão ISO C99 | Garante portabilidade. Sem extensões GNU. |
| `-Wall` | Habilita a maioria dos warnings | Primeira linha de defesa. É o mínimo. |
| `-Wextra` | Warnings adicionais | Cobre o que `-Wall` deixou passar. |
| `-Werror` | **Transforma warnings em erros** | Disciplina máxima. Se o compilador chiou, NÃO COMPILA. |
| `-pedantic` | Rejeita código fora do padrão ISO | Código puro, sem depender de compilador específico. |
| `-Wshadow` | Proíbe variáveis com mesmo nome em escopos aninhados | Evita o clássico "por que essa variável não mudou?". |
| `-Wconversion` | Proíbe conversões implícitas entre tipos | Cada bit importa. `int` → `unsigned int`? Explícito ou nada. |
| `-Wsign-conversion` | Conversões entre signed/unsigned | Complemento do anterior. Segurança de tipos. |
| `-Wformat=2` | Verifica `printf`/`scanf` | `printf("%d", "abc")` não passa. |

### Code Runner — VS Code

Configuração injetada no `settings.json`:

```json
"c": "gcc -std=c99 -Wall -Wextra -Werror -pedantic -Wshadow -Wconversion -Wsign-conversion -Wformat=2 $fileName -o $fileNameWithoutExt && echo '=== Sem warnings ===' && $dir$fileNameWithoutExt"
```

Ao pressionar `Ctrl+Alt+N`, o Code Runner limpa a tela, salva o arquivo, compila com o paredão, e se tudo passar, exibe `=== Sem warnings ===` e executa.

### Sanitizers — Os Sensores de Corrupção

Quando a memória feder a podre, aciono os sanitizers:

```bash
gcc -std=c99 -g -fsanitize=address,undefined fonte.c -o binario
./binario
```

- **AddressSanitizer** (`-fsanitize=address`): detecta buffer overflow, uso após `free`, vazamentos.
- **UndefinedBehaviorSanitizer** (`-fsanitize=undefined`): overflow com sinal, divisão por zero, shift excessivo.

### Valgrind — O Juiz Final

```bash
valgrind --leak-check=full --show-leak-kinds=all ./binario
```

A última linha deve ser:

```
All heap blocks were freed -- no leaks are possible
```

Se não aparecer isso, o exercício **não está terminado**.

---

## 📊 Progresso Atual

| Bloco | Exercícios | Projeto | Status |
|:------|:----------|:--------|:-------|
| 0 — Fundição | 170 | `memalloc` | 🔄 **Em Execução** |
| 1 — Lineares | 200 | `textedit` | ⬛ Planejado |
| 2 — Recursão | 50 | `solver` | ⬛ Planejado |
| 3 — Árvores | 150 | `filesys` | ⬛ Planejado |
| 4 — Hashing | 50 | `dict` | ⬛ Planejado |
| 5 — Grafos | 100 | `metromap` | ⬛ Planejado |
| 6 — Avançadas | 30 | `rangequery` | ⬛ Planejado |
| **Final** | — | `kernel_sim` | ⬛ Planejado |
| **TOTAL** | **750 / 750** | | ⬜ 0% |

---

## 🧠 Por que C? Por que Agora?

> *"Frameworks passam. O hardware fica."*

Programar em C sem abstrações:
- **Força a compreensão da memória:** stack, heap, endereçamento, alinhamento.
- **Expõe o custo real das operações:** cada laço, cada chamada, cada indireção de ponteiro.
- **Conecta software e hardware:** o C é o dialeto comum entre o kernel e o ferro.
- **Constrói disciplina permanente:** os hábitos adquiridos com `-Wall -Wextra -Werror` se refletem em qualquer outra linguagem.

Após 750 exercícios neste regime, abrir o código-fonte do CPython, do Linux ou de qualquer banco de dados não será um choque — será como entrar em casa.

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
```
