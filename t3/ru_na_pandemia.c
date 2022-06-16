#include "libpilha.h"
#include "libfila.h"
#include "liblista.h"
#include "libgrupo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PERC_VAC 99
#define PERC_MASC 98
#define PERC_DINHEIRO 60

/* Struct para armazenar informacoes do RU */
typedef struct informacoesRu_t {
    float total;
    float refeicoes;
    float mascaras;
} informacoesRu_t;

typedef struct armazenaVariaveis_t {
    pilha_t *refeicoes, *mascaras;
    fila_t *atend;
    lista_t *naoAtend;
    informacoesRu_t *ru;
    lista_t *semVac, *semMasc, *acabouMasc, *acabouRef;
} armazenaVariaveis_t;

/* Retorna numero aleatorio no intervalo de [n, m] */
int alet(int n, int m) {

    return (rand() % (m - n + 1)) + n;
}

/* Sorteia cada atributo com chances nas proporcoes estipuladas */
int sorteia_na_proporcao(int PERC) {

    /* se o número sorteado for menor que PERC, retorna 1, se não, 0 */
    return (alet(0, 100) < PERC) ? 1 : 0;
}

/* Retorna 1 se a criação das pessoas ocorreu com sucesso,
 * retorna 0 caso contrário
 */
int popula_fila_ru(pessoa_t *grupo, fila_t *atend) {

    int vac = 0, masc = 0, ticket = 0;
    float din = 0;
    pessoa_t *pessoa;

    for(ticket = 1; ticket <= 1000; ticket++) {

        /* Sorteia se tomou vacina ou não */
        vac = sorteia_na_proporcao(PERC_VAC);

        /* Sorteia se tem máscara ou não */
        masc = sorteia_na_proporcao(PERC_MASC);

        /* Se o retorno for 1, atribui 1.30 para dinheiro, se não, 3.80 */
        din = sorteia_na_proporcao(PERC_DINHEIRO) ? 1.30 : 3.80;
        
        /* Insere pessoa na TAD */
/*         if(! grupo_insere(grupo, ticket, vac, masc, din))
            return 0; */

        pessoa = cria_pessoa(ticket, vac, masc, din);

        grupo[ticket] = pessoa;

        /* Armazena o ticket das pessoas numa fila de atendimento */
        queue(atend, ticket);
    }

    return 1;
}

void fiscaliza_fila(armazenaVariaveis_t *variaveis, pessoa_t *grupo) {

    int ticket;
    pessoa_t pessoa;

    while((! pilha_vazia(variaveis->refeicoes)) && (! fila_vazia(variaveis->atend))) {

        dequeue(variaveis->atend, &ticket);
        /* pessoa = procura_pessoa(variaveis->pessoas, ticket); */
        pessoa = grupo[ticket];

        if(eh_vacinada(pessoa)) {
            if(tem_mascara(pessoa)) {

                    pop(variaveis->refeicoes); /* Paga um bandejão */
                    variaveis->ru->refeicoes += 130; /* Contabiliza compra */
            }

            else {
                if(! pilha_vazia(variaveis->mascaras)) {
                    if(tem_dinheiro(pessoa)) {

                        pop(variaveis->mascaras); /* Compra máscara */
                        variaveis->ru->mascaras += 250; /* Contabiliza compra */
                        coloca_mascara(pessoa);       
                        queue(variaveis->atend, ticket); /* É reinserida ao final da fila */
                    }
                    
                    /* Sem dinheiro para comprar máscara */
                    else {

                        lista_insere_ordenado(variaveis->semMasc, ticket);
                        pessoa.status = 1; /* status = 1 sem dinheiro para máscara */
                    }
                }

                /* Não há máscaras para comprar */
                else  {

                    lista_insere_ordenado(variaveis->acabouMasc, ticket);
                    pessoa.status = 2; /* status = 2 sem máscara para comprar */
                }
            }
        }

        /* Não vacinada */
        else {

            lista_insere_ordenado(variaveis->semVac, ticket);
            pessoa.status = 3; /* status = 3 não vacinada */
        }
        
        /* Insere na lista de tickets não utilizados */
        if((! tem_mascara(pessoa)) || (! eh_vacinada(pessoa))) 
            lista_insere_ordenado(variaveis->naoAtend, ticket);
    }
    
    /* Sem refeições restantes */
    if(pilha_vazia(variaveis->refeicoes)) {
        
        while(! fila_vazia(variaveis->atend)) {

            dequeue(variaveis->atend, &ticket);
            lista_insere_ordenado(variaveis->naoAtend, ticket);
            lista_insere_ordenado(variaveis->acabouRef, ticket);
            pessoa.status = 4; /* status = 4 acabaram as refeicoes */
        }
    }

    /* Tratativa de problema de casas decimais */
    variaveis->ru->refeicoes = variaveis->ru->refeicoes / 100;
    variaveis->ru->mascaras = variaveis->ru->mascaras / 100;

    variaveis->ru->total = variaveis->ru->refeicoes + variaveis->ru->mascaras;
}

void imprime_contabilidade(armazenaVariaveis_t *variaveis, pessoa_t *grupo) {
    
    int ticket;

    printf("Encerrando o expediente....\n\n");
    printf("==============Contabilidade RU==============\n");
    printf(" Arrecadação com Refeições:     R$%.2f      \n", variaveis->ru->refeicoes);
    printf(" Arrecadação com Máscaras:      R$%.2f      \n", variaveis->ru->mascaras);
    printf(" Arrecadação Total:             R$%.2f      \n", variaveis->ru->total);
    printf("============================================\n\n");

    printf("%d tickets nao foram utilizados: \n", lista_tamanho(variaveis->naoAtend));
    printf("%d pessoas estavam sem vacina \n", lista_tamanho(variaveis->semVac));
    printf("%d pessoas estavam sem dinheiro para comprar mascara \n", lista_tamanho(variaveis->semMasc));
    printf("%d pessoas estavam sem mascara e nao havia para comprar \n", lista_tamanho(variaveis->acabouMasc));
    printf("%d pessoas ficaram sem refeicao porque acabaram os bandejoes \n\n", lista_tamanho(variaveis->acabouRef));

    printf("Tickets não atendidos: \n\n");
    printf("Ticket \tMotivo \n");
    while(! lista_vazia(variaveis->naoAtend)) {

        lista_retira_inicio(variaveis->naoAtend, &ticket);

        if(grupo[ticket].status == 1) 
            printf("%d\tSem dinheiro para mascara \n", ticket);

        if(grupo[ticket].status == 2) 
            printf("%d\tAcabaram as mascaras \n", ticket);

        if(grupo[ticket].status == 3)
            printf("%d\tSem vacina \n", ticket);

        if(grupo[ticket].status == 4)
            printf("%d\tAcabaram as refeicoes \n", ticket);

/*         if(lista_pertence(variaveis->semVac, ticket)) 
            printf("%d\tSem vacina \n", ticket);

        else if(lista_pertence(variaveis->semMasc, ticket))
            printf("%d\tSem dinheiro para mascara \n", ticket);

        else if(lista_pertence(variaveis->acabouMasc, ticket))
            printf("%d\tAcabaram as mascaras \n", ticket);

        else if(lista_pertence(variaveis->acabouRef, ticket))
            printf("%d\tAcabaram as refeicoes \n", ticket); */
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

armazenaVariaveis_t* inicializaVariaveis(pessoa_t *grupo) {

    armazenaVariaveis_t *variaveis; 
    pilha_t *refeicoes, *mascaras;
    fila_t *atend;
    lista_t *naoAtend;
    informacoesRu_t *ru;
    lista_t *semVac, *semMasc, *acabouMasc, *acabouRef;

    /* atribui valor aleatorio para refeicoes disponíveis */
    if(! (refeicoes = pilha_cria(alet(500, 1000))))
        return NULL;

    prepara_refeicoes(refeicoes);
    
    /* atribui valor aleatorio para mascaras disponiveis */
    if(! (mascaras = pilha_cria(alet(1, 100))))
       return NULL;

    compra_mascaras(mascaras);

    /* inicializa fila do ru */
    if(! (atend = fila_cria())) 
        return NULL;

    /* inicializa grupo de pessoas */
/*     if(! (pessoas = malloc(sizeof(1000 * pessoa_t)))) 
        return NULL; */

    if(! (naoAtend = lista_cria())) 
        return NULL;

    if(! (semVac = lista_cria())) 
        return NULL;

    if(! (semMasc = lista_cria())) 
        return NULL;

    if(! (acabouMasc = lista_cria())) 
        return NULL;

    if(! (acabouRef = lista_cria())) 
        return NULL;

    /* Criação da struct para armazenar informaçoes do ru */
    if(! (ru = malloc(sizeof(informacoesRu_t)))) 
        return NULL;

    ru->total = 0;
    ru->refeicoes = 0;
    ru->mascaras = 0;

    if(! (popula_fila_ru(grupo, atend)))
        return NULL;
    
    if(! (variaveis = malloc(sizeof(armazenaVariaveis_t)))) 
        return NULL;

    /* armazena as variáveis na struct para organizar o código */
    variaveis->refeicoes = refeicoes;
    variaveis->mascaras = mascaras;
    variaveis->atend = atend;
    variaveis->naoAtend = naoAtend;
    variaveis->ru = ru;
    variaveis->semVac = semVac;
    variaveis->semMasc = semMasc;
    variaveis->acabouMasc = acabouMasc;
    variaveis->acabouRef = acabouRef; 

    return variaveis;
}

void liberaMemoria(armazenaVariaveis_t *variaveis) {

    /* Liberando memoria alocada dinamicante */

    variaveis->refeicoes = pilha_destroi(variaveis->refeicoes);
    variaveis->mascaras = pilha_destroi(variaveis->mascaras);
    variaveis->atend = fila_destroi(variaveis->atend);
    variaveis->naoAtend = lista_destroi(variaveis->naoAtend);
    variaveis->semVac = lista_destroi(variaveis->semVac);
    variaveis->semMasc = lista_destroi(variaveis->semMasc);
    variaveis->acabouMasc = lista_destroi(variaveis->acabouMasc);
    variaveis->acabouRef = lista_destroi(variaveis->acabouRef);
    free(variaveis->ru);
    variaveis->ru = NULL;
}

int main() {

    pessoa_t grupo[1000];
    armazenaVariaveis_t *variaveis;  

    /* Seed para gerar numeros aleatorios a partir do horario do computador */
    srand(time(0));

    if(! (variaveis = inicializaVariaveis(grupo))) {
        printf("Erro durante a alocacao de memoria. \n");
        exit(1);
    }

    printf("\nAbrindo o RU....\n");
    printf("\n==========A venda==========\n");
    printf("\t%d bandejoes \n", pilha_tamanho(variaveis->refeicoes));
    printf("\t%d mascaras \n", pilha_tamanho(variaveis->mascaras));
    printf("===========================\n\n");

    fiscaliza_fila(variaveis, grupo);

    imprime_contabilidade(variaveis, grupo);

    liberaMemoria(variaveis);

    return 0;
}