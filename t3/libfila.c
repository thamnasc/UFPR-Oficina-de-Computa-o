#include "libfila.h"
#include <stdlib.h>
#include <stdio.h>

fila_t *fila_cria() {

    fila_t *auxFila;

    /* caso não seja bem sucedida a alocação */
    if(! (auxFila = malloc(sizeof(fila_t))))
        return NULL;

    auxFila->ini = NULL;
    auxFila->fim = NULL;

    /* zero elementos ao iniciar */
    auxFila->tamanho = 0;

    return auxFila;
}

fila_t *fila_destroi(fila_t *f) {
    
    nodo_f_t *auxNodo;

    if(fila_vazia(f)) {
        free(f);
        return NULL;
    } 

    auxNodo = f->ini;

    /* primeiro libera espaço dos nodos */
    while(auxNodo->prox != NULL) {
        f->ini = f->ini->prox;
        free(auxNodo);
        auxNodo = f->ini;
    }

    free(auxNodo);
    
    free(f);

    /* devolve NULL para a fila */
    return NULL;
}

int fila_vazia(fila_t *f) {

    if(f->tamanho == 0)
        return 1;

    return 0;
}


int fila_tamanho(fila_t *f) {

    return f->tamanho;
}

int queue(fila_t *f, int elemento) {

    nodo_f_t *novoNodo;

    /* caso não seja bem sucedida a alocação */
    if(! (novoNodo = malloc(sizeof(nodo_f_t))))
        return 0;
    novoNodo->chave = elemento;
    novoNodo->prox = NULL;
    
    if(fila_vazia(f)) {
        f->ini = novoNodo;
        f->fim = novoNodo;
        f->tamanho++;

        return 1;
    }

    f->fim->prox = novoNodo;
    f->fim = novoNodo;
    f->tamanho++;

    return 1;
}

int dequeue(fila_t *f, int *elemento) {

    nodo_f_t *auxNodo;

    /* não é possível remover elementos de uma lista vazia */
    if(fila_vazia(f))
        return 0;

    auxNodo = f->ini;

    *elemento = f->ini->chave;

    f->ini = f->ini->prox;
    f->tamanho--;
    free(auxNodo);
    
    return 1;
}

void fila_imprime(fila_t *f) {

    /* cria nodo auxiliar para não alterar o início da fila */
    nodo_f_t *auxNodo;

    /* não imprime fila vazia */
    if(fila_vazia(f)) 
        return;

    auxNodo = f->ini;

    while(auxNodo->prox != NULL) {
        printf("%d ", auxNodo->chave);
        auxNodo = auxNodo->prox;
    }

    printf("%d\n", auxNodo->chave);
}