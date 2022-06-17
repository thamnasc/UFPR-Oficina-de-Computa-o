#include "libpilha.h"
#include "libfila.h"
#include "liblista.h"
#include "libgrupo.h"
#include "libru.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PESSOAS 1000

void fiscalizaFila(armazenaVariaveis_t *var, pessoa_t *grupo) {

    int ticket;
    pessoa_t pessoa;

    while((! pilha_vazia(var->refeicoes)) && (! fila_vazia(var->atend))) {

        dequeue(var->atend, &ticket);
        pessoa = grupo[ticket];

        if(eh_vacinada(pessoa)) {
            if(tem_mascara(pessoa)) {

                    pop(var->refeicoes); /* Paga um bandejão */
                    var->ru->refeicoes += 130; /* Contabiliza compra */
            }

            else {
                if(! pilha_vazia(var->mascaras)) {
                    if(tem_dinheiro(pessoa)) {

                        pop(var->mascaras); /* Compra máscara */
                        var->ru->mascaras += 250; /* Contabiliza compra */
                        coloca_mascara(&pessoa);       
                        queue(var->atend, ticket); /* É reinserida ao final da fila */
                    }
                    
                    else /* Sem dinheiro para comprar máscara */
                        pessoa.status = 1; 
                }

                else /* Não há máscaras para comprar */
                    pessoa.status = 2;
            }
        }

        else /* Não vacinada */
            pessoa.status = 3;
        
        /* Insere na lista de tickets não utilizados */
        if((! tem_mascara(pessoa)) || (! eh_vacinada(pessoa))) 
            lista_insere_ordenado(var->naoAtend, ticket);

        grupo[ticket] = pessoa; /* Salva alteração de status */
    }
    
    /* Sem refeições restantes */
    if(pilha_vazia(var->refeicoes)) {
        
        while(! fila_vazia(var->atend)) {

            dequeue(var->atend, &ticket);
            lista_insere_ordenado(var->naoAtend, ticket);
            pessoa.status = 4; 
            grupo[ticket] = pessoa; /* Salva alteração de status */
        }
    }

    /* Tratativa de problema de casas decimais */
    var->ru->refeicoes = var->ru->refeicoes / 100;
    var->ru->mascaras = var->ru->mascaras / 100;

    /* Contabiliza total de ganho do RU */
    var->ru->total = var->ru->refeicoes + var->ru->mascaras;
}

int main() {

    pessoa_t grupo[PESSOAS];
    armazenaVariaveis_t *var;  

    /* Seed para gerar numeros aleatorios a partir do horario do computador */
    srand(time(0));

    /* Aloca memória e inicializa variáveis */
    if(! (var = inicializaVariaveis())) {
        printf("Erro durante a alocacao de memoria. \n");
        exit(1);
    }

    /* Cria pessoas aleatórias e salva tickets na fila de atendimento do ru */
    populaFilaRu(grupo, var->atend);

    printf("\nAbrindo o RU....\n");
    printf("\n==========A venda==========\n");
    printf("\t%d bandejoes \n", pilha_tamanho(var->refeicoes));
    printf("\t%d mascaras \n", pilha_tamanho(var->mascaras));
    printf("===========================\n\n");

    /* Verifica se a pessoa pode comprar a refeição, atualiza status de compra e
     * popula lista de tickets não atendidos */
    fiscalizaFila(var, grupo);

    imprimeContabilidade(var, grupo);

    /* Libera memória das variáveis alocadas dinamicamente */
    liberaMemoria(var);

    return 0;
}