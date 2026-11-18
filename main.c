#include <stdio.h>
#include <stdlib.h>
#include "produto.h"
#include "hash.h"
#include "abb.h"

int cadastrar_produto(Hash * h, ABB * a, int codigo, char * nome, float preco, int quantidade){
    if(h == NULL || a == NULL || nome == NULL)
        return 0;

    if(buscar_hash(h, codigo) != NULL || buscar_abb(a, nome) != NULL)
        return 0;

    Produto * p = criar_produto(codigo, nome, preco, quantidade);

    if(p == NULL)
        return 0;

    if(!inserir_hash(h, p)){
        free(p);
        return 0;
    }

    if(!inserir_abb(a, p)){
        remover_hash(h, codigo);
        free(p);
        return 0;
    }

    return 1;
}

int atualizar_quantidade(Hash* h, int codigo, int nova_quantidade){
    if(h == NULL || nova_quantidade < 0)
        return 0;

    Produto* p = buscar_hash(h, codigo);

    if(p == NULL)
        return 0;

    p->quantidade = nova_quantidade;

    return 1;
}

int main(){
    Hash* h = criar_hash();
    ABB* a = criar_abb();

    if(h == NULL || a == NULL){
        puts("Erro ao criar estruturas");
        destruir_hash(h);
        destruir_abb(a);
        return 1;
    }

    if(!cadastrar_produto(h, a, 101, "Macarrao", 4.90, 60)){
        puts("Erro ao cadastrar produto");
        destruir_hash(h);
        destruir_abb(a);
        return 1;
    }

    Produto* p1 = buscar_hash(h, 101);
    Produto* p2 = buscar_abb(a, "Macarrao");

    if(p1 != NULL && p1 == p2)
        puts("Hash e ABB apontam para o mesmo produto");
    else
        puts("Erro na integracao");
    
    printf("\nQuantidade antes: %d\n", p1->quantidade);

    if(atualizar_quantidade(h, 101, 100))
        puts("Quantidade atualizada com sucesso");
    else
        puts("Erro ao atualizar quantidade");

    Produto* teste = buscar_abb(a, "Macarrao");

    if(teste != NULL)
        printf("Quantidade na ABB: %d\n", teste->quantidade);

    destruir_hash(h);
    destruir_abb(a);
    free(p1);

    return 0;
}