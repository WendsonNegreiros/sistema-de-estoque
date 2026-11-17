#include "abb.h"
#include <stdlib.h>
#include <string.h>

typedef struct no_abb{
    Produto * produto;
    struct no_abb * esquerda;
    struct no_abb * direita;
}NoABB;

struct abb {
    NoABB* raiz;
};

ABB * criar_abb(void){
    ABB * a = malloc(sizeof(ABB));

    if(a != NULL)
        a->raiz = NULL;

    return a;
}

int inserir_abb(ABB * a, Produto * p){
    if(a == NULL || p == NULL)
        return 0;
    
    NoABB * atual = a->raiz;
    NoABB * pai = NULL;

    while(atual != NULL){
        int comparacao = strcmp(p->nome, atual->produto->nome);
        
        if(comparacao == 0)
            return 0;

        pai = atual;

        if(comparacao < 0)
            atual = atual->esquerda;
        else
            atual = atual->direita;
    }
    NoABB * novo = malloc(sizeof(NoABB));

    if(novo == NULL)
        return 0;

    novo->produto = p;
    novo->esquerda = NULL;
    novo->direita = NULL;

    if(pai == NULL)
        a->raiz = novo;
    else if(strcmp(p->nome, pai->produto->nome) < 0)
        pai->esquerda = novo;
    else
        pai->direita = novo;

    return 1;
}
