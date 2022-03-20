#include <stdio.h>
#include <stdlib.h>
#define MAX 200

void le_vetor(int v[]) {
	
	int i = 0;
	
	scanf("%d", &v[i]);
	while(v[i] != -1) {
		i++;
		scanf("%d", &v[i]);
	}
}

int verifica_tamanho_vetor(int v[]) {

	int i;

	/* o tamanho do vetor eh uma unidade maior que o ultimo indice */
	for(i = 0; i < MAX; i++) {
		if(v[i] == -1)
			return i + 1;
	}

	return 0;
}

int *une_vetores(int v[], int w[]) {

	int i, tam_v, tam_w, tam = 0;
	int *vet;
	
	/* retira -1 de v[] */
	tam_v = verifica_tamanho_vetor(v) - 1;
	tam_w = verifica_tamanho_vetor(w);

	/* contém apenas um -1 no final do novo vetor */
	tam = tam_v + tam_w;

	if(!(vet = malloc(sizeof(int) * tam))) {
		fprintf(stderr, "Alocacao de memoria falhou \n");
		exit(1);
	}
	
	/* coloca no vetor uniao primeiro os elementos de v[] */
	for(i = 0; i < tam_v; i++) 
		*(vet + i) = v[i];

	/* depois os de w[] */
	for(i = tam_v; i < tam; i++) 
		*(vet + i) = w[i - tam_v];

	return vet;
}

int main() {

	int i = 0;
	int *vp;
	int v[MAX], w[MAX];

	le_vetor(v);
	le_vetor(w);

	vp = une_vetores(v, w);

	while(*(vp + i) != -1) {
		printf("vetor[%d] = %d \n", i, *(vp + i));
		i++;
	}

	free(vp);
	vp = NULL;

	return 0;
}
