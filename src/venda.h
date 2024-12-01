#ifndef VENDA_H
#define VENDA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Estruturas
typedef struct {
    int id_produto;
    char nome_item[50];
    char tipo[20];
    float preco_venda;
    float preco_compra;
    char validade[20];
    char unidade_medida[10];
    char valor_nutricional[100];
    int quantidade_estoque;
    float volume;
} Produto;

typedef struct {
    char timestamp[20];
    int id_funcionario;
    float preco_venda;
    char produtos_qnt[500];
    char tipo[20];
    char cpf[20];
    int modalidade;
} Venda;

typedef struct {
    int id_produto;
    float quantidade;
} ProdutoCompra;

// Funções de Validação
int validarInteiro(const char *str);
int validarQuantidade(const char *str);

// Funções de Entrada
void capturarEntradaNumerica(char *destino, int tamanho_maximo);
void capturarCPF(char *cpf_formatted);

// Operações de Venda
void selecionarTipoVenda(char *tipo, int ascii);
int lerProdutos(Produto produtos[], int max_produtos);
Produto* buscarProduto(Produto produtos[], int num_produtos, int id_produto);
int verificarDisponibilidade(Produto produtos[], int num_produtos, int id_produto, float quantidade_requerida, ProdutoCompra compra_produtos[], int num_compra_produtos);
void atualizarEstoque(Produto produtos[], int num_produtos, ProdutoCompra compra_produtos[], int num_compra_produtos, int isCompra);
void salvar_venda_csv(int id_funcionario, double valor_venda, const char *lista_produtos, const char *tipo, const char *cpf);
void adicionar_produto_venda(char *lista_produtos_ids, int id_produto, float quantidade);

// Funções de Interface
int menuSelecao(char *options[], int num_options, int initial_line);

// Função Principal
int venda(int id_funcionario);

#endif // VENDA_H
