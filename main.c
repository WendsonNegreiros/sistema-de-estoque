#include <stdio.h>
#include <stdlib.h>
#include "produto.h"
#include "hash.h"

int main(){
    Hash* h = criar_hash();

    if(h == NULL){
        puts("Erro ao criar a tabela");
        return 1;
    }

    Produto* p1 = criar_produto(101, "Macarrao", 4.90, 60);
    Produto* p2 = criar_produto(202, "Produto Teste", 9.90, 5);

    if(p1 == NULL || p2 == NULL){
        puts("Erro ao criar produtos");
        destruir_hash(h);
        free(p1);
        free(p2);
        return 1;
    }

    if(!inserir_hash(h, p1) || !inserir_hash(h, p2)){
        puts("Erro ao inserir produtos na hash");
        destruir_hash(h);
        free(p1);
        free(p2);
        return 1;
    }

    Produto* encontrado = buscar_hash(h, 101);

    if(encontrado != NULL)
        printf("Encontrado: %d - %s\n", encontrado->codigo, encontrado->nome);
    else
        puts("Produto 101 nao encontrado");

    encontrado = buscar_hash(h, 202);

    if(encontrado != NULL)
        printf("Encontrado: %d - %s\n", encontrado->codigo, encontrado->nome);
    else
        puts("Produto 202 nao encontrado");

    encontrado = buscar_hash(h, 999);

    if(encontrado == NULL)
        puts("Produto 999 nao encontrado");

    if(remover_hash(h, 101))
        puts("Produto 101 removido com sucesso");
    else
        puts("Erro ao remover produto 101");
    if(remover_hash(h, 303))
        puts("Produto 303 removido");
    else
        puts("Produto 303 nao encontrado");

    if(buscar_hash(h, 202) != NULL)
        puts("Produto 202 permanece cadastrado");
    Produto* teste = buscar_hash(h, 101);

    if(teste == NULL)
        puts("Produto 101 nao esta mais na Hash");

    teste = buscar_hash(h, 202);

    if(teste != NULL)
        puts("Produto 202 continua cadastrado");

    destruir_hash(h);
    free(p1);
    free(p2);

    return 0;
}