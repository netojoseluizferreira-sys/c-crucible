# 📊 Registro de Progresso — The C Crucible (755 exercícios)

> **Progresso geral:** 165 / 755 (21,9%)  
> **Bloco atual:** Bloco 1 — Estruturas Lineares e Memória Dinâmica (em andamento)

---

## Bloco 0 — Fundição do Ferro (150 exercícios) ✅ CONCLUÍDO

| Data | Exercícios | Tema | Notas |
|------|-----------|------|-------|
| 12/05/2026 | 001-020 | Tipos, variáveis e operadores | Primeira fornada completa. Bitwise ainda é abstrato. Swap sem auxiliar e MSB foram os mais difíceis. Compilou tudo limpo. |
| 13/05/2026 | 021-035 | Controle de fluxo | If-else, switch, loops aninhados, goto, loop sem corpo. Duff's Device foi substituído por Classificador de Dígitos (decisão madura). Collatz e continue/break fecharam o bloco. Ponteiros ainda não entraram, mas a base de controle está sólida. |
| 18/05/2026 | 036-055 | Funções e Escopo | Recursão dominada: fatorial, Fibonacci, MDC, Hanói. Swap com XOR e proteção de ponteiros. Variádica implementada sem stdarg. A pilha de chamada já não assusta mais. |
| 29/05/2026 | 056-075 | Arrays e Strings | Arrays unidimensionais, multidimensionais, aritmética de ponteiros. Strings dominadas: strlen, strcpy, strcmp, strcat, strchr, strstr recriadas. Palíndromo com ponteiros, inversão in-place. Sub-bloco concluído com fluência. |
| | | | *Pausa entre 18 e 29/05 por motivos acadêmicos (provas, projetos, simulados). Retomada com força total.* |
| 01-02/06/2026 | 076-106, 109-110 | Ponteiros | A descida ao Inferno do Silício. Ponteiros simples, duplos, triplos, void*, casts, ponteiros para função, tabelas de callbacks, qsort. Arrays 2D acessados via ponteiro simples. Alinhamento de structs, const com ponteiros. Exercícios 107 (Dança Macabra – lista duplamente encadeada) e 108 (Portal do Caos – árvore de decisão) pulados por envolverem estruturas ainda não consolidadas — serão revisitados no Bloco 1 com a devida profundidade. O Paredão dos ponteiros (-Wcast-qual, -Wwrite-strings, -Wstrict-aliasing=3) foi domado. |
| 23/08/2026 | 111-135 | Alocação Dinâmica | malloc, calloc, realloc, free, memcpy, memmove. Detecção e correção de vazamentos, double free, dangling pointers. Array de ponteiros para strings, matriz dinâmica, cópia profunda. Realloc com loop, realloc para trocar tipo, struct com array dinâmico. Array genérico com void* e memcpy. CRUD de arrays dinâmicos com 10 slots (exercício 135). Intervalo de 3 meses entre commits devido a perda de foco e procrastinação, combatidas constantemente até a retomada da rotina. |
| 26-27/08/2026 | 136-150 | Arquivos e I/O | Gravador de texto, leitor, copiador, contador de linhas. Escrita e leitura binária. Tamanho de arquivo com fseek/ftell. Atualização seletiva. Bufferização personalizada. CSV manual. Comparador. Inversor binário. Extrator de trecho. Concatenador. Log com append. Frequência de caracteres. Correção de warnings -Wsign-conversion e -Wconversion. Reflexão: conceitos de bufferização e append são universais, mas sintaxe específica de C é ruído para quem não seguirá em C. Sub-bloco concluído. |
| 28/08/2026 | — | Mudança de ementa | Bloco 0 reduzido de 170 para 150 exercícios. Pré-processador (151-160) e Depuração (161-170) removidos por serem específicos demais de C — foco será em ED e algoritmos, não em particularidades de sistemas embarcados. Exercícios 107 e 108 permanecem adiados para o Bloco 1. |
| 29/08/2026 | — | Projeto `memalloc` | Início do projeto integrador do Bloco 0. Desenvolvimento em paralelo com o Bloco 1. |

---

## Bloco 1 — Estruturas Lineares e Memória Dinâmica (130 exercícios)

| Data | Exercícios | Tema | Notas |
|------|-----------|------|-------|
| 09-10/09/2026 | 151-165 | Arrays Dinâmicos (Vector) | O bloco mais chato até agora. Vector com capacidade/tamanho, realocação com realloc, inserção no final/início, inserção ordenada com deslocamento, remoção condicional com callback, merge de ordenados, busca binária para inserção, map, reduce, split de strings, Vector de structs, ordenação com comparator (qsort), mini banco de dados em memória com busca/remoção/ordenação (quicksort manual). Destaques: implementação manual do quicksort com pivô em struct, uso consistente de callbacks para padronizar inserção, reflexão sobre por que arrays são contíguos e por que isso torna certas operações caras. Sensação final: alívio por terminar e clareza sobre por que listas encadeadas existem. |

---

## Bloco 2 — Raciocínio Algorítmico, Recursão e Ordenação (80 exercícios)

| Data | Exercícios | Tema | Notas |
|------|-----------|------|-------|
| | | | |

---

## Bloco 3 — Árvores e Hierarquias (120 exercícios)

| Data | Exercícios | Tema | Notas |
|------|-----------|------|-------|
| | | | |

---

## Bloco 4 — Tabelas Hash, Conjuntos e Mapas (65 exercícios)

| Data | Exercícios | Tema | Notas |
|------|-----------|------|-------|
| | | | |

---

## Bloco 5 — Grafos e Algoritmos em Grafos (100 exercícios)

| Data | Exercícios | Tema | Notas |
|------|-----------|------|-------|
| | | | |

---

## Bloco 6 — Alocadores, Layout de Memória e Engenharia de Sistemas (115 exercícios)

| Data | Exercícios | Tema | Notas |
|------|-----------|------|-------|
| | | | |

---

## Projeto Final — `kernel_sim`

| Data | Atividade | Status |
|------|-----------|--------|
| | | |