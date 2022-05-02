#ifndef _LIBgrupo_t_H
#define _LIBgrupo_t_H

typedef struct pessoa_t {
    int ticket;
    int vacinada;
    int comMascara;
    float dinheiro;
    struct pessoa_t *prox;
} pessoa_t;

struct grupo {
    pessoa_t* ini;        /* ponteiro para o inicio do grupo */
    pessoa_t* fim;        /* ponteiro para o fim do grupo  */
    int tamanho;          /* numero de pessoas no grupo    */
};
typedef struct grupo grupo_t;

/*
 * Cria um grupo vazio e o retorna, se falhar retorna NULL.
*/
grupo_t* grupo_cria();

/*
 * Remove todos as pessoas do grupo, libera espaco e devolve NULL.
*/
grupo_t* grupo_destroi(grupo_t* g);

/*
 * Retorna 1 se o grupo esta vazio e 0 caso contrario.
*/
int grupo_vazio(grupo_t* f);

/*
 * Retorna o tamanho do grupo, isto eh, o numero de pessoas presentes nele.
*/
int grupo_tamanho(grupo_t* f);

/*
 * Cria e insere a pessoa no final do grupo (politica FIFO).
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int grupo_insere(grupo_t *f, int ticket, int vac, int masc, float din);

/*
 * Procura pela pessoa através do ticket;
 * Se estiver no grupo, retorna o ponteiro,
 * Se não, retorna NULL
*/
pessoa_t *procura_pessoa(grupo_t *f, int ticket);

/*
 * Cria pessoa e retorna o ponteiro em caso de sucesso
 * retorna NULL caso contrario
 */
pessoa_t *cria_pessoa(int ticket, int vac, int masc, float din);

/* 
 * Retorna 1 se tomou vacina
 * retorna 0 caso contrário 
 */
int eh_vacinada(pessoa_t *pessoa);

/* 
 * Retorna 1 se tem máscara
 * retorna 0 caso contrário
 */
int tem_mascara(pessoa_t *pessoa);

/* 
 * Retorna 1 se tem 3.80
 * retorna 0 caso contrário
 */
int tem_dinheiro(pessoa_t *pessoa);

#endif