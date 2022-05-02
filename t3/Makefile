parametros = -Wall -std=c90
objetos = ru_na_pandemia.o libgrupo.o libfila.o libpilha.o liblista.o 

all: ru_na_pandemia

ru_na_pandemia: $(objetos)
	gcc -o ru_na_pandemia $(objetos) $(parametros) 

ru_na_pandemia.o: ru_na_pandemia.c
	gcc $(parametros) -c ru_na_pandemia.c

libgrupo.o: libgrupo.h libgrupo.c
	gcc $(parametros) -c libgrupo.c

libfila.o: libfila.h libfila.c
	gcc $(parametros) -c libfila.c

libpilha.o: libpilha.h libpilha.c
	gcc $(parametros) -c libpilha.c

liblista.o: liblista.h liblista.c
	gcc $(parametros) -c liblista.c

clean:
	rm -f *.o ru_na_pandemia 