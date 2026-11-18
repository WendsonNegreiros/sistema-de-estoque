#ifndef ABB_H
#define ABB_H

#include "produto.h"

typedef struct abb  ABB;

ABB * criar_abb(void);

int inserir_abb(ABB * a, Produto * p);

Produto * buscar_abb(ABB* a, char* nome);

void listar_abb(ABB* a);

int remover_abb(ABB* a, char * nome);

void destruir_abb(ABB* a);

#endif
