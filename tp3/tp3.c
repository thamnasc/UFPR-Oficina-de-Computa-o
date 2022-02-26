//tp3
//tmn21
//Criado em 22/02/22

#include <stdio.h>
#include <locale.h>
#include <math.h>

int verifica_primo(int n) {

	//um número primo é um número que é divisível apenas por 1 e ele mesmo
	//então começamos a verificar a partir do 2

	if(n == 0 || n == 1) return 0; //não é primo

	if(n != 2) {

		//método de otimizar com crivo de erastótenes
		//verificar até a raiz do número arrendada para baixo 
		for(int i=2; i <= floor(sqrt(n)); i++) {
			if(n % i == 0) return 0; //é divisível por algum número, não é primo
		}
	}
	
	return 1; //é primo, porque saiu do while e não foi divisível por nenhum caso de teste
}

void imprime_resultado(int n, int eh_primo) {

	if(eh_primo)
		printf("O número %d é primo.\n", n);
	else
		printf("O número %d não é primo.\n", n);
}

int leitura_numero() {

	int numero;

	do {
		printf("Informe um número natural:\n");
		scanf("%d", &numero);
	} while(numero < 0);

	return numero;
}

int main() {
	
	int numero, primo;

	//para poder usar acentuação 
	setlocale(LC_ALL, "Portuguese Brazil");	

	numero = leitura_numero();
	primo = verifica_primo(numero);
	imprime_resultado(numero, primo);

	return 0;
}
