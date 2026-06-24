# Nossa primeira regra gera o executável final chamado 'programa'
programa: main.o mensagem.o
	gcc main.o mensagem.o -o  programa

# Regra para compilar apenas o main.c
main.o: main.c mensagem.h
	gcc -c main.c

# Regra para compilar apenas o mensagem.c
mensagem.o: mensagem.c mensagem.h
	gcc -c mensagem.c

# Uma regra especial (phony target) para limpar os arquivos gerados
clean:
	rm -f *.o programa