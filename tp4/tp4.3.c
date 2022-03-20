#include <stdio.h>
#define TAM 10

int main() {

	int vetor[TAM];
		    /* 0    1    2    3 */
	char abc[] = {'a', 'b', 'c', 'd'};
	void *p;
	int x;

	/* int ocupa 4 bytes de memoria */
	p = (void*)vetor;

	/* char ocupa 1 byte cada letra, entao cabem 4 letras em um espaço de memoria do vetor inteiro */
	for(x = 0; x < TAM * 4; x++) {
	/* 0 % 4 = 0
	 * 1 % 4 = 1
	 * 2 % 4 = 2
	 * 3 % 4 = 3
	 * 4 % 4 = 0
	 */
		*(char*)p = abc[x%4];
		p = (char*)p + 1;
	}

	/* aponta para o inicio do vetor */
	p = (void*)vetor;

	/* o valor em int em cada espaco de memoria eh o mesmo, porque foram armazenados 'abcd' em todos */
	for(x = 0; x < TAM; x++) {
		
		printf("(%p) vetor[%d] = %d \n", p, x, *(int*)p);
		p = (int*)p + 1; 
	}
	
	printf("\n");

	p = (void*)vetor;

	for(x = 0; x < TAM * 4; x++) {
		
		printf("(%p) vetor[%d] = %c \n", p, x, *(char*)p);
		p = (char*)p + 1;
	}

	return 0;
}

