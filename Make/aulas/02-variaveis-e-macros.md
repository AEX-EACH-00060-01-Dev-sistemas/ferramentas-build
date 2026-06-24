# Aula 02: Variáveis e Macros

## 1. Introdução

Na aula anterior, construímos um `Makefile` funcional, mas que sofria de um problema muito comum na programação: **repetição de código**. Escrevemos o comando `gcc` três vezes e repetimos nomes de arquivos em vários lugares.

No ecossistema do Make, podemos criar **variáveis** (frequentemente chamadas de macros) para armazenar textos — nomes de compiladores, flags de compilação, listas de arquivos, e assim por diante.

### O Problema que Resolvemos Aqui

Imagine que seu projeto cresceu para 100 arquivos. De repente, a equipe decide parar de usar o `gcc` e passar a usar o `clang`, adicionando flags de alerta rigoroso.

Sem variáveis, você abriria o `Makefile` e substituiria `gcc` por `clang -Wall` em **100 linhas diferentes**. Com variáveis, você altera apenas **uma única linha** no topo do arquivo e o Make aplica a mudança no projeto inteiro.

---

## 2. Mão na Massa: Refatorando nosso Makefile

> 💡 **Lembrete:** Os arquivos desta aula estão em `exemplos/aula-02/`. O código-fonte em C (`main.c`, `mensagem.c` e `mensagem.h`) é exatamente o mesmo da Aula 01.

### Passo 1: Definindo Variáveis

A sintaxe para criar uma variável no Make é `NOME = valor`. Para usar o valor, coloca-se o nome entre parênteses precedido por um cifrão: `$(NOME)`.

Por convenção universal, **variáveis do Make são escritas em letras maiúsculas** para facilitar a identificação no arquivo. Existem nomes consagrados pelo mercado:

- **`CC`**: O compilador C a ser utilizado (ex: `gcc`, `clang`).
- **`CFLAGS`**: As flags passadas ao compilador na etapa de compilação.
- **`OBJS`**: A lista de arquivos objeto (`.o`) necessários.
- **`EXEC`**: O nome do executável final.

Abra um novo `Makefile` e adicione este cabeçalho:

```makefile
CC    = gcc
CFLAGS = -Wall -Wextra -g
OBJS  = main.o mensagem.o
EXEC  = programa
```

---

### Passo 2: Variáveis Automáticas

O Make possui variáveis especiais que mudam de valor dependendo da regra em execução. Elas parecem crípticas à primeira vista, mas são indispensáveis:

| Variável | O que representa | Onde usar |
| --- | --- | --- |
| `$@` | O **alvo** (target) da regra | Após `-o` para nomear o executável ou `.o` |
| `$^` | **Todas** as dependências | Para passar todos os `.o` ao linker |
| `$<` | Apenas a **primeira** dependência | Para pegar só o `.c`, ignorando os `.h` |

Vale entender por que `$<` é necessário. Se usássemos `$^` na regra de compilação de `main.o`, o compilador receberia `main.c mensagem.h` como entrada — o que causaria um erro, pois o GCC não aceita `.h` como argumento direto. O `$<` garante que só o `.c` seja passado.

---

### Passo 3: O Makefile Refatorado

Substituindo os textos fixos da Aula 01 pelas variáveis:

```makefile
# --- Variáveis ---
CC     = gcc
CFLAGS = -Wall -Wextra -g
OBJS   = main.o mensagem.o
EXEC   = programa

# --- Regras de Compilação ---

# Linkagem: junta os .o e gera o executável
# Expande para: gcc main.o mensagem.o -o programa
$(EXEC): $(OBJS)
	$(CC) $^ -o $@

# Compila main.o a partir de main.c
# Expande para: gcc -Wall -Wextra -g -c main.c
main.o: main.c mensagem.h
	$(CC) $(CFLAGS) -c $<

# Compila mensagem.o a partir de mensagem.c
# Expande para: gcc -Wall -Wextra -g -c mensagem.c
mensagem.o: mensagem.c mensagem.h
	$(CC) $(CFLAGS) -c $<

# Limpeza
clean:
	rm -f *.o $(EXEC)
```

> **Nota:** você pode ter reparado que `clean` não tem dependências e não gera nenhum arquivo — ele só executa um comando. Isso pode causar um problema sutil que resolveremos na Aula 03 com o `.PHONY`.

---

### Passo 4: Testando — Veja o Make Expandindo as Variáveis

**Compilação inicial:**

```
$ make
gcc -Wall -Wextra -g -c main.c
gcc -Wall -Wextra -g -c mensagem.c
gcc main.o mensagem.o -o programa
```

Repare que o Make substituiu `$(CC)`, `$(CFLAGS)` e as variáveis automáticas antes de executar cada comando. O que você escreve no `Makefile` é o molde; o que aparece no terminal é o comando real expandido.

**Rodando `make` novamente sem alterar nada:**

```
$ make
make: 'programa' is up to date.
```

**Trocando o compilador — alterando só uma linha:**

Mude `CC = gcc` para `CC = clang`, execute `make clean` e depois `make`:

```
$ make clean
rm -f *.o programa

$ make
clang -Wall -Wextra -g -c main.c
clang -Wall -Wextra -g -c mensagem.c
clang main.o mensagem.o -o programa
```

Todo o projeto foi recompilado com o novo compilador. Você alterou **uma linha** e o efeito se propagou por todas as regras — esse é o valor das variáveis.

---

## 3. Resumo / Cheat Sheet

### Variáveis Comuns (Convenção do Mercado)

| Variável | Significado | Exemplo |
| --- | --- | --- |
| `CC` | Compilador C | `CC = gcc` |
| `CXX` | Compilador C++ | `CXX = g++` |
| `CFLAGS` | Flags de compilação C | `CFLAGS = -Wall -O2` |
| `LDFLAGS` | Flags do linker | `LDFLAGS = -lm` (linka a libmath) |

### Variáveis Automáticas (Decore estas 3!)

| Variável | O que representa | Onde usar |
| --- | --- | --- |
| `$@` | O alvo da regra | Após `-o` para nomear o arquivo de saída |
| `$^` | Todas as dependências | Para passar os `.o` ao linker |
| `$<` | Primeira dependência | Para pegar só o `.c` e ignorar os `.h` |

---

## 4. O que veremos na próxima aula?

Mesmo usando variáveis, ainda precisamos escrever uma regra separada para `main.o` e outra para `mensagem.o`. Com 50 arquivos `.c`, seriam 50 blocos quase idênticos.

Na **Aula 03**, vamos resolver isso com **Pattern Rules**. Vamos ensinar o Make a compilar qualquer arquivo `.c` do projeto com apenas duas linhas, usando o operador curinga `%`.