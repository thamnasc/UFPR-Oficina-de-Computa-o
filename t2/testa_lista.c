#include "liblista.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    
    lista_t *lista;
    int elemento = 5, i;

    lista = lista_cria();
    printf("Verificando se a lista foi criada: \n");
    if(lista)
        printf("Lista criada com sucesso! \n\n");
    else
        printf("Ocorreu um erro ao criar a lista. \n\n");
    
    printf("A lista está vazia? \n");
    if(lista_vazia(lista)) {
        printf("Sim \n");
        printf("E, portanto, contém %d elementos \n", lista_tamanho(lista));
        printf("Testando se a lista imprime quando está vazia.... \n\n");
        lista_imprime(lista); 
    }
    else
        printf("Não, a lista contém elementos! \n\n"); 
    
    printf("Testando inserir pelo início em lista vazia: \n");
    if(lista_insere_inicio(lista, elemento))
        printf("Operação realizada com sucesso \n");
    else
        printf("A operação não foi bem sucedida \n");
    lista_imprime(lista);
    printf("\n\n");

    printf("Testando inserir pelo fim em lista não vazia: \n");
    if(lista_insere_fim(lista, 3))
        printf("Operacao realizada com sucesso \n");
    else
        printf("A operação não foi bem sucedida \n");
    lista_imprime(lista);
    printf("\n\n");

    printf("Testando inserir pelo início em lista não vazia: \n");
    if(lista_insere_inicio(lista, 7))
        printf("Operacao realizada com sucesso \n");
    else
        printf("A operação não foi bem sucedida \n");
    lista_imprime(lista);
    printf("\n\n");

    printf("Testando inserir ordenado em lista não ordenada: \n");
    if(lista_insere_ordenado(lista, 2)) 
        printf("O elemento 2 foi inserido com sucesso! \n\n");
    else
        printf("A operação não foi bem sucedida \n\n");

    printf("Verificando remover pelo início: \n");
    if(lista_retira_inicio(lista, &elemento))
        printf("O elemento %d foi removido com sucesso \n", elemento);
    else
        printf("A operação não foi bem sucedida \n");
    lista_imprime(lista);
    printf("\n\n");

    printf("Verificando remover pelo fim: \n");
    if(lista_retira_fim(lista, &elemento))
        printf("O elemento %d foi removido com sucesso \n", elemento);
    else
        printf("A operação não foi bem sucedida \n");
    lista_imprime(lista);
    printf("\n\n");

    printf("Verificando se o elemento 5 está na lista: \n");
    if(lista_pertence(lista, 5))
        printf("O elemento 5 pertence a lista \n\n");
    else
        printf("O elemento 5 não pertence a lista \n\n");
    
    printf("Verificando se o elemento 1 pertence a lista: \n");
    if(lista_pertence(lista, 1))
        printf("O elemento 1 pertence a lista \n\n");
    else
        printf("O elemento 1 não pertence a lista \n\n");
    
    lista_retira_fim(lista, &elemento);

    printf("Tentando remover pelo início de uma lista vazia: \n");
    if(lista_retira_inicio(lista, &elemento))
        printf("O elemento %d foi removido com sucesso! \n\n", elemento);
    else
        printf("A operação não foi bem sucedida \n\n");

    printf("Tentando remover pelo fim de uma lista vazia: \n");
    if(lista_retira_fim(lista, &elemento))
        printf("O elemento %d foi removido com sucesso! \n\n", elemento);
    else
        printf("A operação não foi bem sucedida \n\n");
    
    printf("Verificando inserir pelo fim em lista vazia: \n");
    if(lista_insere_inicio(lista, 2))
        printf("O elemento 2 foi inserido com sucesso! \n\n");
    else
        printf("A operação não foi bem sucedida \n\n");
    
    printf("Testando inserir ordenado em lista vazia: \n");
    lista_retira_inicio(lista, &elemento);
    if(lista_insere_ordenado(lista, 9)) 
        printf("O elemento 9 foi inserido com sucesso! \n");
    else
        printf("Não foi possível inserir o elemento 9 \n");
    printf("Imprimindo lista atual: \n");
    lista_imprime(lista);
    printf("\n\n");

    printf("Inserindo ordenado na lista com apenas um elemento: \n");
    printf("Espera-se que insira no início \n");
    if(lista_insere_ordenado(lista, 3)) 
        printf("Elemento 3 inserido com sucesso! \n");
    else
        printf("A operação não foi bem sucedida \n");
    printf("Imprimindo lista atual: \n");
    lista_imprime(lista);
    printf("\n\n");

    printf("Verificando função retira_elemento: \n");
    printf("O elemento 3 deve ser removido \n");
    elemento = 3;
    if(lista_retira_elemento(lista, &elemento))
        printf("O elemento 3 foi removido com sucesso! \n\n");
    else
        printf("A operação não foi bem sucedida \n\n");

    printf("Inserindo ordenado na lista com apenas um elemento: \n");
    printf("Espera-se que insira no final \n");
    if(lista_insere_ordenado(lista, 12)) 
        printf("Elemento 12 inserido com sucesso! \n");
    else
        printf("A operação não foi bem sucedida \n");
    printf("Imprimindo lista atual: \n");
    lista_imprime(lista);
    printf("\n\n");

    printf("Inserindo ordenado na lista, espera-se que insira no meio \n");
    if(lista_insere_ordenado(lista, 10))
        printf("Elemento 10 inserido com sucesso! \n");
    else
        printf("A operação não foi bem sucedida \n");
    printf("Imprimindo lista atual: \n");
    lista_imprime(lista);
    printf("\n\n");

    printf("Inserindo ordenado na lista, espera-se que insira no meio \n");
    if(lista_insere_ordenado(lista, 11))
        printf("Elemento 11 inserido com sucesso! \n");
    else
        printf("A operação não foi bem sucedida \n");
    printf("Imprimindo lista atual: \n");
    lista_imprime(lista);
    printf("\n\n");

    printf("Retirando elementos da pilha até ficar vazia pelo fim: \n");
    while(lista_retira_fim(lista, &elemento))
        printf("O elemento %d foi retirado! \n", elemento);
    if(lista_vazia(lista)) 
        printf("A lista está vazia! \n\n");

    printf("Inserindo elementos: \n");
    for(i = 1; i <= 4; i++) {
        if(lista_insere_ordenado(lista, i))
            printf("O elemento %d foi inserido com sucesso! \n", i);
        else
            printf("Ocorreu um erro ao tentar inserir o elemento %d \n", i);
    }
    printf("Imprimindo lista atual: \n");
    lista_imprime(lista);
    printf("\n");
    printf("Quantos elementos há na lista? \n");
    printf("Há %d elementos \n", lista_tamanho(lista));
    printf("Retirando elementos pelo início até a lista ficar vazia: \n");
    while(lista_retira_inicio(lista, &elemento)) 
        printf("O elemento %d foi removido! \n", elemento);
    if(lista_vazia(lista)) 
    printf("A lista está vazia! \n\n");

    printf("Destruindo lista....\n");
    lista = lista_destroi(lista);


    return 0;
}