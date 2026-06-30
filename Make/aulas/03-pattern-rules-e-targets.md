# Aula 03: Pattern Rules e Targets Especiais — O Makefile Dinâmico

## 1. Introdução

Na Aula 02, melhoramos nosso Makefile com variáveis. Mas ainda tínhamos um problema estrutural: precisávamos escrever um bloco de regra para **cada** arquivo `.c` do projeto.

Imagine fazer isso em um projeto com 500 arquivos fonte. É justamente para resolver esse problema de escalabilidade que existem as **Pattern Rules** (Regras de Padrão).

> **Nota:** O Make possui "Regras Implícitas" embutidas, mas nesta aula vamos escrever as nossas próprias — o que nos dá controle total sobre o comportamento.

---

## 2. O Curinga `%` e o Conceito de *Stem*

A ideia central é ensinar ao Make um **molde universal**:

> *"Toda vez que você precisar gerar um arquivo `.o`, procure um arquivo com o mesmo nome terminando em `.c` e aplique este comando."*

Para isso, usamos o caractere curinga **`%`**:

- O `%` representa qualquer sequência de caracteres.
- O texto específico capturado pelo `%` durante a execução é chamado de **stem** (raiz).

**Exemplo prático:** se o Make precisa construir `main.o`, o `%` captura `main` (o *stem*) e usa esse valor para procurar `main.c`.

---

## 3. Mão na Massa: Construindo o Makefile Dinâmico

> 💡 **Lembrete:** O código final desta aula está na pasta `exemplos/aula-03/`.

### Passo 1: Escrevendo a Pattern Rule

Em vez de listar cada arquivo explicitamente, criamos uma regra baseada em padrão:

```makefile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
```

O que o Make entende aqui:

| Trecho | Significado |
| --- | --- |
| `%.o` | "Se eu precisar construir **qualquer** arquivo `.o`..." |
| `%.c` | "...eu dependo de um `.c` com o mesmo *stem*." |
| `$<` | Primeira dependência (o arquivo `.c`). |
| `$@` | O alvo da regra (o arquivo `.o`). |

---

### Passo 2: Descobrindo os arquivos automaticamente

Podemos pedir ao Make que vasculhe a pasta e descubra todos os `.c` existentes com a função `wildcard`. Em seguida, convertemos a lista de `.c` em `.o` com substituição de sufixo:

```makefile
# Encontra todos os arquivos .c (ex: main.c mensagem.c)
SRCS = $(wildcard *.c)

# Substitui .c por .o (ex: main.o mensagem.o)
OBJS = $(SRCS:.c=.o)
```

---

### Passo 3: O Perigo Oculto dos Arquivos `.h`

⚠️ **Atenção — erro clássico que causa horas de dor de cabeça!**

A Pattern Rule `%.o: %.c` diz que um `.o` depende apenas do `.c` correspondente. Mas e se você alterar `mensagem.h`?

Como o `.h` não está listado como dependência, o Make **não vai recompilar** o projeto. Você altera o cabeçalho, executa `make`, e... nada acontece. O binário gerado fica desatualizado silenciosamente.

A solução simples para esta aula é declarar que todos os `.o` dependem de todos os `.h`:

```makefile
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
```

> **Nota para o futuro:** essa abordagem é uma simplificação. Em projetos maiores, usamos as flags `-MMD -MP` do GCC para rastrear dependências de cabeçalho cirurgicamente — o compilador gera um arquivo `.d` para cada `.c` com as dependências exatas. Veremos isso em aulas avançadas.

---

### Passo 4: O Código Completo Refatorado

```makefile
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
```

---

### Passo 5: Testando — Veja o Make em Ação

**Compilação inicial:**

```
$ make
gcc -Wall -Wextra -g -c main.c -o main.o
gcc -Wall -Wextra -g -c mensagem.c -o mensagem.o
gcc main.o mensagem.o -o programa
```

**Rodando `make` novamente sem alterar nada:**

```
$ make
make: 'programa' is up to date.
```

O Make percebe que nada mudou e não faz trabalho desnecessário.

**Alterando `mensagem.h` e rodando `make`:**

```
$ touch mensagem.h
$ make
gcc -Wall -Wextra -g -c main.c -o main.o
gcc -Wall -Wextra -g -c mensagem.c -o mensagem.o
gcc main.o mensagem.o -o programa
```

Ambos os `.o` são recompilados, porque ambos dependem de `$(HEADERS)`.

**Limpeza:**

```
$ make clean
rm -f main.o mensagem.o programa
```

Note que a variável `$(OBJS)` expande automaticamente para os arquivos corretos — sem precisar listá-los à mão.

---

## 4. Resumo / Cheat Sheet

| Recurso | Sintaxe | Para que serve? |
| --- | --- | --- |
| **Pattern Rule** | `%.o: %.c` | Cria regras baseadas em padrões de nomenclatura. |
| **Curinga / Stem** | `%` | Curinga que captura o nome base (*stem*) do arquivo. |
| **Listagem Dinâmica** | `$(wildcard *.c)` | Vasculha a pasta e retorna todos os arquivos `.c`. |
| **Substituição de Sufixo** | `$(VAR:.c=.o)` | Troca o sufixo `.c` por `.o` em uma lista de arquivos. |
| **Target Protetor** | `.PHONY: regra` | Garante que regras como `clean` funcionem mesmo se existir um arquivo com esse nome. |
| **Variável `$<`** | `$<` | Representa a **primeira** dependência da regra (ex: o `.c`). |
| **Variável `$@`** | `$@` | Representa o **alvo** da regra (ex: o `.o`). |
| **Variável `$^`** | `$^` | Representa **todos** os pré-requisitos (usada na linkagem). |

---

## 5. O que veremos na próxima aula?

No mundo real, raramente deixamos arquivos `.c`, `.h` e `.o` espalhados na mesma pasta. O padrão é organizar o projeto em diretórios como `src/`, `include/` e `build/`.

Na **Aula 04**, fecharemos o módulo de Make aprendendo as boas práticas de arquitetura de diretórios e como adaptar este Makefile para compilar arquivos organizados em pastas separadas.