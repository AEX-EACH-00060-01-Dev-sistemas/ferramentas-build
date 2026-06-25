# Exercício 1: O Primeiro Makefile (Fácil)

## Objetivo
Você recebeu o código-fonte de uma calculadora muito simples, dividida em três arquivos: `main.c`, `math_utils.c` e `math_utils.h`. 
Atualmente, para compilar o programa, você precisa digitar comandos longos no terminal. 

Sua tarefa é criar um arquivo chamado `Makefile` na mesma pasta dos códigos, de forma que:
1. Ao rodar apenas `make` ou `make all`, o programa seja compilado e gere um executável chamado `calc`.
2. Ao rodar `make clean`, o executável `calc` e os arquivos objeto (`.o`) sejam apagados.

## Requisitos
- Utilize variáveis para o compilador (`CC`) e as flags de compilação (`CFLAGS`).
- O executável deve se chamar `calc`.
- O código possui dois arquivos `.c`. Ambos devem ser compilados para arquivos objeto (`.o`) antes de serem "linkados" no executável final.

---

<details>
<summary><b>Dica 1 (Clique para expandir)</b></summary>

Comece definindo as variáveis no topo do arquivo. Por exemplo:
```makefile
CC = gcc
CFLAGS = -Wall -g
```
</details>

<details>
<summary><b>Dica 2 (Clique para expandir)</b></summary>

Lembre-se de que a estrutura básica de uma regra no Makefile é:
```makefile
alvo: dependencias
	comando
```
*(Atenção: o recuo antes do comando deve ser feito com a tecla TAB, não com espaços!)*
</details>

<details>
<summary><b>Dica 3 (Clique para expandir)</b></summary>

Você precisará de regras para:
- `all` (depende de `calc`)
- `calc` (depende de `main.o` e `math_utils.o`)
- `main.o` (depende de `main.c` e `math_utils.h`)
- `math_utils.o` (depende de `math_utils.c` e `math_utils.h`)
- `clean` (remove tudo)
</details>

---

<details>
<summary><b>Resposta Esperada (Clique para ver a solução completa)</b></summary>

Seu `Makefile` deve ficar parecido com este:

```makefile
# Variáveis
CC = gcc
CFLAGS = -Wall -g

# Alvo principal
all: calc

# Regra para o executável final
calc: main.o math_utils.o
	$(CC) $(CFLAGS) -o calc main.o math_utils.o

# Regras para os arquivos objeto
main.o: main.c math_utils.h
	$(CC) $(CFLAGS) -c main.c

math_utils.o: math_utils.c math_utils.h
	$(CC) $(CFLAGS) -c math_utils.c

# Alvo para limpar os arquivos gerados
clean:
	rm -f *.o calc

# Declarar targets que não são arquivos
.PHONY: all clean
```
</details>