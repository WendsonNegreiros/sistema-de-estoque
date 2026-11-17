#include "produto.h"
#include <stdlib.h>
#include <string.h>

Produto* criar_produto(int codigo, char* nome, float preco, int qnt){
    if (codigo <= 0 || preco < 0.0 || qnt < 0 || strcmp(nome, "") == 0 || strlen(nome) > 50)
        return NULL;

    Produto* p = malloc(sizeof(Produto));    
    if(p != NULL)
        p->codigo = codigo;
        strcpy(p->nome, nome);
        p->preco = preco;
        p->quantidade = qnt;

    return p;
}
