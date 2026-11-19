#ifndef ESTOQUE_H
#define ESTOQUE_H
#include "produto.h"
#include "hash.h"
#include "abb.h"

int cadastrar_produto(Hash * h, ABB * a, int codigo, char * nome, float preco, int quantidade);

int atualizar_quantidade(Hash * h, int codigo, int nova_quantidade);

int alterar_preco(Hash * h, int codigo, float novo_preco);

int remover_produto(Hash * h, ABB * a, int codigo);

#endif