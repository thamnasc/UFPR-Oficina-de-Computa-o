#include "libpilha.h"
#include <stdlib.h>
#include <stdio.h>

pilha_t *pilha_cria(int nelem) {

    pilha_t *pilha;

    if(! (pilha = malloc(sizeof(pilha_t))))
        return NULL;

    pilha->topo = -1;
    pilha->nelem = nelem;

    if(! (pilha->elems = malloc(sizeof(int) * nelem)))
        return NULL;

    return pilha;
}

int push(pilha_t *pilha, int elem) {

    /* se a pilha não está cheia */
    if(pilha->topo != (pilha->nelem - 1)) {
        pilha->topo++;
        pilha->elems[pilha->topo] = elem;

    /* número de elementos da pilha */
        return (pilha->topo + 1);
    }

    /* pilha está cheia */
    return -1;
}

int pop(pilha_t *pilha) {

    if(pilha_vazia(pilha))
        return 0;

    pilha->topo--;

    return pilha->elems[pilha->topo + 1];
}
 
int pilha_topo(pilha_t *pilha) {

    return pilha->elems[pilha->topo];
}

int pilha_tamanho(pilha_t *pilha) {

    return pilha->topo + 1;
}

int pilha_vazia(pilha_t *pilha) {

    if(pilha->topo == -1)
        return 1;
    
    return 0;
}

pilha_t* pilha_destroi(pilha_t *pilha) {

    /* para não perder o ponteiro do vetor,
     * é preciso desalocá-lo antes da pilha */
    free(pilha->elems);
    pilha->elems = NULL;

    free(pilha);

    return NULL;
}

void pilha_imprime(pilha_t *pilha) {

    int i;

    if(pilha_vazia(pilha))
        return;
    
    for(i = 0; i < pilha->topo; i++) {
        printf("%d ", pilha->elems[i]);
    }
    printf("%d", pilha->elems[pilha->topo]);
}