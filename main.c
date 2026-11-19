#include <stdio.h>
#include <stdlib.h>
#include "produto.h"
#include "hash.h"
#include "abb.h"
#include "estoque.h"

void exibir_menu(void){
    printf("\n===== SISTEMA DE ESTOQUE =====\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Consultar produto por codigo\n");
    printf("3 - Consultar produto por nome\n");
    printf("4 - Atualizar quantidade em estoque\n");
    printf("5 - Alterar preco\n");
    printf("6 - Remover produto\n");
    printf("7 - Listar produtos em ordem alfabetica\n");
    printf("8 - Exibir estatisticas\n");
    printf("0 - Encerrar\n");
    printf("Escolha uma opcao: ");
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

    int opcao;
    int c;

    do {
        exibir_menu();

        if(scanf("%d", &opcao) != 1){
            if(feof(stdin))
                break;

            puts("Entrada invalida");

            while((c = getchar()) != '\n' && c != EOF);

            continue;
        }

        while((c = getchar()) != '\n' && c != EOF);

        switch(opcao){
            case 0:
                puts("Encerrando o programa...");
                break;

            case 1: {
            int codigo, quantidade;
                float preco;
                char nome[50];

                printf("Digite o codigo: ");
                if(scanf("%d", &codigo) != 1){
                    puts("Codigo invalido!");
                    break;
                }

                printf("Digite o nome: ");
                if(scanf(" %49[^\n]", nome) != 1){
                    puts("Nome invalido!");
                    break;
                }

                printf("Digite o preco: ");
                if(scanf("%f", &preco) != 1){
                    puts("Preco invalido!");
                    break;
                }

                printf("Digite a quantidade: ");
                if(scanf("%d", &quantidade) != 1){
                    puts("Quantidade invalida!");
                    break;
                }

                if(cadastrar_produto(h, a, codigo, nome, preco, quantidade))
                    puts("Produto cadastrado com sucesso!");
                else
                    puts("Erro ao cadastrar produto!");

                break;
            }

            case 2: {
                int codigo;

                printf("Digite o codigo do produto: ");

                if(scanf("%d", &codigo) != 1){
                    puts("Codigo invalido!");

                    while((c = getchar()) != '\n' && c != EOF);

                    break;
                }

                while((c = getchar()) != '\n' && c != EOF);

                Produto* p = buscar_hash(h, codigo);

                if(p != NULL){
                    printf("\nCodigo: %d\n", p->codigo);
                    printf("Nome: %s\n", p->nome);
                    printf("Preco: R$ %.2f\n", p->preco);
                    printf("Quantidade: %d\n", p->quantidade);
                }
                else{
                    puts("Produto nao encontrado!");
                }

                break;
            }
            case 3: {
                char nome[50];

                printf("Digite o nome do produto: ");

                if(scanf(" %49[^\n]", nome) != 1){
                    puts("Nome invalido!");

                    while((c = getchar()) != '\n' && c != EOF);

                    break;
                }

                while((c = getchar()) != '\n' && c != EOF);

                Produto* p = buscar_abb(a, nome);

                if(p != NULL){
                    printf("\nCodigo: %d\n", p->codigo);
                    printf("Nome: %s\n", p->nome);
                    printf("Preco: R$ %.2f\n", p->preco);
                    printf("Quantidade: %d\n", p->quantidade);
                }
                else{
                    puts("Produto nao encontrado!");
                }

                break;
            }
            case 4: {
                int codigo, quantidade;

                printf("Digite o codigo do produto: ");

                if(scanf("%d", &codigo) != 1){
                    puts("Codigo invalido!");

                    while((c = getchar()) != '\n' && c != EOF);

                    break;
                }

                while((c = getchar()) != '\n' && c != EOF);

                Produto* p = buscar_hash(h, codigo);

                if(p == NULL){
                    puts("Produto nao encontrado!");
                    break;
                }

                printf("Produto: %s\n", p->nome);
                printf("Quantidade atual: %d\n", p->quantidade);

                printf("Digite a nova quantidade: ");

                if(scanf("%d", &quantidade) != 1){
                    puts("Quantidade invalida!");

                    while((c = getchar()) != '\n' && c != EOF);

                    break;
                }

                while((c = getchar()) != '\n' && c != EOF);

                if(atualizar_quantidade(h, codigo, quantidade))
                    puts("Quantidade atualizada com sucesso!");
                else
                    puts("Erro ao atualizar quantidade!");

                break;
            }
            case 5: {
                int codigo;
                float preco;

                printf("Digite o codigo do produto: ");

                if(scanf("%d", &codigo) != 1){
                    puts("Codigo invalido!");

                    while((c = getchar()) != '\n' && c != EOF);

                    break;
                }

                while((c = getchar()) != '\n' && c != EOF);

                Produto* p = buscar_hash(h, codigo);

                if(p == NULL){
                    puts("Produto nao encontrado!");
                    break;
                }

                printf("Produto: %s\n", p->nome);
                printf("Preco atual: R$ %.2f\n", p->preco);

                printf("Digite o novo preco: ");

                if(scanf("%f", &preco) != 1){
                    puts("Preco invalido!");

                    while((c = getchar()) != '\n' && c != EOF);

                    break;
                }

                while((c = getchar()) != '\n' && c != EOF);

                if(alterar_preco(h, codigo, preco))
                    puts("Preco alterado com sucesso!");
                else
                    puts("Erro ao alterar preco!");

                break;
            }
            case 6: {
                int codigo;

                printf("Digite o codigo do produto que deseja remover: ");

                if(scanf("%d", &codigo) != 1){
                    puts("Codigo invalido!");

                    while((c = getchar()) != '\n' && c != EOF);

                    break;
                }

                while((c = getchar()) != '\n' && c != EOF);

                Produto* p = buscar_hash(h, codigo);

                if(p == NULL){
                    puts("Produto nao encontrado!");
                    break;
                }

                printf("Produto encontrado: %s\n", p->nome);

                if(remover_produto(h, a, codigo))
                    puts("Produto removido com sucesso!");
                else
                    puts("Erro ao remover produto!");

                break;
            }
            case 7: {
                printf("\n===== PRODUTOS EM ORDEM ALFABETICA =====\n");

                listar_abb(a);

                break;
            }
            case 8: {
                int total_produtos;
                int total_unidades;

                calcular_estatisticas(h, &total_produtos, &total_unidades);

                printf("\n===== ESTATISTICAS DO ESTOQUE =====\n");
                printf("Produtos cadastrados: %d\n", total_produtos);
                printf("Total de unidades: %d\n", total_unidades);

                break;
            }
            default:
                puts("Opcao invalida!");
        }

    } while(opcao != 0);

    destruir_hash(h);
    destruir_abb(a);

    return 0;
}