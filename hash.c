#include "produto.h"
#include "hash.h"
#include <stdlib.h>

#define TAM 101

typedef struct no {
    Produto* produto;
    struct no* prox;
} No;

struct hash {
    No* tabela[TAM];
};

int funcao_hash(int codigo){
    return codigo % TAM;
}

Hash * criar_hash(void){
    Hash * h = malloc(sizeof(Hash));

    if(h != NULL)
        for(int i = 0; i < TAM; i++){
            h->tabela[i] = NULL;
        }

    return h;
}

int inserir_hash(Hash * h, Produto * p){
    if (h == NULL || p == NULL)
        return 0;

    int posicao = funcao_hash(p->codigo);

    No * atual = h->tabela[posicao];

    while(atual != NULL){
        if(atual->produto->codigo == p->codigo)
            return 0;

        atual = atual->prox;
    }

    No * novo_no = malloc(sizeof(No));
    if(novo_no == NULL)
        return 0;
    
    novo_no->produto = p;
    novo_no->prox = h->tabela[posicao];
    h->tabela[posicao] = novo_no;

    return 1;
}

Produto * buscar_hash (Hash * h, int codigo){
    if(h == NULL || codigo <= 0)
        return NULL;

    int posicao = funcao_hash(codigo);

    No * atual = h->tabela[posicao];

    while (atual != NULL){
        if(atual->produto->codigo == codigo)
            return atual->produto;

        atual = atual->prox;
    }

    return NULL;
}

int remover_hash(Hash * h, int codigo){
    if(h == NULL || codigo <= 0)
        return 0;

    int posicao = funcao_hash(codigo);
    
    No * atual = h->tabela[posicao];
    No * anterior = NULL;

    while(atual != NULL){
        if(atual->produto->codigo == codigo){

            if(anterior == NULL)
                h->tabela[posicao] = atual->prox;
            else
                anterior->prox = atual->prox;
            free(atual);
            return 1;
        }

        anterior = atual;
        atual = atual->prox;
    }
}

void destruir_hash(Hash * h){
    if(h==NULL)
        return;
    
    for(int i = 0; i < TAM; i++){
        No * atual = h->tabela[i];

        while(atual != NULL){
            No * proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
    }
    free(h);
}