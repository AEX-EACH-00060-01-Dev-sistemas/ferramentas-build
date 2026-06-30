# Exercício 3: O Padrão Ouro dos Makefiles (Difícil)

## Objetivo
Você agora é o mantenedor de um motor de simulação física! O projeto cresceu e os arquivos não podem mais ficar todos bagunçados na mesma pasta. 

Organize o projeto da seguinte criando as pastas:
- `src/` : Contendo os arquivos fonte (`main.c`, `physics.c`)
- `include/` : Contendo os cabeçalhos (`physics.h`)

Sua tarefa é criar um `Makefile` profissional que:
1. Compile os arquivos `.c` da pasta `src/` e salve os arquivos `.o` gerados em uma nova pasta chamada `build/`.
2. Gere o executável chamado `simulator` dentro de uma nova pasta chamada `bin/`.
3. Crie as pastas `build/` e `bin/` automaticamente caso elas não existam.
4. Utilize a técnica de "Dependências Automáticas" (flags `-MMD -MP`) para que o Make recompile os arquivos `.c` automaticamente caso o arquivo `physics.h` seja alterado, sem precisarmos listar os cabeçalhos manualmente nas regras.

## Requisitos
- Use as funções `wildcard` para buscar todos os `.c` na pasta `src/`.
- Use `patsubst` para transformar a lista de arquivos `.c` em uma lista de arquivos `.o` na pasta `build/`.
- Adicione a flag `-I./include` no gcc para ele saber onde achar os `.h`.
- Adicione as flags `-MMD -MP` para gerar os arquivos `.d` (dependências).

---

<details>
<summary><b>Dica 1: Como buscar arquivos e trocar nomes? (Clique para expandir)</b></summary>

Para listar todos os arquivos `.c` da pasta `src`:
```makefile
SRC = $(wildcard src/*.c)
```

Para transformar essa lista (ex: `src/main.c`) em uma lista de objetos na pasta `build` (ex: `build/main.o`):
```makefile
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
```
</details>

<details>
<summary><b>Dica 2: Como criar as pastas automaticamente? (Clique para expandir)</b></summary>

Na regra que compila os arquivos objeto, você pode usar o comando `mkdir -p` (o `@` no começo esconde o comando no terminal):
```makefile
build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@
```
Faça o mesmo para a pasta `bin` na regra do executável.
</details>

<details>
<summary><b>Dica 3: A Magia das Dependências (Clique para expandir)</b></summary>

Adicione `-MMD -MP` na sua variável `CFLAGS`. Isso fará o GCC gerar arquivos `.d` na pasta `build`. No final do seu `Makefile`, você deve importar esses arquivos assim:
```makefile
-include $(OBJ:.o=.d)
```
</details>

---

<details>
<summary><b>Resposta Esperada (Clique para ver a solução completa)</b></summary>

Seu `Makefile` profissional deve ficar muito parecido com este:

```makefile
# Variáveis do Compilador
CC = gcc
# -Iinclude diz ao gcc onde achar os .h
# -MMD -MP gera os arquivos de dependência .d
CFLAGS = -Wall -Wextra -Iinclude -MMD -MP -g

# Diretórios
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

# Arquivos
# Busca todos os .c em src/
SRC = $(wildcard $(SRC_DIR)/*.c)
# Substitui src/arquivo.c por build/arquivo.o
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
# Define os arquivos de dependência (.d)
DEP = $(OBJ:.o=.d)

# Alvo final
TARGET = $(BIN_DIR)/simulator

# Regra Principal
all: $(TARGET)

# Criação do Executável
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Regra de compilação dos arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Inclui os arquivos de dependência gerados pelo GCC
-include $(DEP)

.PHONY: all clean
```
</details>