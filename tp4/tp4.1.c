#include <stdio.h>

/*gcc -Wall -std=c90 -o*/

/* rsync -av groo.inf.ufpr.br:tpm .
 */

int main() {

	double d = 3.14159;
	double *pd = &d;
	int i = 42;
	int *pi = &i;
	char c = 't';
	char *pc = &c; 
	
	/*todo ponteiro tem 8 bytes, independente de onde aponta
	%ld sizeof(int)*/
	printf("O endereço de char %c é %p\n", 'c', pc);
	printf("O endereço de int %c é %p\n", 'i', pi);
	printf("O endereço de double %c é %p\n", 'd', pd);
	printf("O endereço de char* %s é %p\n", "pc", &pc);
	printf("O endereço de int* %s é %p\n", "pi", &pi);
	printf("O endereço de double* %s é %p\n\n", "pd", &pd);

	printf("O valor de char c é %c\n", c);
	printf("O valor de int i é %d\n", i);
	printf("O valor de double d é %f\n", d);
	printf("O valor de char* pc é %c\n", *pc);
	printf("O valor de int* i é %d\n", *pi);
	printf("O valor de double* d é %f\n\n", *pd);

	printf("O tamanho de char é %ld\n", sizeof(char));
	printf("O tamanho de int é %ld\n", sizeof(int));
	printf("O tamanho de double é %ld\n", sizeof(double));
	printf("O tamanho de char* é %ld\n", sizeof(char*));
	printf("O tamanho de int* é %ld\n", sizeof(int*));
	printf("O tamanho de double* é %ld\n\n", sizeof(double*));

	return 0;
}
