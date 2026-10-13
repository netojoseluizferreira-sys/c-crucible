# ⚙️ The C Crucible — Engenharia de Sistemas e Estruturas de Dados em C

[![C Standard](https://img.shields.io/badge/standard-C99%2FC17-blue)](https://en.wikipedia.org/wiki/C99)
[![Build](https://img.shields.io/badge/build-Wall_Wextra_Werror-red)](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html)
[![Memory](https://img.shields.io/badge/memory-Valgrind%20%7C%20Sanitizers-purple)](https://valgrind.org/)
[![License](https://img.shields.io/badge/license-MIT-green)](./LICENSE)
[![Progress](https://img.shields.io/badge/exerc%C3%ADcios-215%2F745-darkgrey)](./PROGRESS.md)

Repositório estruturado de desenvolvimento, análise assintótica e implementação de estruturas de dados e algoritmos de baixo nível em linguagem C pura (padrão ISO C99/C17).

O projeto é constituído por 745 exercícios práticos e 8 projetos integradores desenvolvidos do zero, focando na gestão manual de memória, análise de custo de hardware, ciclo de vida estrito de ponteiros e compilação sem tolerância a avisos (*warnings as errors*).

---

## 🧬 Filosofia e Diretrizes de Engenharia

> *"A maioria programa para que o código apenas funcione. O objetivo deste projeto é compreender e controlar o custo real de cada instrução, alocação e indireção de memória."*

1. **Zero Warnings (`-Werror`):** Se o compilador emite um aviso, o código contém uma fragilidade estrutural e deve ser corrigido antes da integração.
2. **Ciclo de Vida e Ownership:** Toda a região alocada na heap (`malloc`, `calloc`) possui um dono explícito responsável pela sua desalocação (`free`). Ausência de fugas (*zero-leak policy*) e ponteiros órfãos (*dangling pointers*), validados continuamente via Valgrind e sanitizadores.
3. **Comentários Arquiteturais:** A documentação interna foca em decisões de engenharia, complexidade de tempo/espaço e invariantes estruturais, e não em sintaxe óbvia.
4. **Implementação do Zero:** Construção de primitivas e algoritmos a partir dos fundamentos antes do consumo de bibliotecas de alto nível.
5. **Previsibilidade:** Código modular, encapsulado com ponteiros opacos e alinhamento de memória consciente.

---

## 🗺️ Mapa de Evolução Arquitetural

A progressão parte da sintaxe elementar e avança em direção à engenharia de sistemas operacionais:


```

┌─────────────────────────────────────────────────────────────┐
│    [Bloco 0] Fundição do Ferro (150)                        │
│    Fundação: ponteiros, arrays, structs, malloc/free e I/O  │
└───────────────────────┬─────────────────────────────────────┘
│
▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 1] Estruturas Lineares e Memória Dinâmica (150)   │
│    Ponteiro como ferramenta: ownership de nós, lifetime     │
└───────────────────────┬─────────────────────────────────────┘
│
▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 2] Raciocínio Algorítmico e Ordenação (80)        │
│    Ponteiro na call stack: recursão, backtracking, Big-O    │
└───────────────────────┬─────────────────────────────────────┘
│
▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 3] Árvores e Hierarquias (120)                    │
│    Ownership recursivo: travessias, balanceamento (AVL/RB)  │
└───────────────────────┬─────────────────────────────────────┘
│
▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 4] Tabelas Hash, Conjuntos e Mapas (65)           │
│    Alocação de buckets, tratamento de colisões e rehash     │
└───────────────────────┬─────────────────────────────────────┘
│
▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 5] Grafos e Algoritmos em Grafos (105)            │
│    Estruturas compostas: matrizes, listas de adj., caminhos │
└───────────────────────┬─────────────────────────────────────┘
│
▼
┌─────────────────────────────────────────────────────────────┐
│    [Bloco 6] Alocadores, Layout e Engenharia (75)           │
│    Mecanismo de sistema: arenas, pools, cache e profiling   │
└───────────────────────┬─────────────────────────────────────┘
│
▼
┌─────────────────────────────────────────────────────────────┐
│    [Projeto Final] kernel_sim                               │
│    Simulador de núcleo: escalonamento, memória virtual, VFS │
└─────────────────────────────────────────────────────────────┘

```

---

## 📊 Progresso Atual

| Bloco | Escopo Técnico | Exercícios | Projeto Integrador | Status |
|:------|:---------------|:-----------|:-------------------|:-------|
| **0 — Fundição** | Fundamentos, Memória e I/O | 150 / 150 | `memalloc` | ✅ **Concluído** 🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩 100% |
| **1 — Lineares** | Listas, Pilhas, Filas, Deques | 65 / 150 | `textedit` | 🔄 **Em Andamento** 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ 43% |
| **2 — Algoritmos** | Recursão, Backtracking, Ordenação | 0 / 80 | `solver` | ⬛ Planeado |
| **3 — Árvores** | Binárias, BST, AVL, Heaps, Tries | 0 / 120 | `filesys` | ⬛ Planeado |
| **4 — Hash** | Dispersão, Colisões, Caches | 0 / 65 | `dict` | ⬛ Planeado |
| **5 — Grafos** | BFS/DFS, Dijkstra, MST, Redes | 0 / 105 | `metromap` | ⬛ Planeado |
| **6 — Alocadores** | Arenas, Pools, Otimização | 0 / 75 | `c_forge` | ⬛ Planeado |
| **Final** | Simulador de Kernel Minimalista | — | `kernel_sim` | ⬛ Planeado |
| **TOTAL** | | **215 / 745** | | 🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜ **29%** |

---

## 🔨 Detalhamento dos Blocos e Projetos

### BLOCO 0 — Fundição do Ferro (150 exercícios) ✅ CONCLUÍDO

* **Tipos, variáveis e operadores (20):** Declarações, overflow/underflow, promoções implícitas, operadores bitwise em tipos signed e unsigned.
* **Controle de fluxo (15):** Laços aninhados, laços sem corpo, Duff's device e saltos estruturados com `goto`.
* **Funções e escopo (20):** Passagem por valor e por referência via ponteiros, recursão simples, pilha de chamadas e funções variádicas.
* **Arrays e strings (20):** Arrays unidimensionais/multidimensionais, aritmética de ponteiros com arrays, strings terminadas em nulo (`\0`) e recriação da `string.h`.
* **Ponteiros (35):** Aritmética de endereços, ponteiros para ponteiros (`T**`), ponteiros de funções, `void*`, alinhamento de memória, casts e `char **argv`.
* **Alocação dinâmica (25):** `malloc`, `calloc`, `realloc`, `free`, `memcpy`, `memmove`, tratamento de double-free, dangling pointers e fugas de memória.
* **Arquivos e I/O (15):** `fopen`, `fread`, `fwrite`, `fseek`, streams binários vs texto e gestão de bufferização.

> **🏗️ Projeto Integrador: `memalloc` — Alocador Dinâmico Customizado**  
> Alocador em C puro sobre memória simulada, implementando divisão de blocos (*splitting*), coalescência bidirecional com blocos vizinhos livres, prevenção de double-free e geração de relatórios de fragmentação.  
> 🔗 Repositório: [github.com/netojoseluizferreira-sys/memalloc](https://github.com/netojoseluizferreira-sys/memalloc)

---

### BLOCO 1 — Estruturas Lineares e Memória Dinâmica (150 exercícios) 🔄

* **Arrays Dinâmicos (15):** Redimensionamento com crescimento geométrico, capacidade vs tamanho, inserção/remoção com deslocamento, custo amortizado e realocação segura.
* **Listas Encadeadas Simples (30):** Operações básicas, inversão iterativa/recursiva, algoritmo de Floyd (lebre e tartaruga) para deteção de ciclos, merge sort em listas e ownership de nós.
* **Listas Duplamente Encadeadas (20):** Manipulação de vínculos bidirecionais (`ant` e `prox`), inserções/remoções $O(1)$ com cabeça e cauda, cursor e remoção arbitrária com 4 ponteiros.
* **Listas Circulares (10):** Estruturas em anel, resolução do problema de Josephus, concatenação e desalocação segura sem recursão infinita.
* **Pilhas (20):** Implementações em array e lista encadeada, avaliador de expressões pós-fixas/infixas, balanceamento de parênteses e mecanismos genéricos de undo/redo.
* **Filas (20):** Filas encadeadas e buffers circulares em array com aritmética modular, filas de prioridade simples e análise de desperdício de memória.
* **Deques (10):** Implementações com lista dupla e array circular, operações em ambas as extremidades e janelas deslizantes (*sliding window*).
* **Integração, Debugging e Reforço (25):** Resolução de bugs com Valgrind/ASan, heap corruption, implementação de listas com nós sentinelas e simulação de cache LRU linear.

> **🏗️ Projeto Integrador: `textedit` — Editor de Texto em Terminal**  
> Buffer de edição textual modelado com listas duplamente encadeadas para linhas de texto, pilhas dedicadas para histórico de undo/redo, realocação dinâmica de caracteres e persistência em ficheiros.

---

### BLOCO 2 — Raciocínio Algorítmico, Recursão e Ordenação (80 exercícios)

* **Recursão Básica e Stack (10):** Rastreamento manual da stack de execução, tempo de vida de variáveis locais e prevenção de *stack overflow*.
* **Recursão em Strings e Arrays (15):** Busca binária recursiva, permutações, combinações, subconjuntos e avaliação de profundidade de memória.
* **Backtracking (20):** Exploração do espaço de estados (N-Rainhas, Sudoku, labirintos, coloração de mapas), restrições, restauração de invariantes e podas (*pruning*).
* **Algoritmos de Ordenação (20):** Implementações do zero: Bubble, Selection, Insertion, Merge Sort (análise de memória auxiliar) e Quick Sort (partições de Lomuto/Hoare); estabilidade e ordenação in-place vs out-of-place.
* **Análise de Complexidade Integrada (15):** Aplicação de notações assintóticas ($O$, $\Omega$, $\Theta$), resolução de relações de recorrência (Teorema Mestre básico) e trade-offs de tempo/espaço.

> **🏗️ Projeto Integrador: `solver` — Resolvedor de Labirintos e Sudoku**  
> Motor de resolução automática por backtracking e DFS, contendo instrumentação para cálculo de chamadas recursivas, profundidade da pilha e relatório de complexidade.

---

### BLOCO 3 — Árvores e Hierarquias (120 exercícios)

* **Árvores Binárias (20):** Travessias em profundidade (pré, em, pós-ordem) e largura (em nível), altura, simetria e reconstrução de árvores a partir de percursos.
* **Árvores Binárias de Busca - BST (25):** Inserção, busca, remoção com tratamento de nó com dois filhos, predecessor/sucessor e validação de invariantes.
* **Árvores Balanceadas AVL (20):** Fator de balanceamento, rotações simples e duplas à esquerda/direita, inserção e remoção com garantia de altura $O(\log N)$.
* **Árvores Rubro-Negras (10):** Invariantes de coloração, recolorações, rotações e comparação empírica de performance com AVL.
* **Heaps Binários (20):** Max-Heap e Min-Heap indexados em vetor contíguo, rotinas de `heapify`, filas de prioridade e Heap Sort.
* **Tries (15):** Árvores de prefixo para busca léxica, autocomplete, compressão básica e contagem de ocorrências.
* **Integração e Conversões (10):** Conversão de listas ordenadas em BSTs balanceadas, heaps em vetores e árvores em listas duplas.

> **🏗️ Projeto Integrador: `filesys` — Sistema de Arquivos em Memória**  
> Simulação de um sistema de arquivos hierárquico em RAM estruturado sobre uma árvore n-ária (filho-irmão), suportando navegação e comandos Unix (`mkdir`, `touch`, `ls`, `cd`, `rm -r`).

---

### BLOCO 4 — Tabelas Hash, Conjuntos e Mapas (65 exercícios)

* **Funções Hash (8):** Implementação e teste de uniformidade e dispersão de funções clássicas (`djb2`, `sdbm`, `murmur`, `FNV-1a`).
* **Encadeamento Separado (15):** Resolução de colisões via listas dinâmicas de buckets, fator de carga ideal e análise de pior caso.
* **Endereçamento Aberto (15):** Sondagem linear (*linear probing*), quadrática e dispersão dupla (*double hashing*); marcação por *tombstones* e agrupamentos primário/secundário.
* **Hash Dinâmica (10):** Redimensionamento automático com rehash completo de entradas, monitorização de fator de carga e expansão/contração de memória.
* **Aplicações e Otimizações (17):** Implementação de mapas, conjuntos, contadores de frequência, tabelas universais e Cache LRU (tabela hash + lista dupla).

> **🏗️ Projeto Integrador: `dict` — Dicionário e Corretor Ortográfico**  
> Sistema de consulta léxica integrando tabelas hash e estruturas trie para comparação de velocidade e consumo de memória, com cálculo de distância de edição (Levenshtein) com poda para correção de digitação.

---

### BLOCO 5 — Grafos e Algoritmos em Grafos (105 exercícios)

* **Representação (15):** Matrizes de adjacência (grafos densos) versus listas de adjacência dinâmicas (grafos esparsos); direcionados e não-direcionados.
* **Busca em Largura - BFS (20):** Caminhos mínimos em arestas unitárias, componentes conexos, cálculo de distâncias e teste de bipartição.
* **Busca em Profundidade - DFS (20):** Deteção de ciclos, ordenação topológica, tempos de descoberta/finalização e componentes fortemente conexos (Tarjan/Kosaraju).
* **Caminhos Mínimos com Pesos (25):** Algoritmo de Dijkstra implementado com Min-Heap versus array linear, e algoritmo de Bellman-Ford para grafos com custos negativos.
* **Árvores Geradoras Mínimas - MST (15):** Algoritmos de Kruskal e Prim integrados à estrutura de conjuntos disjuntos (*Disjoint-Set / Union-Find*).
* **Algoritmos em Redes e Problemas Integrados (10):** Fechamento transitivo, algoritmo de Floyd-Warshall e modelagem de rotas e dependências.

> **🏗️ Projeto Integrador: `metromap` — Planejador de Rotas de Metrô**  
> Roteador interativo em terminal baseado em grafos ponderados que calcula caminhos mais curtos em distância (Dijkstra) e rotas com menor quantidade de transbordos (BFS).

---

### BLOCO 6 — Alocadores, Layout de Memória e Engenharia de Sistemas (75 exercícios)

* **Layout de Memória e Representação (15):** Segmentos de processo (Stack, Heap, Data, BSS, Text), alinhamento de tipos, padding de compilador, endianness e inspeção de bytes via GDB.
* **Alocadores Customizados (25):** Implementação de arenas sequenciais (*bump allocators* com reset), memory pools de tamanho fixo e listas livres (*freelists*) sobre memória pré-alocada.
* **Debugging Avançado (10):** Diagnóstico sistemático de use-after-free, corrupção de stack/heap, vazamentos ocultos e estouros de limites com Valgrind, ASan e UBSan.
* **Modularização e APIs (10):** Encapsulamento estrito com ponteiros opacos (*opaque pointers*), ponteiros de funções para callbacks e separação de contratos públicos (`.h`) da implementação (`.c`).
* **Performance e Otimização de Hardware (15):** Padrões de acesso à memória com alta localidade espacial/temporal, minimização de falhas de cache L1/L2/L3, uso do qualificador `restrict` e profiling com `perf`/`gprof`.

> **🏗️ Projeto Integrador Obrigatório: `c_forge` — Servidor de Dados com Cache e Alocadores**  
> Sistema de armazenamento chave-valor de alta performance que opera sobre pools de memória customizados e estruturas de dados otimizadas, eliminando a sobrecarga de chamadas de sistema repetitivas.

---

### 👑 PROJETO FINAL: `kernel_sim` — Simulador de Kernel Minimalista

> Projeto integrador final unificando todos os conceitos da trilha:
> * **Gerenciador de Processos:** Fila circular de tarefas com blocos de controle de processo (PCB).
> * **Escalonador:** Fila de prioridades com Heap binário para controle cooperativo/preemptivo.
> * **Gerência de Memória Virtual:** Simulação de paginação e tradução de endereços via tabelas de dispersão.
> * **Sistema de Arquivos:** VFS em memória suportado por árvores n-árias.
> * **Resolução de Dependências:** Grafo de recursos e tarefas com análise de bloqueios (*deadlocks*).

---

## 🛡️ Políticas de Compilação e Qualidade

Todo o código é compilado com as diretivas estritas do GCC:

```bash
gcc -std=c99 -Wall -Wextra -Werror -pedantic \
    -Wshadow -Wconversion -Wsign-conversion \
    -Wformat=2 -Warray-bounds -Wmissing-prototypes \
    -Wnull-dereference -Wstrict-prototypes -Wold-style-definition \
    -Wcast-qual -Wwrite-strings -Wstrict-aliasing=3 \
    -fno-common \
    fonte.c -o binario

```

### Análise Dinâmica e Auditoria

* **Sanitizadores (Compilação para Testes):**
```bash
gcc -std=c99 -g -fsanitize=address,undefined fonte.c -o binario_san

```


* **Valgrind (Auditoria de Memória Obrigatória):**
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./binario

```


Critério de aprovação: `All heap blocks were freed -- no leaks are possible`.

---

## 📚 Referências Bibliográficas

* **The C Programming Language** — Brian W. Kernighan & Dennis M. Ritchie
* **Understanding and Using C Pointers** — Richard Reese
* **Expert C Programming: Deep C Secrets** — Peter van der Linden
* **Algorithms in C (Parts 1-4 & Part 5)** — Robert Sedgewick
* **Computer Systems: A Programmer's Perspective (CS:APP)** — Randal E. Bryant & David R. O'Hallaron

---

**Autor:** José Luiz Ferreira Neto (Enkel) © 2026
