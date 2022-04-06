#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libpilha.h"
#define MAX_ELEM 200

/* retorna 1 quando corresponde a 
 * algum dos três caracteres de abertura,
 * retorna 0 caso contrário */
int ehCharAbertura(char caracter) {

    switch(caracter) {
        case '(':
        case '{':
        case '[':
            return 1;
            break;
        default:
            return 0;
    }
}

/* retorna 1 quando corresponde a 
 * algum dos três caracteres de fechamento,
 * retorna 0 caso contrário */
int ehCharFechamento(char caracter) {

    switch(caracter) {
        case ')':
        case '}':
        case ']':
            return 1;
            break;
        default:
            return 0;
    }
}

/* retorna 1 quando os pares estão corretos,
 * retorna 0 caso contrário */
int ehParCorreto(char topo, char fecha) {

    if((topo == '(') && (fecha == ')'))
        return 1;
    if((topo == '{') && (fecha == '}'))
        return 1;
    if((topo == '[') && (fecha == ']'))
        return 1;

    return 0;
}

int main() {

    pilha_t *pilha;
    char expressao[MAX_ELEM * 2], topo, caracter;
    int i = 0; 
    
    if(! (pilha = inicializa_pilha(MAX_ELEM))) {
        fprintf(stderr, "A alocacao nao obteve sucesso \n");
        
        /* para a shell, 1 representa erro */
        exit(1);
    }

    /* lê duas vezes o que a pilha pode empilhar, porque
     * empilhamos apenas o caracter de abertura */
    fgets(expressao, MAX_ELEM * 2, stdin);

    /* o fgets lê até encontrar o newline, mas o inclui
     * na string, então é preciso substituir o 
     * último caracter */
    expressao[strcspn(expressao, "\n")] = '\0';

    /* percorre a string */
    while((caracter = expressao[i]) != '\0') {

        if(ehCharAbertura(caracter)) {
            if(push(pilha, caracter) == -1) {
                /* a pilha está cheia */
                destroi_pilha(pilha);
                return 0;
            }
        }

        /* se o caracter for de fechamento */
        else if(ehCharFechamento(caracter)) {

            if(! pilha_vazia(pilha)) {
                topo = pop(pilha);

                /* verifica o topo da pilha com o caracter de fechamento */
                if(! ehParCorreto(topo, caracter)) {
                /* caracter não correspondente */
                    destroi_pilha(pilha);
                    return 0;
                }
            }
            /* pilha vazia, o caracter de fechamento está sobrando */
            else {
                destroi_pilha(pilha);
                return 0;
            }
        }

        /* caracter inválido */
        else {
            destroi_pilha(pilha);
            return 0;
        }
        
        i++;
    }

    /* sobrou caracteres, expressão inválida */
    if(! pilha_vazia(pilha)) {
        destroi_pilha(pilha);
        return 0;
    }

    destroi_pilha(pilha);
    
    /* expressão válida */
    return 1;
}
