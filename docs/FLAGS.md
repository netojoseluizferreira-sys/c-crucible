# 🛡️ Dicionário das Flags de Compilação

## O Paredão

Todo código neste repositório é compilado com as seguintes flags:

\`\`\`bash
gcc -std=c99 -Wall -Wextra -Werror -pedantic \
    -Wshadow -Wconversion -Wsign-conversion \
    -Wformat=2 \
    fonte.c -o binario
\`\`\`

## Glossário

| Flag | Tradução | O que faz |
|------|----------|-----------|
| `-std=c99` | Standard C99 | Força o padrão ISO C99. Sem extensões GNU. |
| `-Wall` | Warnings All | Habilita a maioria dos warnings. |
| `-Wextra` | Warnings Extra | Warnings adicionais que `-Wall` não cobre. |
| `-Werror` | Warnings as Errors | **Transforma qualquer warning em erro de compilação.** |
| `-pedantic` | Pedantic Mode | Rejeita código que não siga estritamente o padrão ISO. |
| `-Wshadow` | Warning Shadow | Proíbe variável local com mesmo nome de global/parâmetro. |
| `-Wconversion` | Warning Conversion | Proíbe conversões implícitas entre tipos diferentes. |
| `-Wsign-conversion` | Warning Sign Conversion | Específico para conversões signed ↔ unsigned. |
| `-Wformat=2` | Warning Format Level 2 | Verifica se argumentos do `printf`/`scanf` batem com a string de formato. |

## Sanitizers (Sob Demanda)

\`\`\`bash
gcc -g -fsanitize=address,undefined fonte.c -o binario
\`\`\`

- **AddressSanitizer:** Detecta buffer overflow, uso após `free`, memory leaks.
- **UndefinedBehaviorSanitizer:** Detecta overflow com sinal, divisão por zero, shift inválido.

## Valgrind

\`\`\`bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./binario
\`\`\`

Resultado obrigatório: `All heap blocks were freed -- no leaks are possible`

---
Documentação mantida como parte do regime de qualidade do C Crucible.