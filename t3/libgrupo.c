#include "libgrupo.h"
#include <stdlib.h>

void grupo_insere(pessoa_t *grupo, int ticket, int vac, int masc, float din) {

    pessoa_t pessoa;

    pessoa.ticket = ticket;
    pessoa.comMascara = masc;
    pessoa.vacinada = vac;
    pessoa.dinheiro = din;
    pessoa.status = 0;

    grupo[ticket] = pessoa;
}

int eh_vacinada(pessoa_t pessoa) {
    
    return (pessoa.vacinada == 1) ? 1 : 0;
}

int tem_mascara(pessoa_t pessoa) {

    return (pessoa.comMascara == 1) ? 1 : 0;
}

int tem_dinheiro(pessoa_t pessoa) {

    return (pessoa.dinheiro > 1.30) ? 1 : 0;
}

void coloca_mascara(pessoa_t *pessoa) {

    pessoa->comMascara = 1;
}

