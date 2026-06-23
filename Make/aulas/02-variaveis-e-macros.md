# Aula 02: Variáveis e Macros

## 1. Introdução Teórica

Na aula anterior, construímos um `Makefile` funcional, mas que sofria de um problema muito comum na programação: **repetição de código**. Nós escrevemos o comando `gcc` três vezes e repetimos os nomes dos arquivos `.o` em vários lugares.

No ecossistema do **Make**, podemos criar **Variáveis** (frequentemente chamadas de macros) para armazenar textos, como nomes de compiladores, *flags* (opções) de compilação ou listas de arquivos.

### O Problema que Resolvemos Aqui

Imagine que o seu projeto cresceu para 100 arquivos. De repente, a equipe decide que vocês devem parar de usar o compilador `gcc` e passar a usar o `clang`, além de ativar alertas rigorosos de código (como a flag `-Wall`).

Sem variáveis, você teria que abrir o `Makefile` e substituir `gcc` por `clang -Wall` em **100 linhas diferentes**. Com variáveis, você altera apenas **uma única linha** no topo do arquivo e o Make aplica a mudança no projeto inteiro. Isso traz manutenibilidade e flexibilidade.

---

## 2. Mão na Massa: Refatorando nosso Makefile

Vamos pegar o projeto da aula passada e reescrevê-lo utilizando as melhores práticas do mercado.

> 💡 **Lembrete:** Você pode encontrar os arquivos desta aula na pasta `exemplos/aula-02/` do nosso repositório. O código-fonte em C (`main.c`, `mensagem.c` e `mensagem.h`) é exatamente o mesmo da Aula 01.

### Passo 1: Definindo Variáveis Tradicionais

A sintaxe para criar uma variável no Make é simples: `NOME_DA_VARIAVEL = valor`. Para usar o valor depois, colocamos o nome entre parênteses precedido por um cifrão: `$(NOME_DA_VARIAVEL)`.

Existem convenções universais para nomes de variáveis no Make:

* **`CC`**: O compilador C que será utilizado (ex: gcc, clang).
* **`CFLAGS`**: As *flags* que serão passadas para o compilador.
* **`OBJ`**: A lista de arquivos objeto (`.o`) necessários.

Abra um novo arquivo `Makefile` e adicione este cabeçalho:

```makefile
# Definindo as nossas variáveis

CC = gcc

# Ativa os alertas e inclui informações de debug
CFLAGS = -Wall -Wextra -g  

OBJ = main.o mensagem.o

EXEC = programa

```

### Passo 2: O Poder das Variáveis Automáticas

O Make possui "variáveis secretas" que mudam de valor dependendo da regra que está sendo executada no momento. Elas parecem criptografia, mas são extremamente úteis:

* **`$@`**: Pega o nome do **alvo** (target) da regra.
* **`$^`**: Pega o nome de **todas as dependências** da regra.
* **`$<`**: Pega o nome apenas da **primeira dependência** da regra.

> Relembrando que a estrutura de toda regra é:
>```makefile
> alvo: dependencias
>	comando
>```

### Passo 3: O Makefile Refatorado

Substituindo os textos fixos da Aula 01 pelas nossas novas variáveis, o nosso `Makefile` ficará assim:

```makefile
# --- Variáveis Iniciais ---
CC = gcc
CFLAGS = -Wall -Wextra
OBJ = main.o mensagem.o
EXEC = programa

# Por convenção, variáveis do Make costumam ser escritas em letras maiúsculas para facilitar a identificação.

# --- Regras de Compilação ---

# Regra principal (Linkagem)
# Vai virar: gcc main.o mensagem.o -o programa
$(EXEC): $(OBJ)
	$(CC) $^ -o $@

# Regra para compilar o main.o
# Vai virar: gcc -Wall -Wextra -c main.c
main.o: main.c mensagem.h
	$(CC) $(CFLAGS) -c $<

# Regra para compilar o mensagem.o
# Vai virar: gcc -Wall -Wextra -c mensagem.c
mensagem.o: mensagem.c mensagem.h
	$(CC) $(CFLAGS) -c $<

# Regra de limpeza
clean:
	rm -f *.o $(EXEC)

```

### Passo 4: Executando e Testando

1. No seu terminal, dentro da pasta da Aula 02, digite `make`.
2. Observe a saída no terminal. Você verá que o Make automaticamente substituiu as variáveis e executou os comandos completos com as flags `-Wall` e `-Wextra`.
3. Experimente alterar a variável `CC = gcc` para `CC = clang` (se você tiver o clang instalado) ou mude o nome do `EXEC`. Digite `make clean` e depois `make` novamente. Veja como todo o comportamento do build muda alterando apenas a primeira linha!

---

## 3. Resumo / Cheat Sheet

### Variáveis Comuns (Convenção do Mercado)

| Variável | Significado | Exemplo de Uso |
| --- | --- | --- |
| **`CC`** | Compilador C | `CC = gcc` |
| **`CXX`** | Compilador C++ | `CXX = g++` |
| **`CFLAGS`** | Opções para compilar C | `CFLAGS = -Wall -O2` |
| **`LDFLAGS`** | Opções para o Linker | `LDFLAGS = -lm` (para linkar a math.h) |

### Variáveis Automáticas (Decore estas 3!)

| Variável | O que ela representa | Onde usar? |
| --- | --- | --- |
| **`$@`** | O nome do Alvo (Target) | Após a flag `-o` para dar nome ao executável |
| **`$^`** | Todas as dependências | Ao passar os arquivos `.o` para o compilador |
| **`$<`** | Apenas a primeira dependência | Para pegar apenas o arquivo `.c` e não os `.h` |

---

## 4. O que veremos na próxima aula?

Mesmo usando variáveis, repare que nós ainda tivemos que escrever uma regra específica para o `main.o` e outra idêntica para o `mensagem.o`. Se tivéssemos 50 arquivos `.c`, ainda precisaríamos de 50 blocos de regras quase iguais.

Na **Aula 03**, vamos acabar com isso usando **Regras Implícitas (Pattern Rules)**. Vamos ensinar o Make a compilar *qualquer* arquivo `.c` do universo com apenas duas linhas de código usando o operador mágico `%`!
