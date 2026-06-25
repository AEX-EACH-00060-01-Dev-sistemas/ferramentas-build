# Aula 04: Arquitetura de Diretórios e Dependências Avançadas

## 1. Introdução

Até agora, todos os nossos arquivos (`.c`, `.h`, `.o` e o executável final) estavam misturados na mesma pasta. Para um projeto com 3 arquivos, isso não é um problema. Para um software real, isso é o caos.

O padrão da indústria para projetos em C/C++ é separar os arquivos por responsabilidade:

| Diretório | Conteúdo |
| --- | --- |
| `src/` | Arquivos-fonte `.c` |
| `include/` | Cabeçalhos `.h` |
| `build/` | Arquivos objeto `.o` gerados na compilação (temporários) |
| `bin/` | Executável final, pronto para ser rodado |

### O Problema que Resolvemos Aqui

Mover os arquivos para pastas diferentes **quebra o nosso Makefile da Aula 03**. O Make precisa aprender a procurar os `.c` em `src/` e salvar os `.o` em `build/`.

Além disso, vamos resolver de forma profissional o problema dos arquivos `.h`. Na aula passada, fizemos todos os `.o` dependerem de todos os `.h` — uma simplificação consciente. O GCC é inteligente o suficiente para ler o seu código e gerar um mapa exato de quais `.h` cada `.c` realmente usa. Vamos ensinar o Make a ler esse mapa.

---

## 2. Mão na Massa: O Makefile Definitivo

> 💡 **Lembrete:** A estrutura completa desta aula está em `exemplos/aula-04/`.

### Passo 1: Reorganizando a Casa

Crie as pastas e mova os arquivos do projeto para que a estrutura fique assim:

```text
aula-04/
├── Makefile
├── include/
│   └── mensagem.h
└── src/
    ├── main.c
    └── mensagem.c
```

> As pastas `build/` e `bin/` serão criadas automaticamente pelo Makefile — você não precisa criá-las à mão.

---

### Passo 2: Atualizando as Variáveis — Por que `patsubst` agora?

Na Aula 03, usávamos a substituição de sufixo `$(SRCS:.c=.o)` para converter `.c` em `.o`. Por que não podemos fazer o mesmo aqui?

Porque agora o **caminho mudou**, não só a extensão. Precisamos transformar `src/main.c` em `build/main.o` — trocar tanto a pasta quanto a extensão ao mesmo tempo. Para isso, usamos a função `patsubst` (*Pattern Substitution*):

```makefile
# Sintaxe: $(patsubst padrão_busca, padrão_troca, texto)

# Encontra todos os .c dentro de src/
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Transforma "src/main.c" em "build/main.o"
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
```

O `%` funciona igual à Pattern Rule: captura o *stem* (`main`, `mensagem`) e o reutiliza no padrão de saída.

---

### Passo 3: Criando os Diretórios — Order-Only Prerequisites

Precisamos garantir que as pastas `build/` e `bin/` existam antes de tentar salvar arquivos nelas. A forma idiomática de fazer isso no Make é com **Order-Only Prerequisites**.

Observe a diferença entre os dois tipos de pré-requisitos:

```makefile
# Pré-requisito normal: se "arquivo.h" for mais novo que o alvo, recompila
alvo: arquivo.h

# Order-only prerequisite: garante que "build/" exista, mas nunca força recompilação
alvo: | build/
```

O pipe `|` separa os pré-requisitos normais dos *order-only*. O Make vai garantir que `build/` exista antes de executar a regra, mas **não vai recompilar** o alvo só porque o diretório foi "modificado" (o que aconteceria a cada novo arquivo criado dentro dele).

Adicionamos também uma regra para criar os diretórios sob demanda:

```makefile
# Cria o diretório se ele não existir; o '@' oculta o comando do terminal
$(BUILD_DIR) $(BIN_DIR):
	@mkdir -p $@
```

E usamos o `|` na Pattern Rule para ligar o `.o` ao seu diretório:

```makefile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
```

---

### Passo 4: Dependências Automáticas com `-MMD` e `-MP`

Para que o GCC gere o mapa de dependências dos `.h`, adicionamos flags específicas ao `CFLAGS`. Vamos separá-las por propósito para ficar mais claro:

**Flag de busca — onde achar os `.h`:**
```makefile
-I$(INC_DIR)
```
Sem isso, o GCC não saberia que os cabeçalhos estão em `include/` e daria erro de "arquivo não encontrado".

**Flags de mapeamento — gerar o mapa de dependências:**
```makefile
-MMD -MP
```
- `-MMD`: instrui o GCC a criar um arquivo `.d` junto com cada `.o`. Esse arquivo contém uma regra do Make listando exatamente quais `.h` aquele `.c` inclui.
- `-MP`: cria regras vazias para cada `.h` listado. Isso evita que o Make quebre caso você delete um cabeçalho — sem essa flag, o Make tentaria reconstruir o `.h` deletado e falharia.

Por fim, precisamos dizer ao Make onde guardar os `.d` e como carregá-los:

```makefile
# Troca .o por .d para obter a lista de arquivos de dependência
DEPS = $(OBJS:.o=.d)

# Inclui os mapas gerados. O '-' na frente ignora erros se os .d ainda não existirem (primeira compilação)
-include $(DEPS)
```

---

### Passo 5: O Código Completo do Makefile Profissional

```makefile
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
```

---

### Passo 6: Testando — Veja o Make em Ação

**Compilação inicial:**

```
$ make
mkdir -p build
mkdir -p bin
gcc -Wall -Wextra -Iinclude -MMD -MP -c src/main.c -o build/main.o
gcc -Wall -Wextra -Iinclude -MMD -MP -c src/mensagem.c -o build/mensagem.o
gcc build/main.o build/mensagem.o -o bin/programa
```

Note que as pastas foram criadas automaticamente antes de qualquer compilação.

**Rodando `make` novamente sem alterar nada:**

```
$ make
make: 'bin/programa' is up to date.
```

**Alterando apenas `mensagem.c` e rodando `make`:**

```
$ touch src/mensagem.c
$ make
gcc -Wall -Wextra -Iinclude -MMD -MP -c src/mensagem.c -o build/mensagem.o
gcc build/main.o build/mensagem.o -o bin/programa
```

Só `mensagem.o` foi recompilado. O `main.o` não foi tocado.

**Alterando `mensagem.h` e rodando `make`:**

```
$ touch include/mensagem.h
$ make
gcc -Wall -Wextra -Iinclude -MMD -MP -c src/main.c -o build/main.o
gcc -Wall -Wextra -Iinclude -MMD -MP -c src/mensagem.c -o build/mensagem.o
gcc build/main.o build/mensagem.o -o bin/programa
```

Ambos os arquivos foram recompilados — porque ambos incluem `mensagem.h`, e o GCC mapeou isso no `.d`.

**Veja o que há dentro de `build/main.d`:**

```makefile
build/main.o: src/main.c include/mensagem.h

include/mensagem.h:
```

Isso é o mapa gerado pelo GCC. O Make lê esse arquivo via `-include $(DEPS)` e passa a saber exatamente de quais `.h` o `main.o` depende — sem você precisar escrever isso à mão.

**Limpeza:**

```
$ make clean
rm -rf build bin
```

As pastas inteiras são removidas, deixando o projeto em estado limpo.

---

## 3. Resumo / Cheat Sheet

| Recurso / Flag | Sintaxe | Para que serve? |
| --- | --- | --- |
| **patsubst** | `$(patsubst busca, troca, texto)` | Substitui padrões com `%` em uma lista. Necessário quando o caminho muda, não só a extensão. |
| **Order-Only Prerequisite** | `alvo: \| diretório` | Garante que o diretório exista antes da regra, sem forçar recompilação quando ele muda. |
| **mkdir -p** | `@mkdir -p $@` | Cria a pasta (e subpastas) se não existir. Silencioso com `@`. |
| **-I\<pasta\>** | `-I$(INC_DIR)` | Diz ao GCC onde procurar arquivos `.h`. |
| **-MMD** | `-MMD` | Gera um `.d` por `.c` com o mapa exato de dependências de cabeçalhos. |
| **-MP** | `-MP` | Cria regras vazias nos `.d` para evitar erros ao deletar um `.h`. |
| **-include** | `-include $(DEPS)` | Importa regras de outro arquivo. O `-` inicial ignora erros se o arquivo não existir ainda. |

---

## 4. Conclusão do Módulo e Próximos Passos

Parabéns! Você chegou ao fim do módulo de GNU Make. Você começou digitando comandos manuais longos e repetitivos no terminal — e agora tem em mãos um *template* de arquitetura profissional, capaz de gerenciar projetos complexos de forma totalmente automatizada.

### O Limite do Make

O Make é poderoso, mas tem uma limitação clássica: o nosso `Makefile` foi escrito pensando nas ferramentas e no sistema operacional que estamos usando agora. E se outra pessoa quiser compilar o mesmo código no Windows com o compilador MSVC, ou no macOS com o Xcode? Manter um `Makefile` diferente para cada plataforma seria um pesadelo.

É exatamente esse problema que resolve o nosso próximo módulo: o **CMake**.

O CMake atua um nível acima do Make. Ele não compila o código — ele analisa o ambiente onde está rodando e **gera** os Makefiles (ou projetos do Visual Studio, ou arquivos do Ninja) de forma automática para você.

Revise os arquivos em `exemplos/`, faça os exercícios propostos e nos vemos no módulo de CMake!