parametros= -Wall -std=c90

all: testa_fila testa_pilha testa_lista

testa_fila: testa_fila.o libfila.o
	gcc -o testa_fila testa_fila.o libfila.o $(parametros)

testa_fila.o: testa_fila.c
	gcc $(parametros) -c testa_fila.c

libfila.o: libfila.h libfila.c
	gcc $(parametros) -c libfila.c

testa_pilha: testa_pilha.o libpilha.o
	gcc -o testa_pilha testa_pilha.o libpilha.o $(parametros)

testa_pilha.o: testa_pilha.c
	gcc $(parametros) -c testa_pilha.c

libpilha.o: libpilha.h libpilha.c
	gcc $(parametros) -c libpilha.c

testa_lista: testa_lista.o liblista.o
	gcc -o testa_lista testa_lista.o liblista.o $(parametros)

testa_lista.o: testa_lista.c
	gcc $(parametros) -c testa_lista.c

liblista.o: liblista.h liblista.c
	gcc $(parametros) -c liblista.c

clean:
	rm -f *.o testa_fila testa_pilha testa_lista



