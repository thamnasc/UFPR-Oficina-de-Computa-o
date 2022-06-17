#include "libru.h"
#include "libfila.h"
#include "libgrupo.h"
#include "libpilha.h"
#include "liblista.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PERC_VAC 99
#define PERC_MASC 99
#define PERC_DINHEIRO 60

int alet(int n, int m) {

    return (rand() % (m - n + 1)) + n;
}

int sorteiaNaProporcao(int PERC) {

    /* Se o número sorteado for menor que PERC, retorna 1, se não, 0 */
    return (alet(0, 100) < PERC) ? 1 : 0;
}

void populaFilaRu(pessoa_t *grupo, fila_t *atend) {

    int vac = 0, masc = 0, ticket = 0;
    float din = 0;

    for(ticket = 0; ticket <= 999; ticket++) {

        /* Sorteia se tomou vacina ou não */
        vac = sorteiaNaProporcao(PERC_VAC);

        /* Sorteia se tem máscara ou não */
        masc = sorteiaNaProporcao(PERC_MASC);

        /* Se o retorno for 1, atribui 1.30 para dinheiro, se não, 3.80 */
        din = sorteiaNaProporcao(PERC_DINHEIRO) ? 1.30 : 3.80;

        /* Insere pessoa no grupo */
        grupo_insere(grupo, ticket, vac, masc, din);

        /* Armazena o ticket das pessoas numa fila de atendimento */
        queue(atend, ticket);
    }
}

void imprimeContabilidade(armazenaVariaveis_t *var, pessoa_t *grupo) {
    
    int ticket;
    int semVac = 0, semMasc = 0, acabouMasc = 0, acabouRef = 0;
    int naoAtend = lista_tamanho(var->naoAtend);

    printf("Tickets não atendidos: \n\n");
    printf("Ticket \tMotivo \n");
    while(! lista_vazia(var->naoAtend)) {

        lista_retira_inicio(var->naoAtend, &ticket);

        if(grupo[ticket].status == 1) {
            printf("%d\tSem dinheiro para mascara \n", ticket);
            semMasc++;
        }
            
        if(grupo[ticket].status == 2) {
            printf("%d\tAcabaram as mascaras \n", ticket);
            acabouMasc++;
        }
            
        if(grupo[ticket].status == 3) {
            printf("%d\tSem vacina \n", ticket);
            semVac++;
        }

        if(grupo[ticket].status == 4) {
            printf("%d\tAcabaram as refeicoes \n", ticket);
            acabouRef++;
        }
    }

    printf("\nEncerrando o expediente....\n\n");
    printf("==============Contabilidade RU==============\n");
    printf(" Arrecadação com Refeições:     R$%.2f      \n", var->ru->refeicoes);
    printf(" Arrecadação com Máscaras:      R$%.2f      \n", var->ru->mascaras);
    printf(" Arrecadação Total:             R$%.2f      \n", var->ru->total);
    printf("============================================\n\n");

    printf("%d tickets nao foram utilizados: \n", naoAtend);
    printf("%d pessoas estavam sem vacina \n", semVac);
    printf("%d pessoas estavam sem dinheiro para comprar mascara \n", semMasc);
    printf("%d pessoas estavam sem mascara e nao havia para comprar \n", acabouMasc);
    printf("%d pessoas ficaram sem refeicao porque acabaram os bandejoes \n\n", acabouRef);
}

void preparaRefeicoes(pilha_t *refeicoes) {

    int i = 1;

    while(push(refeicoes, i) != -1) 
        i++;
}

void compraMascaras(pilha_t *mascaras) {

    int i = 1;

    while(push(mascaras, i) != -1) 
        i++;
}

armazenaVariaveis_t* inicializaVariaveis() {

    armazenaVariaveis_t *var; 
    pilha_t *refeicoes, *mascaras;
    fila_t *atend;
    lista_t *naoAtend;
    informacoesRu_t *ru;

    /* Atribui valor aleatorio para refeicoes disponíveis */
    if(! (refeicoes = pilha_cria(alet(500, 1000))))
        return NULL;

    preparaRefeicoes(refeicoes);
    
    /* Atribui valor aleatorio para mascaras disponiveis */
    if(! (mascaras = pilha_cria(alet(1, 100))))
       return NULL;

    compraMascaras(mascaras);

    /* Inicializa fila de atendimento do ru */
    if(! (atend = fila_cria())) 
        return NULL;

    /* Inicializa lista de tickets não utilizados */
    if(! (naoAtend = lista_cria())) 
        return NULL;

    /* Criação da struct para armazenar informaçoes do ru */
    if(! (ru = malloc(sizeof(informacoesRu_t)))) 
        return NULL;

    ru->total = 0;
    ru->refeicoes = 0;
    ru->mascaras = 0;
    
    /* Aloca memória para struct de variáveis do programa */
    if(! (var = malloc(sizeof(armazenaVariaveis_t)))) 
        return NULL;

    /* Armazena as variáveis na struct para organizar o código */
    var->refeicoes = refeicoes;
    var->mascaras = mascaras;
    var->atend = atend;
    var->naoAtend = naoAtend;
    var->ru = ru;

    return var;
}

void liberaMemoria(armazenaVariaveis_t *var) {

    /* Liberando memoria alocada dinamicante */

    var->refeicoes = pilha_destroi(var->refeicoes);
    var->mascaras = pilha_destroi(var->mascaras);
    var->atend = fila_destroi(var->atend);
    var->naoAtend = lista_destroi(var->naoAtend);
    free(var->ru);
    var->ru = NULL;
    free(var);
    var = NULL;
}