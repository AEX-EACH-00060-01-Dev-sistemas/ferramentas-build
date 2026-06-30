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
