#include <stdio.h>
#define TAM 10

int main() {

	int vetor[TAM];
	char abc[] = {'a', 'b', 'c', 'd'};
	void *p;
	int x;

	p = (void*)vetor;

	for(x = 0; x < TAM * 4; x++) {
		*(char*)p = abc[x%4];
		p = (char*)p + 1;
	}

	p = (void*)vetor;

	for(x = 0; x < TAM; x++) {
		
		printf("(%p) vetor[%d] = %d \n", p, x, *(int*)p);
		p = (int*)p + 1; 
	}
	
	printf("\n");

	p = (void*)vetor;

	for(x = 0; x < TAM; x++) {
		
		printf("(%p) vetor[%d] = %c \n", p, x, *(char*)p);
		p = (char*)p + 1;
	}

	return 0;
}

