#include "libpilha.h"
#include <stdio.h>
#define MAX_ELEM 200

int main() {

    pilha_t *pilha;
    int elemento = 5, i = 0;

    pilha = pilha_cria(MAX_ELEM);

    printf("A pilha foi criada com sucesso? \n");
    if(pilha)
        printf("Sim \n");
    else
        printf("Não, ocorreu um erro ao criar a pilha \n");
    
    printf("A pilha está vazia? \n");
    if(pilha_vazia(pilha)) {
        printf("Sim \n");
        printf("E, portanto, contém %d elementos \n", pilha_tamanho(pilha));
        printf("Testando se a pilha imprime quando está vazia.... \n\n");
        pilha_imprime(pilha); 
    }
    else
        printf("Não, a pilha contém elementos! \n\n"); 
    
    printf("Testando destruir a pilha após ter desempilhado o último elemento: \n");
    push(pilha, elemento);
    elemento = pop(pilha);
    printf("Destruindo pilha....\n\n");
    pilha = pilha_destroi(pilha);

    printf("Criando nova pilha.... \n");
    pilha = pilha_cria(MAX_ELEM);

    printf("Testando desempilhar com a pilha vazia: \n");
    if((elemento = pop(pilha)))
        printf("Tentativa de pop realizada com sucesso. \n O elemento retirado foi %d \n\n", elemento);
    else
        printf("Tentativa falha de pop, pois a pilha está vazia \n\n");
    
    printf("Empilhando elementos: \n");

    for(i = 1; i <= MAX_ELEM + 3; i++) {
        if(push(pilha, i) != -1)
            printf("O elemento %d foi empilhado! \n", i);
        else
            printf("A pilha está cheia! Não foi possível empilhar o elemento %d! \n", i);
    }
    printf("Há %d elementos empilhados! \n\n", pilha_tamanho(pilha));

    printf("Testando imprimir a pilha não vazia: \n");
    pilha_imprime(pilha);
    printf("\n\n");

    printf("Verificando se a pilha retorna como não vazia caso tenha elementos: \n");
    if(pilha_vazia(pilha))
        printf("A pilha está vazia \n\n");
        
    else
        printf("A pilha não está vazia! \n\n");

    printf("Verifica o elemento que está no topo sem desempilhar: %d \n\n", pilha_topo(pilha));
    
    printf("Testando desempilhar todos os elementos com pop: \n");
    while((elemento = pop(pilha)))
        printf("Elemento %d desempilhado com sucesso! \n", elemento);
    
    printf("\nVerificando se a pilha está vazia: \n");
    if(pilha_vazia(pilha))
        printf("Todos os elementos foram desempilhados! \n\n");
    else
        printf("Ainda contém elementos na pilha \n\n");

    printf("Empilhando para destruir pilha com elementos: \n");
    for(i = 1; i <= 9; i++) {
        if(push(pilha, i) != -1)
            printf("O elemento %d foi empilhado! \n", i);
        else
            printf("A pilha está cheia! Não foi possível empilhar o elemento %d! \n", i);
    }
    printf("Destruindo pilha.... \n");
    pilha = pilha_destroi(pilha);

    return 0;
}