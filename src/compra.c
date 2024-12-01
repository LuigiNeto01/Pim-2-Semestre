#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include "utils.h"
#include "components/ascii.h"
#include "venda.h"


// Função para salvar a venda no arquivo CSV
void salvar_compra_csv(int id_funcionario, double valor_venda, const char *lista_produtos, const char *tipo, const char *cpf) {
    // Nome do arquivo CSV
    const char *nome_arquivo = "data/registro_vendas.csv";
    
    // Gerar timestamp atual
    char timestamp[20];
    time_t t;
    struct tm *tmp;

    t = time(NULL);
    tmp = localtime(&t);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tmp);

    // Abre o arquivo CSV em modo "append" para adicionar linhas ao final
    FILE *arquivo = fopen(nome_arquivo, "a");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nome_arquivo);
        return;
    }

    // Escreve os dados no formato CSV
    fprintf(arquivo, "%s;%d;%.2f;%s;%s;%s;%d\n", timestamp, id_funcionario, valor_venda, lista_produtos, tipo, cpf, 2);

    // Fecha o arquivo
    fclose(arquivo);
    
    printf("Dados salvos com sucesso!\n");
}


// Função principal de venda refatorada
int compra(int id_funcionario) {
    // Declaração das variáveis
    Produto *produtos = NULL;
    int max_produtos = 1000; // Capacidade inicial para produtos
    int num_produtos = 0;

    // Aloca memória para os produtos
    produtos = (Produto *)malloc(sizeof(Produto) * max_produtos);
    if (produtos == NULL) {
        fprintf(stderr, "Erro ao alocar memória para produtos.\n");
        return 1;
    }

    num_produtos = lerProdutos(produtos, max_produtos);
    if (num_produtos == 0) {
        printf("Nenhum produto encontrado.\n");
        free(produtos); // Libera a memória alocada
        return 1;
    }

    float total_compra = 0.0f;
    int continuar = 1;
    char cpf_formatted[15] = "0";
    char *lista_produtos_ids = NULL;
    int max_lista_produtos_ids = 1000; // Capacidade inicial para lista_produtos_ids

    // Aloca memória para lista_produtos_ids
    lista_produtos_ids = (char *)malloc(sizeof(char) * max_lista_produtos_ids);
    if (lista_produtos_ids == NULL) {
        fprintf(stderr, "Erro ao alocar memória para lista_produtos_ids.\n");
        free(produtos);
        return 1;
    }
    lista_produtos_ids[0] = '\0'; // Inicializa como string vazia

    char tipo_venda[20] = "Presencial"; // Valor padrão

    // Variáveis para a compra atual
    ProdutoCompra *compra_produtos = NULL;
    int max_compra_produtos = 100; // Capacidade inicial para compra_produtos
    int num_compra_produtos = 0;

    // Aloca memória para compra_produtos
    compra_produtos = (ProdutoCompra *)malloc(sizeof(ProdutoCompra) * max_compra_produtos);
    if (compra_produtos == NULL) {
        fprintf(stderr, "Erro ao alocar memória para compra_produtos.\n");
        free(produtos);
        free(lista_produtos_ids);
        return 1;
    }

    // Seleciona o tipo de venda
    selecionarTipoVenda(tipo_venda, 9);

    // Limpa a tela e exibe a arte ASCII
    system("cls");
    Ascii(9);

    // Exibe a caixa para inserir o CPF do cliente
    printf("   ╔═══════════════════════════════════════════╗\n");
    printf("   ║          Insira o CPF do cliente          ║\n");
    printf("   ║                    ou                     ║\n");
    printf("   ║     Pressione Enter para Não Utilizar     ║\n");
    printf("   ╚═══════════════════════════════════════════╝\n");

    // Exibe o placeholder para o CPF
    printf("   ╔═════════════════════════════════════╗\n");
    printf("   ║  CPF: ___.___.___-__                ║\n");
    printf("   ╚═════════════════════════════════════╝\n");

    // Obtém o CPF do usuário
    capturarCPF(cpf_formatted);

    // Loop principal da venda
    while (continuar) {
        system("cls");
        Ascii(9);

        // Exibe o total atual da compra
        gotoxy(0, 8);
        printf("   ╔═════════════════════════════════════╗\n");
        printf("   ║  Total atual da compra: R$          ║\n");
        printf("   ╚═════════════════════════════════════╝\n");
        gotoxy(32, 9);
        printf("%.2f", total_compra);

        // Caixa para inserir o ID do produto
        gotoxy(0, 11);
        printf("   ╔═════════════════════════════════════╗\n");
        printf("   ║ Digite o ID do produto:             ║\n");
        printf("   ╚═════════════════════════════════════╝\n");
        gotoxy(30, 12);
        char id_produto_str[20];
        capturarEntradaNumerica(id_produto_str, sizeof(id_produto_str));
        int id_produto = atoi(id_produto_str);

        // Busca o produto pelo ID
        Produto *produto = buscarProduto(produtos, num_produtos, id_produto);

        if (produto) {
            // Caixa para inserir a quantidade
            gotoxy(0, 14);
            printf("   ╔═════════════════════════════════════╗\n");
            printf("   ║                                     ║\n");
            printf("   ║                                     ║\n");
            printf("   ╚═════════════════════════════════════╝\n");

            // Pergunta a quantidade
            gotoxy(4, 15);
            printf("Digite a quantidade em %s:", produto->unidade_medida);
            gotoxy(6, 16);
            printf("qnt: ");
            char quantidade_str[20];
            capturarEntradaNumerica(quantidade_str, sizeof(quantidade_str));

            // Valida a quantidade
            if (!validarQuantidade(quantidade_str)) {
                printf("\nErro: Quantidade inválida. Deve ser um número válido com até duas casas decimais.\n");
                _getch();
                continue;
            }

            // Converte a quantidade para float
            for (int i = 0; quantidade_str[i]; i++) {
                if (quantidade_str[i] == ',') quantidade_str[i] = '.'; // Substitui a vírgula por ponto
            }
            float quantidade = atof(quantidade_str);

            // Adiciona ou atualiza o produto em compra_produtos[]
            int encontrado = 0;
            for (int i = 0; i < num_compra_produtos; i++) {
                if (compra_produtos[i].id_produto == id_produto) {
                    compra_produtos[i].quantidade += quantidade;
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                // Verifica se é necessário expandir o array compra_produtos
                if (num_compra_produtos == max_compra_produtos) {
                    max_compra_produtos *= 2;
                    ProdutoCompra *temp = realloc(compra_produtos, sizeof(ProdutoCompra) * max_compra_produtos);
                    if (temp == NULL) {
                        fprintf(stderr, "Erro ao realocar memória para compra_produtos.\n");
                        free(produtos);
                        free(lista_produtos_ids);
                        free(compra_produtos);
                        return 1;
                    }
                    compra_produtos = temp;
                }

                // Adiciona novo produto na compra
                compra_produtos[num_compra_produtos].id_produto = id_produto;
                compra_produtos[num_compra_produtos].quantidade = quantidade;
                num_compra_produtos++;
            }

            // Calcula o subtotal
            float subtotal = produto->preco_compra * quantidade;

            // Atualiza o total da compra
            total_compra += subtotal;

            // Exibe o subtotal e o total atualizado
            gotoxy(0, 18);
            printf("Subtotal deste item: R$ %.2f\n", subtotal);
            gotoxy(32, 9);
            printf("%.2f\n", total_compra);

            // Menu de opções
            char *opcoes[] = {
                "Adicionar mais um produto",
                "Comprar",
                "Cancelar compra",
                "Sair"
            };
            int num_opcoes = 4;
            int linha_inicial_menu = 20;
            int opcao = menuSelecao(opcoes, num_opcoes, linha_inicial_menu);

            switch (opcao) {
                case 1:
                    // Adicionar mais um produto (continua o loop)
                    break;
                case 2:
                    // Ir para o pagamento
                    goto pagamento;
                case 3:
                    // Cancelar venda
                    total_compra = 0.0f;
                    lista_produtos_ids[0] = '\0'; // Limpa a lista de produtos
                    num_compra_produtos = 0;
                    printf("Compra cancelada.\n");
                    _getch();
                    continuar = 0;
                    break;
                case 4:
                    // Sair
                    continuar = 0;
                    break;
                default:
                    // Opção inválida
                    break;
            }
        } else {
            // Produto não encontrado
            system("cls");
            Ascii(9);
            gotoxy(0, 8);
            printf("   ╔═════════════════════════════════════════╗\n");
            printf("   ║        Produto Não Encontrado!          ║\n");
            printf("   ║ Pressione qualquer tecla para continuar ║\n");
            printf("   ╚═════════════════════════════════════════╝\n");
            _getch(); // vai esperar qualquer tecla ser pressionada
        }
    }

pagamento:

    // Verifica se há produtos na compra
    if (num_compra_produtos > 0) {
        // Atualizar estoque
        atualizarEstoque(produtos, num_produtos, compra_produtos, num_compra_produtos, 1);

        // Gerar lista_produtos_ids
        // Calcula o tamanho necessário para a string
        int tamanho_necessario = num_compra_produtos * 20;
        if (strlen(lista_produtos_ids) + tamanho_necessario >= max_lista_produtos_ids) {
            // Realoca para evitar overflow
            while (strlen(lista_produtos_ids) + tamanho_necessario >= max_lista_produtos_ids) {
                max_lista_produtos_ids *= 2;
            }
            char *temp_lista = realloc(lista_produtos_ids, sizeof(char) * max_lista_produtos_ids);
            if (temp_lista == NULL) {
                fprintf(stderr, "Erro ao realocar memória para lista_produtos_ids.\n");
                free(produtos);
                free(lista_produtos_ids);
                free(compra_produtos);
                return 1;
            }
            lista_produtos_ids = temp_lista;
        }

        lista_produtos_ids[0] = '\0';
        for (int i = 0; i < num_compra_produtos; i++) {
            if (i > 0) {
                strcat(lista_produtos_ids, "|");
            }
            char produto_info[50];
            snprintf(produto_info, sizeof(produto_info), "%d:%.2f", compra_produtos[i].id_produto, compra_produtos[i].quantidade);
            strcat(lista_produtos_ids, produto_info);
        }

        // Salva os dados no CSV
        salvar_compra_csv(id_funcionario, total_compra, lista_produtos_ids, tipo_venda, cpf_formatted);
        continuar = 0;
    } else {
        // Nenhum produto na compra
        printf("Nenhum produto na compra para efetuar o pagamento.\n");
        _getch();
        continuar = 0;
    }

    // Finaliza a venda
    system("cls");
    Ascii(9);
    if (total_compra > 0) {
        printf("   ╔════════════════════════════════════════════════════╗\n");
        printf("   ║ Compra finalizada. Total a pagar: R$               ║\n");
        printf("   ║                                                    ║\n");
        printf("   ║           Obrigado por comprar conosco!            ║\n");
        printf("   ║      Pressione qualquer tecla para continuar       ║\n");
        printf("   ╚════════════════════════════════════════════════════╝\n");
        gotoxy(42, 9);
        printf("%.2f", total_compra);
        _getch();
    } else {
        printf("   ╔══════════════════════════════════════════════╗\n");
        printf("   ║ Compra cancelada. Nenhum valor foi cobrado.  ║\n");
        printf("   ╚══════════════════════════════════════════════╝\n");
    }

    // Libera a memória alocada
    free(produtos);
    free(lista_produtos_ids);
    free(compra_produtos);

    return 0;
}