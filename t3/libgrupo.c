#include "libgrupo.h"
#include <stdlib.h>

grupo_t *grupo_cria() {

    grupo_t *auxGrupo;

    /* caso não seja bem sucedida a alocação */
    if(! (auxGrupo = malloc(sizeof(grupo_t))))
        return NULL;

    auxGrupo->ini = NULL;
    auxGrupo->fim = NULL;

    /* zero pessoas ao iniciar */
    auxGrupo->tamanho = 0;

    return auxGrupo;
}

grupo_t *grupo_destroi(grupo_t *g) {
    
    pessoa_t *auxPessoa;

    if(grupo_vazio(g)) {
        free(g);
        return NULL;
    } 

    auxPessoa = g->ini;

    /* primeiro libera espaço da struct das pessoas */
    while(auxPessoa->prox != NULL) {
        g->ini = g->ini->prox;
        free(auxPessoa);
        auxPessoa = g->ini;
    }

    free(auxPessoa);
    free(g);

    /* devolve NULL para o grupo */
    return NULL;
}

int grupo_vazio(grupo_t *g) {

    if(g->tamanho == 0)
        return 1;

    return 0;
}

int grupo_tamanho(grupo_t *g) {

    return g->tamanho;
}

int grupo_insere(grupo_t *g, int ticket, int vac, int masc, float din) {

    pessoa_t *pessoa;

    if(! (pessoa = cria_pessoa(ticket, vac, masc, din)))
        return 0;

    if(grupo_vazio(g)) {
        g->ini = pessoa;
        g->fim = pessoa;
        g->tamanho++;

        return 1;
    }

    g->fim->prox = pessoa;
    g->fim = pessoa;
    g->tamanho++;

    return 1;
}

pessoa_t *procura_pessoa(grupo_t *g, int ticket) {

    pessoa_t *auxPessoa;

    /* não há pessoas no grupo */
    if(grupo_vazio(g))
        return 0;

    auxPessoa = g->ini;

    /* procura pela pessoa */
    while((auxPessoa->ticket != ticket) && 
          (auxPessoa->prox != NULL))
        auxPessoa = auxPessoa->prox;

    /* não encontrada */
    if(auxPessoa->ticket != ticket)
        return NULL;
        
    /* pessoa encontrada */
    return auxPessoa;
}

pessoa_t *cria_pessoa(int ticket, int vac, int masc, float din) {

    pessoa_t *pessoa;

    if(! (pessoa = malloc(sizeof(pessoa_t))))
        return NULL;

    pessoa->ticket = ticket;
    pessoa->comMascara = masc;
    pessoa->vacinada = vac;
    pessoa->dinheiro = din;
    pessoa->prox = NULL;

    return pessoa;
}

int eh_vacinada(pessoa_t *pessoa) {

    if(pessoa->vacinada)
        return 1;
    else 
        return 0;
}

int tem_mascara(pessoa_t *pessoa) {

    if(pessoa->comMascara)
        return 1;
    else
        return 0;
}

int tem_dinheiro(pessoa_t *pessoa) {

    if(pessoa->dinheiro > 1.30)
        return 1;
    else
        return 0;
}

void coloca_mascara(pessoa_t *pessoa) {

    pessoa->comMascara = 1;
}

