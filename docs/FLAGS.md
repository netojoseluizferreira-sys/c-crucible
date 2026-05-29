# 🛡️ Dicionário das Flags de Compilação

## O Paredão Atual (Sub-Bloco 04 em diante)

Todo código neste repositório é compilado com as seguintes flags:

\`\`\`bash
gcc -std=c99 -Wall -Wextra -Werror -pedantic \
    -Wshadow -Wconversion -Wsign-conversion \
    -Wformat=2 -Warray-bounds -Wmissing-prototypes \
    -Wnull-dereference -Wstrict-prototypes -Wold-style-definition \
    -Wcast-qual -Wwrite-strings -Wstrict-aliasing=3 \
    -fno-common \
    fonte.c -o binario
\`\`\`

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

\`\`\`bash
gcc -g -fsanitize=address,undefined fonte.c -o binario
\`\`\`

## Valgrind (Obrigatório a partir do Sub-Bloco 06)

\`\`\`bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./binario
\`\`\`

Resultado obrigatório: `All heap blocks were freed -- no leaks are possible`

---
Documentação mantida como parte do regime de qualidade do C Crucible.