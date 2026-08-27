# Changelog

## [0.7.0] — 2026-08-27
### Adicionado
- 15 exercícios do sub-bloco 07 — Arquivos e I/O (136 a 150)
  - Gravador de texto, leitor, copiador, contador de linhas
  - Escrita e leitura binária, tamanho de arquivo com fseek/ftell
  - Atualização seletiva, bufferização personalizada, CSV manual
  - Comparador, inversor binário, extrator de trecho, concatenador, log, frequência
  - Destaques: Inversor de arquivo binário com malloc e dois ponteiros, bufferização com setvbuf
- Reflexão: conceitos de arquivos (bufferização, append, acesso aleatório) são universais,
  mas sintaxe específica de C é ruído para quem não seguirá em C
- **Reformulação do projeto**: Blocos 1 a 6 reestruturados (750 → 775 exercícios)

## [0.6.0] — 2026-08-23
### Adicionado
- 25 exercícios do sub-bloco 06 — Alocação Dinâmica (111 a 135)
  - malloc, calloc, realloc, free, memcpy, memmove
  - Detecção e correção de vazamentos, double free, dangling pointers
  - Array de ponteiros para strings, matriz dinâmica, cópia profunda
  - Realloc com loop, realloc para trocar tipo, struct com array dinâmico
  - Array genérico com void* e memcpy
  - CRUD de arrays dinâmicos com 10 slots (exercício 135)
- Intervalo de 3 meses entre commits devido a perda de foco e procrastinação,
  combatidas constantemente até a retomada da rotina.

## [0.5.0] — 2026-06-02
### Adicionado
- 33 exercícios do sub-bloco 05 — Ponteiros (076 a 106, 109 e 110)
  - Aritmética de ponteiros, void*, casts, ponteiros para ponteiros (até nível triplo)
  - Ponteiros para funções, callbacks, tabelas de funções, qsort
  - Arrays 2D acessados via ponteiro simples, alinhamento de structs, const com ponteiros
  - Destaques: A Forja de Funções (callback), A Tumba dos Alinhamentos, A Aniquilação do Silício (filtro + transformação + ordenação via função)
- Exercícios 107 (Dança Macabra – lista duplamente encadeada) e 108 (Portal do Caos – árvore de decisão) adiados para o Bloco 1 por envolverem estruturas ainda não consolidadas
- Paredão expandido: -Wcast-qual, -Wwrite-strings, -Wstrict-aliasing=3, -fno-common

## [0.4.0] — 2026-05-29
### Adicionado
- 20 exercícios do sub-bloco 04 — Arrays e Strings (056 a 075)
  - Arrays unidimensionais e multidimensionais, aritmética de ponteiros com arrays
  - Strings C (null-terminated): strlen, strcpy, strcmp, strcat, strchr, strstr recriadas do zero
  - Palíndromo com ponteiros, inversão in-place, concatenação manual
  - Destaques: Multiplicação de matrizes 2×3 por 3×2, busca em array com ponteiros
- Pausa entre 18 e 29/05 por motivos acadêmicos (provas, projetos, simulados)

## [0.3.0] — 2026-05-18
### Adicionado
- 20 exercícios do sub-bloco 03 — Funções e Escopo (036 a 055)
  - Passagem por valor e referência, procedimentos (void), recursão
  - Funções com ponteiros, escopo local vs global, funções variádicas
  - Destaques: Torre de Hanói, Swap com XOR, MDC recursivo

## [0.2.0] — 2026-05-13
### Adicionado
- 15 exercícios do sub-bloco 02 — Controle de Fluxo (021 a 035)

## [0.1.0] — 2026-05-12
### Adicionado
- README completo, estrutura de diretórios, Makefile, documentação
- Primeiros 20 exercícios do Bloco 0

---
"Mantenha um registro. O futuro você agradecerá."