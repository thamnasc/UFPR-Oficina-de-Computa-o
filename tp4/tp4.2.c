#include <stdio.h>

void troca_nums(int *x, int *y) {

	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

/* Como as variáveis foram criadas como ponteiros do tipo char,
 * *s1 e *s2 guardam a primeira letra das strings
 * e s1 e s2 o endereço da primeira letra de cada string.
 * Como queremos inverter os ponteiros, chamamos *s1 e *s2 como ponteiros novamente (ponteiro de ponteiro).
 * Isso é necessário ao se trabalhar com funções, assim é possível de se alterar propriamente as variáveis (não apenas localmente).
 * Um ponteiro de ponteiro tem *x como o endereço da variável que é apontada
 * e **x aponta para o que o ponteiro está apontando, ou seja, o conteúdo propriamente dito. */
void troca_ponteiros(char **x, char **y) {

	char *tmp;
        /* guarda o endereco que o ponteiro **x está apontando */	
	tmp = *x;
	/* guarda o endereço que o ponteiro **y está apontando */
	*x = *y;
	/* guarda o endereço que o ponteiro *tmp está apontando */
	*y = tmp;
}

int main() {
	
	int a, b;

	/* s1 e s2 guardam o endereço do primeiro caracter da string */
	char *s1, *s2;

	a = 3;
	b = 4;

	troca_nums(&a, &b);

	printf("a eh %d\n", a);
	printf("b eh %d\n", b);
	
	s1 = "Imprimir isso primeiro";
	s2 = "Imprimir isso depois";

	/* passa o endereço de s1 e s2, para que possa trabalhar invertendo os ponteiros*/
	troca_ponteiros(&s1, &s2);

	printf("s1 eh %s\n", s1);
	printf("s2 eh %s\n", s2);

	return 0;
}
