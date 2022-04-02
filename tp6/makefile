parametros= -g -Wall -std=c90
nomePrograma=tp6

all: $(nomePrograma)

$(nomePrograma): tp6.o libpilha.o
	gcc -o $(nomePrograma) tp6.o libpilha.o $(parametros)

tp6.o: tp6.c
	gcc $(parametros) -c tp6.c 

libpilha.o: libpilha.h libpilha.c
	gcc $(parametros) -c libpilha.c 

clean:
	rm -f *.o $(nomePrograma)