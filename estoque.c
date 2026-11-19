#include <stdlib.h>
#include "estoque.h"

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

    Produto * p = buscar_hash(h, codigo);

    if(p == NULL)
        return 0;

    p->quantidade = nova_quantidade;

    return 1;
}

int alterar_preco(Hash * h, int codigo, float novo_preco){
    if(h == NULL || novo_preco <= 0.0)
        return 0;

    Produto * p = buscar_hash(h, codigo);

    if(p == NULL)
        return 0;

    p->preco = novo_preco;

    return 1;
}

int remover_produto(Hash * h, ABB * a, int codigo){
    if(h == NULL || a == NULL)
        return 0;

    Produto * p = buscar_hash(h, codigo);

    if(p == NULL)
        return 0;

    if(buscar_abb(a, p->nome) != p)
        return 0;

    if(!remover_abb(a, p->nome))
        return 0;

    if(!remover_hash(h, codigo))
        return 0;

    free(p);

    return 1;
}