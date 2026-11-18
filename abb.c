#include "abb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

Produto * buscar_abb(ABB * a, char * nome){
    if(a == NULL || nome == NULL)
        return NULL;

    NoABB * atual = a->raiz;

    while(atual != NULL){
        int cmp = strcmp(nome, atual->produto->nome);

        if(cmp == 0)
            return atual->produto;

        if(cmp < 0)
            atual = atual->esquerda;
        else
            atual = atual->direita;
    }

    return NULL;
}

static void em_ordem(NoABB* no){
    if(no == NULL)
        return;

    em_ordem(no->esquerda);

    printf("Codigo: %d | Nome: %s | Preco: R$ %.2f | Quantidade: %d\n", no->produto->codigo, no->produto->nome, no->produto->preco, no->produto->quantidade);

    em_ordem(no->direita);
}

void listar_abb(ABB * a){
    if(a == NULL)
        return;

    if(a->raiz == NULL){
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    em_ordem(a->raiz);
}

int remover_abb(ABB * a, char * nome){
    if(a == NULL || nome == NULL)
        return 0;

    NoABB * atual = a->raiz;
    NoABB * pai = NULL;

    while(atual != NULL){
        int comparacao = strcmp(nome, atual->produto->nome);

        if(comparacao == 0)
            break;

        pai = atual;

        if(comparacao < 0)
            atual = atual->esquerda;
        else
            atual = atual->direita;
    }

    if(atual == NULL)
        return 0;

    if(atual->esquerda == NULL && atual->direita == NULL){
        if(pai == NULL)
            a->raiz = NULL;
        else if(pai->esquerda == atual)
            pai->esquerda = NULL;
        else
            pai->direita = NULL;

        free(atual);
        return 1;
    }

    if(atual->esquerda == NULL || atual->direita == NULL){
        NoABB * filho;

        if(atual->esquerda != NULL)
            filho = atual->esquerda;
        else
            filho = atual->direita;

        if(pai == NULL)
            a->raiz = filho;
        else if(pai->esquerda == atual)
            pai->esquerda = filho;
        else
            pai->direita = filho;

        free(atual);
        return 1;
}

    NoABB* pai_sucessor = atual;
    NoABB* sucessor = atual->direita;

    while(sucessor->esquerda != NULL){
        pai_sucessor = sucessor;
        sucessor = sucessor->esquerda;
    }

    Produto* temp = atual->produto;
    atual->produto = sucessor->produto;
    sucessor->produto = temp;

    if(pai_sucessor->esquerda == sucessor)
        pai_sucessor->esquerda = sucessor->direita;
    else
        pai_sucessor->direita = sucessor->direita;

    free(sucessor);
    return 1;
}

static void destruir_nos(NoABB * no){
    if(no == NULL)
        return;

    destruir_nos(no->esquerda);
    destruir_nos(no->direita);

    free(no);
}

void destruir_abb(ABB* a){
    if(a == NULL)
        return;

    destruir_nos(a->raiz);

    free(a);
}
