# --- Configurações do Compilador ---
CC     = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR) -MMD -MP

# --- Diretórios ---
SRC_DIR   = src
INC_DIR   = include
BUILD_DIR = build
BIN_DIR   = bin

# --- Arquivos ---
EXEC = $(BIN_DIR)/programa
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

# --- Targets Especiais ---
.PHONY: all clean

all: $(EXEC)

# --- Regras de Diretórios ---
# Uma regra única para criar qualquer diretório sob demanda
$(BUILD_DIR) $(BIN_DIR):
	@mkdir -p $@

# --- Regras de Compilação ---

# Linkagem: $(BIN_DIR) como order-only garante que a pasta exista
$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CC) $^ -o $@

# Pattern Rule: compila .c em .o
# '| $(BUILD_DIR)' garante que a pasta exista sem forçar recompilação
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Inclui os mapas de dependência gerados pelo GCC
-include $(DEPS)

# Limpeza: apaga as pastas inteiras
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)