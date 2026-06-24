# --- Variáveis ---
CC      = gcc
CFLAGS  = -Wall -Wextra -g

# Busca dinâmica de arquivos
SRCS    = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJS    = $(SRCS:.c=.o)
EXEC    = programa

# --- Targets Especiais ---
# Avisa o Make que 'all' e 'clean' não são arquivos reais
.PHONY: all clean

# A primeira regra é a padrão (executada quando você só digita 'make')
all: $(EXEC)

# --- Regras de Compilação ---

# Linkagem: junta todos os .o e gera o executável
# $^ = todos os pré-requisitos (main.o mensagem.o ...)
$(EXEC): $(OBJS)
	$(CC) $^ -o $@

# Pattern Rule: compila qualquer .c em .o
# Recompila também se qualquer .h for alterado
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJS) $(EXEC)