#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
} Produto;

Produto* criar_produto(int codigo, char* nome, float preco, int qnt);

#endif