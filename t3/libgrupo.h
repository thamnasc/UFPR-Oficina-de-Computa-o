#ifndef _LIBgrupo_t_H
#define _LIBgrupo_t_H

/*  Status ru:
    0 - default
    1 - sem dinheiro para comprar máscara
    2 - acabaram as máscaras para comprar
    3 - não vacinada
    4 - acabaram as refeições
*/
typedef struct pessoa_t {
    int ticket;
    int vacinada;
    int comMascara;
    float dinheiro;
    int status; 
    struct pessoa_t *prox;
} pessoa_t;

/*
 * Cria e insere a pessoa no índice equivalente ao seu ticket.
*/
void grupo_insere(pessoa_t *g, int ticket, int vac, int masc, float din);

/* 
 * Retorna 1 se tomou vacina
 * Retorna 0 caso contrário 
 */
int eh_vacinada(pessoa_t pessoa);

/* 
 * Retorna 1 se tem máscara
 * Retorna 0 caso contrário
 */
int tem_mascara(pessoa_t pessoa);

/* 
 * Retorna 1 se tem 3.80
 * Retorna 0 caso contrário
 */
int tem_dinheiro(pessoa_t pessoa);

/* 
 * Atribui estado 1 para comMascara
 */
void coloca_mascara(pessoa_t *pessoa);

#endif