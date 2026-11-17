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
