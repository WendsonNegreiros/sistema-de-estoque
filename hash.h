#ifndef HASH_H
#define HASH_H

typedef struct hash Hash;

Hash * criar_hash(void);

int inserir_hash(Hash * h, Produto * p);

Produto * buscar_hash(Hash * h, int codigo);

int remover_hash(Hash * h, int codigo);

void destruir_hash(Hash * h); 

void calcular_estatisticas(Hash * h, int * total_produtos, int * total_unidades);

#endif