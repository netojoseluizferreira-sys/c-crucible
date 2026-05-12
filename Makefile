# ⚙️ The C Crucible — Makefile Global
# Todas as flags de guerra aplicadas a todos os exercícios e projetos

CC       = gcc
CFLAGS   = -std=c99 -Wall -Wextra -Werror -pedantic
CFLAGS  += -Wshadow -Wconversion -Wsign-conversion -Wformat=2
LDFLAGS  =
DEBUG_FLAGS = -g -fsanitize=address,undefined
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

# Busca recursivamente todos os .c e compila
SOURCES = $(shell find . -name "*.c" -not -path "./projeto-*/*")
TARGETS = $(SOURCES:.c=.out)

# Compila todos os fontes encontrados
all: $(TARGETS)

%.out: %.c
	@echo "[BUILD] $<"
	@$(CC) $(CFLAGS) $< -o $@
	@echo "[OK]   Compilado sem warnings"

# Compila com símbolos de debug e sanitizers
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all
	@echo "[DEBUG] Compilado com AddressSanitizer e UBSan"

# Executa Valgrind em um binário específico
valgrind-%: %.out
	@echo "[VALGRIND] $<"
	@$(VALGRIND) ./$<

# Limpa todos os binários
clean:
	@echo "[CLEAN] Removendo binários..."
	@find . -name "*.out" -delete
	@find . -name "*.o"   -delete
	@echo "[CLEAN] Concluído"

.PHONY: all debug clean