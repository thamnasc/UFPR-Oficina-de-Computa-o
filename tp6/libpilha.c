#include "libpilha.h"
#include <stdlib.h>

pilha_t *inicializa_pilha(int nelem) {

    pilha_t *pilha;

    if( !(pilha = malloc(sizeof(pilha_t))) )
        return NULL;

    pilha->topo = -1;
    pilha->nelem = nelem;

    if( !(pilha->elems = malloc(sizeof(char) * nelem)) )
        return NULL;

    return pilha;
}

int push(pilha_t *pilha, char elem) {

    /* se a pilha não está cheia */
    if( pilha->topo != (pilha->nelem - 1) ) {
        pilha->topo++;
        pilha->elems[pilha->topo] = elem;

    /* número de elementos da pilha */
        return (pilha->topo + 1);
    }

    /* pilha está cheia */
    return -1;
}

char pop(pilha_t *pilha) {

    if( pilha_vazia(pilha) )
        return 0;

    pilha->topo--;

    return pilha->elems[pilha->topo + 1];
}

char topo(pilha_t *pilha) {

    return pilha->elems[pilha->topo];
}

int pilha_vazia(pilha_t *pilha) {

    if( pilha->topo == -1 )
        return 1;
    
    return 0;
}

void destroi_pilha(pilha_t *pilha) {

    /* para não perder o ponteiro do vetor,
     * é preciso desalocá-lo antes da pilha */
    free(pilha->elems);
    pilha->elems = NULL;

    free(pilha);
    pilha = NULL;
}