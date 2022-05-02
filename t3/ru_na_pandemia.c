#include "libpilha.h"
#include "libfila.h"
#include "liblista.h"
#include "libgrupo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* em Curitiba há 1.963.726 habitantes
* e até o dia 29/04 1.671.819 receberam a primeira dose,
* então estou considerando a proporção 85 / 15 para vacinados
*/
#define PERC_VAC 85
#define PERC_MASC 95
#define PERC_DINHEIRO 60

/* struct para armazenar informacoes do RU */
typedef struct informacoes_t {
    float total;
    float refeicoes;
    float mascaras;
} informacoes_t;

/* retorna numero aleatorio no intervalo de n m */
int alet(int n, int m) {

    return (rand() % (m - n + 1)) + n;
}

/* sorteia cada atributo com chances nas proporcoes estipuladas */
int sorteia_na_proporcao(int PERC) {

    if(alet(0, 100) < PERC)
        return 1;
    else
        return 0;
}

/* retorna 1 se a criação das pessoas ocorreu com sucesso,
 * retorna 0 caso contrário
 */
int popula_fila_ru(grupo_t *grupo, fila_t *atend) {

    int vac = 0, masc = 0, i = 0;
    float din = 0;

    for(i = 1; i <= 1000; i++) {

        /* sorteia se tomou vacina ou não */
        vac = sorteia_na_proporcao(PERC_VAC);

        /* sorteia se tem máscara ou não */
        masc = sorteia_na_proporcao(PERC_MASC);

        /* sorteia o dinheiro */
        if(sorteia_na_proporcao(PERC_DINHEIRO))
            din = 1.30;
        else
            din = 3.80;
        
        /* insere pessoa na TAD */
        grupo_insere(grupo, i, vac, masc, din);
        /* armazena o ticket das pessoas numa fila de atendimento */
        queue(atend, i);
    }

    return 1;
}

void fiscaliza_fila(grupo_t *pessoas, fila_t *atend, lista_t *naoAtend, 
                    informacoes_t *info, pilha_t *refeicoes, pilha_t *mascaras, 
                    lista_t *semVac, lista_t *semMasc, lista_t *acabouMasc, lista_t *acabouRef) {

    int ticket;
    pessoa_t *pessoa;

    while((! pilha_vazia(refeicoes)) && (! fila_vazia(atend))) {

        dequeue(atend, &ticket);
        pessoa = procura_pessoa(pessoas, ticket);

        if(eh_vacinada(pessoa)) {
            if(tem_mascara(pessoa)) {
                    /* paga um bandejão */
                    pop(refeicoes);
                    /*contabiliza compra */
                    info->refeicoes += 130;
            }

            else {
                if(! pilha_vazia(mascaras)) {
                    if(tem_dinheiro(pessoa)) {
                        /* compra máscara */
                        pop(mascaras);
                        /* é reinserida ao final da fila */
                        queue(atend, ticket);
                        /*contabiliza compra */
                        info->mascaras += 250;
                    }
                    
                    /* sem dinheiro para comprar máscara */
                    else {
                        lista_insere_ordenado(semMasc, ticket);
                        lista_insere_ordenado(naoAtend, ticket);
                    }
                }

                /* não há máscaras para comprar */
                else {
                    lista_insere_ordenado(acabouMasc, ticket);
                    lista_insere_ordenado(naoAtend, ticket);
                }
            }
        }

        /* não vacinada */
        else {
            lista_insere_ordenado(semVac, ticket);
            lista_insere_ordenado(naoAtend, ticket);
        }
    }
    
    /* sem refeições restantes */
    if(pilha_vazia(refeicoes) && (! fila_vazia(atend))) {
        
        while(! fila_vazia(atend)) {
            dequeue(atend, &ticket);
            lista_insere_ordenado(naoAtend, ticket);
            lista_insere_ordenado(acabouRef, ticket);
        }
    }

    info->refeicoes = info->refeicoes / 100;
    info->mascaras = info->mascaras / 100;
    info->total = info->refeicoes + info->mascaras;
}

void imprime_contabilidade(informacoes_t *infos, lista_t *naoAtend, lista_t *semVac, 
                           lista_t *semMasc, lista_t *acabouMasc, lista_t *acabouRef) {
    
    int ticket;

    printf("Encerrando o expediente....\n\n");
    printf("==============Contabilidade RU==============\n");
    printf(" Arrecadação com Refeições:     R$%.2f      \n", infos->refeicoes);
    printf(" Arrecadação com Máscaras:      R$%.2f      \n", infos->mascaras);
    printf(" Arrecadação Total:             R$%.2f      \n", infos->total);
    printf("============================================\n\n");

    printf("%d tickets nao foram utilizados: \n", naoAtend->tamanho);
    printf("%d pessoas estavam sem vacina \n", lista_tamanho(semVac));
    printf("%d pessoas estavam sem dinheiro para comprar mascara \n", lista_tamanho(semMasc));
    printf("%d pessoas estavam sem mascara e nao havia para comprar \n", lista_tamanho(acabouMasc));
    printf("%d pessoas ficaram sem refeicao porque acabaram os bandejoes \n\n", lista_tamanho(acabouRef));

    printf("Tickets não atendidos: \n\n");
    printf("Ticket \tMotivo \n");
    while(! lista_vazia(naoAtend)) {
        lista_retira_inicio(naoAtend, &ticket);
        if(lista_pertence(semVac, ticket)) 
            printf("%d\tSem vacina \n", ticket);
        else if(lista_pertence(semMasc, ticket))
            printf("%d\tSem dinheiro para mascara \n", ticket);
        else if(lista_pertence(acabouMasc, ticket))
            printf("%d\tAcabaram as mascaras \n", ticket);
        else if(lista_pertence(acabouRef, ticket))
            printf("%d\tAcabaram as refeicoes \n", ticket);
    }
}

void prepara_refeicoes(pilha_t *refeicoes) {

    int i = 1;

    while(push(refeicoes, i) != -1) 
        i++;
}

void compra_mascaras(pilha_t *mascaras) {

    int i = 1;

    while(push(mascaras, i) != -1) 
        i++;
}

int main() {

    pilha_t *refeicoes, *mascaras;
    fila_t *atend;
    grupo_t *pessoas;
    lista_t *naoAtend;
    informacoes_t *info;
    lista_t *semVac, *semMasc, *acabouMasc, *acabouRef;

    /* seed para gerar numeros aleatorios a partir do horario do computador */
    srand(time(0));

    printf("\nAbrindo o RU....\n");
    printf("\n=====A venda=====\n");

    if(! (refeicoes = pilha_cria(alet(500, 1000)))) {
        printf("Erro durante a alocacao da pilha de bandejoes. \n");
        exit(1);
    }
    prepara_refeicoes(refeicoes);
    printf("%d bandejoes \n", pilha_tamanho(refeicoes));
    
    if(! (mascaras = pilha_cria(alet(1, 100)))) {
        printf("Erro durante a alocacao da pilha de mascaras. \n");
        exit(1);
    }
    compra_mascaras(mascaras);
    printf("%d mascaras \n", pilha_tamanho(mascaras));
    printf("=================\n\n");

    if(! (atend = fila_cria())) {
        printf("Erro durante a alocacao da fila de atendimento. \n");
        exit(1);
    }
    if(! (pessoas = grupo_cria())) {
        printf("Erro durante a alocacao da fila do RU. \n");
        exit(1);
    }
    if(! (naoAtend = lista_cria())) {
        printf("Erro durante a alocacao de tickets nao atendidos. \n");
        exit(1);
    }
    if(! (semVac = lista_cria())) {
        printf("Erro durante a alocacao de lista para quem estava sem vacina. \n");
        exit(1);
    }
    if(! (semMasc = lista_cria())) {
        printf("Erro durante a alocacao de lista para quem estava sem mascara. \n");
        exit(1);
    }
    if(! (acabouMasc = lista_cria())) {
        printf("Erro durante a alocacao da lista para quando acabou as mascaras. \n");
        exit(1);
    }
    if(! (acabouRef = lista_cria())) {
        printf("Erro durante a alocacao da lista para quando acabou as refeicoes. \n");
        exit(1);
    }

    /* criação da struct para armazenar informaçoes */
    if(! (info = malloc(sizeof(informacoes_t)))) {
        printf("Erro durante a alocacao da struct de informacoes. \n");
        exit(1);
    }
    info->total = 0;
    info->refeicoes = 0;
    info->mascaras = 0;

    if(! (popula_fila_ru(pessoas, atend))) {
        printf("Erro durante a criaçao das structs de pessoas. \n");
        exit(1);
    }
    
    fiscaliza_fila(pessoas, atend, naoAtend, info, refeicoes, 
                   mascaras, semVac, semMasc, acabouMasc, acabouRef);

    imprime_contabilidade(info, naoAtend, semVac, semMasc, acabouMasc, acabouRef);

    /* liberando memoria alocada dinamicante */
    refeicoes = pilha_destroi(refeicoes);
    mascaras = pilha_destroi(mascaras);
    atend = fila_destroi(atend);
    pessoas = grupo_destroi(pessoas);
    naoAtend = lista_destroi(naoAtend);
    semVac = lista_destroi(semVac);
    semMasc = lista_destroi(semMasc);
    acabouMasc = lista_destroi(acabouMasc);
    acabouRef = lista_destroi(acabouRef);
    free(info);
    info = NULL;

    return 0;
}