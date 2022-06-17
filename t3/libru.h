#ifndef _LIBru_t_H
#define _LIBru_t_H
#include "libpilha.h"
#include "libfila.h"
#include "liblista.h"
#include "libgrupo.h"

/* Struct para armazenar informacoes do RU */
typedef struct informacoesRu_t {
    float total;
    float refeicoes;
    float mascaras;
} informacoesRu_t;

/* Struct para armazenar variáveis para organizar o código */
typedef struct armazenaVariaveis_t {
    pilha_t *refeicoes;
    pilha_t *mascaras;
    fila_t *atend;
    lista_t *naoAtend;
    informacoesRu_t *ru;
} armazenaVariaveis_t;

/* Retorna numero aleatorio no intervalo de [n, m] */
int alet(int n, int m);

/* Sorteia cada atributo com chances nas proporcoes estipuladas */
int sorteiaNaProporcao(int PERC);

/* Cria pessoas aleatórias, populando o grupo de pessoas
 * e cria fila de atendimento do ru
 */
void populaFilaRu(pessoa_t *grupo, fila_t *atend);

/* Imprime os ganhos e os motivos para os tickets não utilizados */
void imprimeContabilidade(armazenaVariaveis_t *var, pessoa_t *grupo);

/* Popula pilha de refeições com valor aleatório sorteado entre 500 e 1000 */
void preparaRefeicoes(pilha_t *refeicoes);

/* Popula pilha de máscaras com valor aleatório sorteado entre 1 e 100 */
void compraMascaras(pilha_t *mascaras);

/* Aloca memória e inicializa variáveis */
armazenaVariaveis_t* inicializaVariaveis();

/* Libera memória alocada dinamicamente */
void liberaMemoria(armazenaVariaveis_t *var);

#endif