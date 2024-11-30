#ifndef VENDA_H
#define VENDA_H

// Estrutura para armazenar informações do produto
typedef struct {
    int id_produto;                // Identificador único do produto
    char nome_item[100];           // Nome do produto
    char tipo[50];                 // Tipo do produto
    float preco_venda;             // Preço de venda do produto
    float preco_compra;            // Preço de compra do produto
    char validade[20];             // Data de validade do produto
    char unidade_medida[20];       // Unidade de medida do produto (ex: kg, unidade)
    char valor_nutricional[100];   // Informações nutricionais do produto
    int quantidade_estoque;        // Quantidade em estoque do produto
    float volume;                  // Volume do produto
} Produto;

// Protótipos das funções de validação e manipulação
int validarInteiro(const char *str);
int validarQuantidade(const char *str);
void capturarEntradaNumerica(char *destino, int tamanho_maximo);
void capturarCPF(char *cpf_formatted);
void selecionarTipoVenda(char *tipo, int ascii);
int lerProdutos(Produto produtos[], int max_produtos);
Produto* buscarProduto(Produto produtos[], int num_produtos, int id_produto);
int menuSelecao(char *options[], int num_options, int initial_line);
void salvar_venda_csv(int id_funcionario, double valor_venda, const char *lista_produtos, const char *tipo, const char *cpf);
void adicionar_produto_venda(char *lista_produtos_ids, int id_produto, float quantidade);
int venda(int id_funcionario);

#endif // VENDA_H
