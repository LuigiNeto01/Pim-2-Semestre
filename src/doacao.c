#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include "utils.h"
#include "venda.h"
#include "components/ascii.h"

// Função para salvar a venda no arquivo CSV
void salvar_doacao_csv(int id_funcionario, double valor_venda, const char *lista_produtos, const char *tipo, const char *cpf) {
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
    fprintf(arquivo, "%s;%d;%.2f;%s;%s;%s;%d\n", timestamp, id_funcionario, 0.00, lista_produtos, tipo, cpf, 0); // O 1 foi definido de forma fixa pq a ideia eh que ele seja referente ao venda

    // Fecha o arquivo
    fclose(arquivo);
    
    printf("Dados salvos com sucesso!\n");
}

// Função principal de venda refatorada
int doacao(int id_funcionario) {
    // Declaração das variáveis
    Produto produtos[1000]; // Aumentei o tamanho para 1000 produtos
    int num_produtos = lerProdutos(produtos, 1000);
    if (num_produtos == 0) {
        printf("Nenhum produto encontrado.\n");
        return 1;
    }

    float total_compra = 0.0f;
    int continuar = 1;
    char cpf_formatted[15] = "0";
    char lista_produtos_ids[1000] = "";
    char tipo_venda[20] = "Presencial"; // Valor padrão

    // Seleciona o tipo de venda
    selecionarTipoVenda(tipo_venda, 10);

    // Limpa a tela e exibe a arte ASCII
    system("cls");
    Ascii(10);

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
        Ascii(10);

        // Exibe o total atual da compra
        gotoxy(0, 8);
        printf("   ╔═════════════════════════════════════╗\n");
        printf("   ║  Total atual da doação: R$          ║\n");
        printf("   ╚═════════════════════════════════════╝\n");
        gotoxy(32, 9);
        printf("0.00");

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

            // Adiciona o produto à lista de vendas
            adicionar_produto_venda(lista_produtos_ids, produto->id_produto, quantidade);

            // Exibe o subtotal e o total atualizado
            gotoxy(0, 18);
            printf("Subtotal deste item: R$ 0.00\n");
            gotoxy(32, 9);
            printf("%.2f\n", total_compra);

            // Menu de opções
            char *opcoes[] = {
                "Adicionar mais um produto",
                "Doar",
                "Cancelar doação",
                "Sair"
            };
            int num_opcoes = 4;
            int linha_inicial_menu = 20;
            int opcao = menuSelecao(opcoes, num_opcoes, linha_inicial_menu);

            switch (opcao) {
                case 1:
                    // Adicionar mais um produto (continua o loop)
                    break;
                case 2: { // Pagar
                    // Salva os dados no CSV
                    salvar_doacao_csv(id_funcionario, total_compra, lista_produtos_ids, tipo_venda, cpf_formatted);
                    continuar = 0;
                    break;
                }
                case 3: { // Cancelar venda
                    total_compra = 0.0f;
                    lista_produtos_ids[0] = '\0'; // Limpa a lista de produtos
                    printf("Doação cancelada.\n");
                    _getch();
                    continuar = 0;
                    break;
                }
                case 4: { // Sair
                    continuar = 0;
                    break;
                }
                default:
                    // Opção inválida
                    break;
            }
        } else {
            // Produto não encontrado
            system("cls");
            Ascii(10);
            gotoxy(0, 8);
            printf("   ╔═════════════════════════════════════════╗\n");
            printf("   ║        Produto Não Encontrado!          ║\n");
            printf("   ║ Pressione qualquer tecla para continuar ║\n");
            printf("   ╚═════════════════════════════════════════╝\n");
            _getch(); // Aguarda uma tecla ser pressionada
        }
    }

    // Finaliza a venda
    system("cls");
    Ascii(10);
    if (total_compra > 0) {
        printf("   ╔════════════════════════════════════════════════════╗\n");
        printf("   ║ Doação finalizada. Total a pagar: R$               ║\n");
        printf("   ║                                                    ║\n");
        printf("   ║           Obrigado por doar conosco!               ║\n");
        printf("   ║      Pressione qualquer tecla para continuar       ║\n");
        printf("   ╚════════════════════════════════════════════════════╝\n");
        gotoxy(42, 9);
        printf("%.2f", total_compra);
        _getch();
    } else {
        printf("   ╔══════════════════════════════════════════════╗\n");
        printf("   ║ Doação cancelada. Nenhum valor foi cobrado.  ║\n");
        printf("   ╚══════════════════════════════════════════════╝\n");
    }

    return 0;
}
