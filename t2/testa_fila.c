#include "libfila.h"
#include <stdio.h>

int main() {

    fila_t *fila;
    int elemento = 5, i = 1;

    fila = fila_cria();

    printf("A fila foi criada com sucesso? \n");
    if(fila)
        printf("Sim \n");
    else
        printf("Não, ocorreu um erro ao criar a fila \n");

    printf("A fila está vazia? \n");
    if(fila_vazia(fila)) {
        printf("Sim \n");
        printf("E, portanto, contém %d elementos \n", fila->tamanho);
        printf("Testando se a fila imprime quando está vazia.... \n\n");
        fila_imprime(fila);
    }
    else
        printf("Não, a fila contém elementos! \n\n");
    
    printf("Testando destruir fila após ter desenfileirado o último elemento: \n");
    queue(fila, elemento);
    dequeue(fila, &elemento);
    printf("Destruindo fila....\n\n");
    fila = fila_destroi(fila);

    printf("Criando nova fila.... \n");
    fila = fila_cria();

    printf("Testando desenfileirar com a fila vazia: \n");
    if(dequeue(fila, &elemento))
        printf("Tentativa de dequeue realizada com sucesso. \n O elemento retirado foi %d \n\n", elemento);
    else
        printf("Tentativa falha de dequeue, pois a fila está vazia \n\n");
    
    printf("Enfileirando elementos: \n");

    for(i = 1; i <= 9; i++) {
        if(queue(fila, i))
            printf("O elemento %d foi enfileirado! \n", i);
        else
            printf("Ocorreu um erro ao tentar enfileirar o elemento %d! \n", i);
    }
    printf("Há %d elementos enfileirados! \n\n", fila->tamanho);

    printf("Testando imprimir a fila não vazia: \n");
    fila_imprime(fila);
    printf("\n\n");

    printf("Verificando se a fila retorna como não vazia caso tenha elementos: \n");
    if(! fila_vazia(fila))
        printf("A fila não está vazia! \n\n");
    else
        printf("A fila está vazia \n\n");
    
    printf("Testando desenfileirar todos os elementos com dequeue: \n");
    while(dequeue(fila, &elemento)) 
        printf("Elemento %d desenfileirado com sucesso! \n", elemento);
    if(fila_vazia(fila))
        printf("Todos os elementos foram desenfileirados! \n\n");
    else
        printf("Ainda restam elementos na fila \n\n");

    printf("Enfileirando elementos para liberar seus espaços quando for destruir a fila: \n");
    for(i = 1; i <= 9; i++) {
        if(queue(fila, i))
            printf("O elemento %d foi enfileirado! \n", i);
        else
            printf("Ocorreu um erro ao tentar enfileirar o elemento %d! \n", i);
    }
    printf("Destruindo fila.... \n");
    fila = fila_destroi(fila);

    return 0;
}