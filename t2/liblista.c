#include "liblista.h"
#include <stdlib.h>
#include <stdio.h>

/* cria nodo e retorna o seu ponteiro em caso de sucesso
 * retorna NULL em caso de erro
 */
nodo_l_t *nodo_cria(int elemento) {

    nodo_l_t *auxNodo;

    if(! (auxNodo = malloc(sizeof(nodo_l_t))))
        return NULL;

    auxNodo->elemento = elemento;
    auxNodo->prox = NULL;

    return auxNodo;
}

lista_t *lista_cria() {

    lista_t *auxLista;

    if(! (auxLista = malloc(sizeof(lista_t))))
        return NULL;
    
    auxLista->ini = NULL;
    auxLista->tamanho = 0;

    return auxLista;
}

lista_t *lista_destroi(lista_t *l) {

    nodo_l_t *auxNodo;

    if(lista_vazia(l)) {
        free(l);
        return NULL;
    }

    auxNodo = l->ini;

    while(auxNodo->prox != NULL) {
        l->ini = l->ini->prox;
        free(auxNodo);
        auxNodo = l->ini;
    }
    
    free(l->ini);
    free(l);

    return NULL;
}

int lista_vazia(lista_t *l) {

    if(l->tamanho == 0)
        return 1;

    return 0;
}

int lista_tamanho(lista_t *l) {

    return l->tamanho;
}

int lista_insere_inicio(lista_t *l, int elemento) {

    nodo_l_t *novoNodo;

    /* caso não seja bem sucedida a alocação do nodo,
     * retorna 0 */
    if(! (novoNodo = nodo_cria(elemento)))
        return 0;

    l->tamanho++;

    if(lista_vazia(l)) {
        l->ini = novoNodo;
        return 1;
    }

    /* quando há pelo menos um elemento na lista */
    novoNodo->prox = l->ini;
    l->ini = novoNodo;

    return 1;
}

int lista_insere_fim(lista_t *l, int elemento) {

    nodo_l_t *auxNodo, *novoNodo;

    /* caso não seja bem sucedida a alocação do nodo,
     * retorna 0 */
    if(! (novoNodo = nodo_cria(elemento)))
        return 0;

    /* se a lista estiver vazia, insere no início */
    if(lista_vazia(l)) {
        l->ini = novoNodo;
        l->tamanho++;
        return 1;
    }

    l->tamanho++;

    /* quando há pelo menos um elemento na lista */
    auxNodo = l->ini;

    /* procura pelo último elemento */
    while(auxNodo->prox != NULL) 
        auxNodo = auxNodo->prox;

    auxNodo->prox = novoNodo;

    return 1;
}

int lista_insere_ordenado(lista_t *l, int elemento) {

    nodo_l_t *nodoAtual, *nodoAnt, *novoNodo;
    int i;
    
    nodoAtual = l->ini;

    /* está ordenada com um elemento */
    if(l->tamanho > 1) {
        for(i = 0; i < l->tamanho - 1; i++) {
            /* não está ordenada */
            if(nodoAtual->elemento > nodoAtual->prox->elemento)
                return 0;
            nodoAtual = nodoAtual->prox;
        }
    }

    /* caso não seja bem sucedida a alocação do nodo,
     * retorna 0 */
    if(! (novoNodo = nodo_cria(elemento)))
        return 0;

    if(lista_vazia(l)) {
        l->ini = novoNodo;
        l->tamanho++;
        return 1;
    }

    l->tamanho++;

    nodoAtual = l->ini;
    nodoAnt = l->ini;

    /* percorre a lista até encontrar o fim */
    while(nodoAtual != NULL) {
        if(nodoAtual->elemento > novoNodo->elemento) {
            /* inserir no início da lista */
            if(nodoAtual == l->ini) {
                novoNodo->prox = nodoAtual;
                l->ini = novoNodo;
                return 1;
            }
            /* inserir antes do fim ou no meio da lista */    
            else {
                novoNodo->prox = nodoAtual;
                nodoAnt->prox = novoNodo;
                return 1;
            }
        }
        nodoAnt = nodoAtual;
        nodoAtual = nodoAtual->prox;
    }

    /* o elemento do nodo final é menor que o elemento do novoNodo */
    nodoAtual = nodoAnt;
    nodoAtual->prox = novoNodo;

    return 1;
}

int lista_retira_inicio(lista_t *l, int *elemento) {

    nodo_l_t *auxNodo;

    /* não é possível retirar elementos de uma lista vazia */
    if(lista_vazia(l))
        return 0;

    *elemento = l->ini->elemento;

    if(l->tamanho == 1) {
        l->tamanho--;
        free(l->ini);
        l->ini = NULL;
        return 1;
    }

    l->tamanho--;
    
    /* se tiver mais de um elemento */
    auxNodo = l->ini;

    l->ini = l->ini->prox;

    free(auxNodo);

    return 1;
}

int lista_retira_fim(lista_t *l, int *elemento) {

    nodo_l_t *auxNodo;
    
    /* não é possível retirar elementos de uma lista vazia */
    if(lista_vazia(l)) 
        return 0;

    if(l->tamanho == 1) {
        *elemento = l->ini->elemento;
        l->tamanho--;
        free(l->ini);
        l->ini = NULL;
        return 1;
    }

    l->tamanho--;
    auxNodo = l->ini;

    /* procura pelo penúltimo */
    while(auxNodo->prox->prox != NULL)
        auxNodo = auxNodo->prox;
    
    /* retorna o último elemento */
    *elemento = auxNodo->prox->elemento;
    /* libera espaço do último elemento */
    free(auxNodo->prox);

    /* ajusta o prox do penúltimo elemento,
     * que agora é o último elemento 
     */
    auxNodo->prox = NULL;
    
    return 1;
}

int lista_retira_elemento(lista_t *l, int *elemento) {

    nodo_l_t *nodoAnt, *nodoAtual;

    nodoAtual = l->ini;

    /* primeiro nodo contém o elemento */
    if(l->ini->elemento == *elemento) {
        l->tamanho--;
        l->ini = l->ini->prox;
        free(nodoAtual);
        return 1;
    }

    /* procura pelo elemento a ser removido */
    while((nodoAtual->elemento != *elemento) && 
          (nodoAtual->prox != NULL)) {
        nodoAnt = nodoAtual;
        nodoAtual = nodoAtual->prox;
    }
    
    /* o elemento não foi encontrado */
    if(nodoAtual->elemento != *elemento)
        return 0;
       
    l->tamanho--;

    /* último nodo contém o elemento */
    if(nodoAtual->prox == NULL) {
        nodoAnt->prox = NULL;
        free(nodoAtual);
        return 1;
    }

    /* o elemento está no meio da lista */
    nodoAnt->prox = nodoAtual->prox;
    free(nodoAtual);
    
    return 1; 
}

int lista_pertence(lista_t *l, int elemento) {

    nodo_l_t *auxNodo;

    /* não há elementos na lista */
    if(lista_vazia(l))
        return 0;

    auxNodo = l->ini;

    /* procura pelo elemento */
    while((auxNodo->elemento != elemento) && 
          (auxNodo->prox != NULL))
        auxNodo = auxNodo->prox;

    /* não encontrado */
    if(auxNodo->elemento != elemento)
        return 0;
        
    /* elemento encontrado */
    return 1;
}

void lista_imprime(lista_t *l) {

    nodo_l_t *auxNodo;

    auxNodo = l->ini;

    /* se a lista está vazia, não imprime nada */
    if(lista_vazia(l))
        return;

    while(auxNodo->prox != NULL) {
        printf("%d ", auxNodo->elemento);
        auxNodo = auxNodo->prox;
    }
    printf("%d\n", auxNodo->elemento);
}