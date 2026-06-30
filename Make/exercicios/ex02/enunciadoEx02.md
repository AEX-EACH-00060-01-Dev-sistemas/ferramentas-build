# Exercício 2: O Poder das Variáveis Automáticas e Pattern Rules (Médio)

## Objetivo
Você recebeu os códigos de um pequeno conversor de texto composto por `main.c`, `str_utils.c` e `str_utils.h`. 

No exercício anterior, escrevemos uma regra para cada arquivo `.o` manualmente. Imagine fazer isso para um projeto com 50 arquivos! Para resolver isso, sua tarefa agora é criar um `Makefile` mais inteligente que:
1. Compile o executável com o nome `conversor`.
2. Utilize uma **Pattern Rule** (`%.o: %.c`) para ensinar o Make a compilar qualquer arquivo `.c` em um arquivo `.o` de forma genérica.
3. Utilize as **Variáveis Automáticas** (`$@`, `$<`, `$^`) nas suas regras em vez de digitar os nomes dos arquivos repetidas vezes nos comandos.

## Requisitos
- Defina variáveis `CC` e `CFLAGS`.
- Crie uma variável `TARGET` com o valor `conversor` e uma variável `OBJ` com os arquivos objeto (`main.o str_utils.o`).
- O target principal (`all`) deve depender de `$(TARGET)`.
- Implemente o target `clean`.

---

<details>
<summary><b>Dica 1: O que são as Variáveis Automáticas? (Clique para expandir)</b></summary>

- `$@` : Representa o nome do **alvo** (target) da regra.
- `$<` : Representa o nome da **primeira dependência**. Muito útil para compilar o arquivo `.c` correspondente.
- `$^` : Representa **todas as dependências** listadas, separadas por espaço. Excelente para usar na hora do "link" (gerar o executável final).
</details>

<details>
<summary><b>Dica 2: Como montar a Pattern Rule? (Clique para expandir)</b></summary>

Uma pattern rule diz ao make "como transformar qualquer X em Y". No caso do C:
```makefile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

```

Isso significa: "Para gerar um `.o`, pegue o `.c` correspondente (`$<`) e compile gerando o alvo (`$@`)".
</details>

---

<details>
<summary><b>Resposta Esperada (Clique para ver a solução completa)</b></summary>

Seu `Makefile` deve ficar parecido com este:

```makefile
# Variáveis de Compilação
CC = gcc
CFLAGS = -Wall -Wextra -g

# Variáveis de Arquivos
TARGET = conversor
OBJ = main.o str_utils.o

# Alvo principal
all: $(TARGET)

# Linkando o executável final (Usa $^ para pegar todos os .o e $@ para o alvo)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Pattern Rule para compilar os objetos (Usa $< para pegar o .c e $@ para o alvo .o)
%.o: %.c str_utils.h
	$(CC) $(CFLAGS) -c $< -o $@

# Alvo de limpeza
clean:
	rm -f *.o $(TARGET)

# Boas práticas
.PHONY: all clean