#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <conio.h>
#include <ctype.h>
#include "utils.h"
#include "components/ascii.h"

// Protótipos das funções de validação
int validarInteiro(const char *str);
int validarQuantidade(const char *str);

// Estrutura para armazenar informações do produto
typedef struct {
    int id_produto; // Identificador único do produto
    char nome_item[100]; // Nome do produto
    char tipo[50]; // Tipo do produto
    float preco; // Preço do produto
    char validade[20]; // Data de validade do produto
    char unidade_medida[20]; // Unidade de medida do produto (ex: kg, unidade)
    char valor_nutricional[100]; // Informações nutricionais do produto
} Produto;

// Função para validar se uma string contém apenas números inteiros
int validarInteiro(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return 0;
        }
    }
    return 1;
}

// Função para validar a quantidade no formato correto (apenas uma vírgula e até duas casas decimais)
int validarQuantidade(const char *str) {
    int i = 0;
    int virgula_encontrada = 0;
    int digitos_apos_virgula = 0;

    if (str == NULL || *str == '\0') {
        return 0;
    }

    while (str[i] != '\0') {
        if (isdigit((unsigned char)str[i])) {
            if (virgula_encontrada) {
                digitos_apos_virgula++;
                if (digitos_apos_virgula > 2) {
                    return 0; // Mais de dois dígitos após a vírgula
                }
            }
        } else if (str[i] == ',') {
            if (virgula_encontrada) {
                return 0; // Mais de uma vírgula encontrada
            }
            virgula_encontrada = 1;
        } else {
            return 0; // Caractere inválido encontrado
        }
        i++;
    }

    return 1;
}

// Função para capturar entrada do usuário permitindo apenas números e vírgula
void capturarEntradaNumerica(char *destino, int tamanho_maximo) {
    int i = 0;
    char ch;

    while (i < tamanho_maximo - 1) {
        ch = _getch(); // Captura o caractere sem exibir imediatamente na tela

        // Permite apenas números e uma vírgula
        if (isdigit(ch) || (ch == ',' && strchr(destino, ',') == NULL)) {
            destino[i++] = ch;
            printf("%c", ch); // Exibe o caractere na tela
        } else if (ch == '\b' && i > 0) { // Backspace para apagar
            i--;
            printf("\b \b");
        } else if (ch == '\r') { // Enter para finalizar a entrada
            break;
        }
    }
    destino[i] = '\0'; // Finaliza a string
}

// Função para ler os produtos de um arquivo CSV
int lerProdutos(Produto produtos[], int max_produtos) {
    FILE *file;
    char line[512];
    int product_count = 0;
    char *token;
    char preco_str[20];

    // Abre o arquivo de produtos
    file = fopen("data/produtos.csv", "r");
    if (!file) {
        // Caso não seja possível abrir o arquivo, exibe um erro e retorna 0
        fprintf(stderr, "Erro ao abrir o arquivo data/produtos.csv\n");
        return 0;
    }

    // Lê cada linha do arquivo até o máximo de produtos permitidos
    while (fgets(line, sizeof(line), file) && product_count < max_produtos) {
        // Remove o caractere de nova linha
        line[strcspn(line, "\n")] = '\0';

        // Tokeniza a linha usando ';' como delimitador
        token = strtok(line, ";");
        if (!token) continue;

        // Valida se o ID do produto é um número inteiro
        if (!validarInteiro(token)) {
            fprintf(stderr, "Erro: ID do produto inválido. Deve ser um número inteiro.\n");
            continue;
        }
        produtos[product_count].id_produto = atoi(token); // Converte o ID do produto para inteiro

        // Lê o nome do item
        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(produtos[product_count].nome_item, token, sizeof(produtos[product_count].nome_item) - 1);
        produtos[product_count].nome_item[sizeof(produtos[product_count].nome_item) - 1] = '\0';

        // Lê o tipo do produto
        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(produtos[product_count].tipo, token, sizeof(produtos[product_count].tipo) - 1);
        produtos[product_count].tipo[sizeof(produtos[product_count].tipo) - 1] = '\0';

        // Lê o preço e valida o formato
        token = strtok(NULL, ";");
        if (!token) continue;
        if (!validarQuantidade(token)) {
            fprintf(stderr, "Erro: Preço do produto inválido. Deve ser um número válido com até duas casas decimais.\n");
            continue;
        }
        strncpy(preco_str, token, sizeof(preco_str) - 1);
        preco_str[sizeof(preco_str) - 1] = '\0';
        for (int i = 0; preco_str[i]; i++) {
            if (preco_str[i] == ',') preco_str[i] = '.'; // Substitui a vírgula por ponto
        }
        produtos[product_count].preco = atof(preco_str); // Converte o preço para float

        // Lê a validade do produto
        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(produtos[product_count].validade, token, sizeof(produtos[product_count].validade) - 1);
        produtos[product_count].validade[sizeof(produtos[product_count].validade) - 1] = '\0';

        // Lê a unidade de medida
        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(produtos[product_count].unidade_medida, token, sizeof(produtos[product_count].unidade_medida) - 1);
        produtos[product_count].unidade_medida[sizeof(produtos[product_count].unidade_medida) - 1] = '\0';

        // Lê o valor nutricional
        token = strtok(NULL, ";");
        if (!token) continue;
        strncpy(produtos[product_count].valor_nutricional, token, sizeof(produtos[product_count].valor_nutricional) - 1);
        produtos[product_count].valor_nutricional[sizeof(produtos[product_count].valor_nutricional) - 1] = '\0';

        // Incrementa o contador de produtos
        product_count++;
    }

    // Fecha o arquivo após leitura
    fclose(file);
    return product_count;
}

// Função para buscar um produto pelo ID
Produto* buscarProduto(Produto produtos[], int num_produtos, int id_produto) {
    for (int i = 0; i < num_produtos; i++) {
        // Verifica se o ID do produto corresponde ao ID buscado
        if (produtos[i].id_produto == id_produto) {
            return &produtos[i]; // Retorna um ponteiro para o produto encontrado
        }
    }
    return NULL; // Retorna NULL se o produto não for encontrado
}

// Função para exibir um menu e obter a escolha do usuário
int menuSelecao(char *options[], int num_options, int initial_line) {
    int current_choice = 1;
    int selected_option = 0;
    int ch;
    ocultar_cursor(); // Oculta o cursor enquanto o menu está sendo exibido

    while (1) {
        // Exibe as opções do menu
        for (int i = 0; i < num_options; i++) {
            gotoxy(4, initial_line + i);
            if (current_choice == i + 1) {
                printf("-> %s   ", options[i]); // Marca a opção atual com uma seta
            } else {
                printf("   %s   ", options[i]); // Exibe outras opções sem marcação
            }
        }

        // Captura a tecla pressionada
        ch = _getch();
        if (ch == 224) {  // Tecla de seta pressionada
            ch = _getch();
            if (ch == 72) { // Seta para cima
                current_choice--;
                if (current_choice < 1) current_choice = num_options; // Rola para a última opção
            } else if (ch == 80) { // Seta para baixo
                current_choice++;
                if (current_choice > num_options) current_choice = 1; // Rola para a primeira opção
            }
        } else if (ch == 13) { // Tecla Enter pressionada
            selected_option = current_choice; // Armazena a opção selecionada
            break;
        }
    }
    mostrar_cursor(); // Mostra o cursor novamente
    return selected_option; // Retorna a opção selecionada
}

// Função para realizar uma venda
int venda() {
    // Declaração das variáveis
    Produto produtos[100]; // Array para armazenar até 100 produtos
    int num_produtos;
    float total_compra = 0.0f; // Total da compra
    int continuar = 1; // Variável de controle do loop
    char id_produto_str[20];
    Produto *produto;
    char quantidade_str[20];
    float quantidade;
    float subtotal;
    char *opcoes[] = {
        "Adicionar mais um produto",
        "Pagar",
        "Cancelar venda",
        "Sair"
    };
    int num_opcoes = 4;
    int linha_inicial_menu = 20;
    int opcao;

    // Carrega os produtos a partir do arquivo
    num_produtos = lerProdutos(produtos, 100);

    if (num_produtos == 0) {
        // Caso nenhum produto seja encontrado, exibe uma mensagem e retorna
        printf("Nenhum produto encontrado.\n");
        return 1;
    }

    while (continuar) {
        // Limpa a tela e exibe a arte ASCII
        system("cls");
        Ascii(5);

        // Exibe o total atual da compra dentro de uma caixa
        gotoxy(0, 8);
        printf("   ╔═════════════════════════════════════╗\n");
        printf("   ║  Total atual da compra: R$          ║\n");
        printf("   ╚═════════════════════════════════════╝\n");
        gotoxy(32, 9);
        printf("%.2f", total_compra);

        // Cria uma caixa vazia para perguntar o ID do produto
        gotoxy(0, 11);
        printf("   ╔═════════════════════════════════════╗\n");
        printf("   ║ Digite o ID do produto:             ║\n");
        printf("   ╚═════════════════════════════════════╝\n");

        // Obtém o ID do produto
        gotoxy(30, 12);
        capturarEntradaNumerica(id_produto_str, sizeof(id_produto_str));

        // Valida o ID do produto (opcional, pois agora só aceita números)
        int id_produto = atoi(id_produto_str);

        // Busca o produto pelo ID
        produto = buscarProduto(produtos, num_produtos, id_produto);

        if (produto) {
            // Cria uma caixa vazia para perguntar a quantidade
            gotoxy(0, 14);
            printf("   ╔═════════════════════════════════════╗\n");
            printf("   ║                                     ║\n");
            printf("   ║                                     ║\n");
            printf("   ╚═════════════════════════════════════╝\n");

            // Insere a pergunta dentro da caixa
            gotoxy(4, 15);
            printf("Digite a quantidade em %s (s)", produto->unidade_medida);

            // Obtém a quantidade
            gotoxy(6, 16);
            printf("qnt: ");
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
            quantidade = atof(quantidade_str);

            // Calcula o subtotal
            subtotal = produto->preco * quantidade;

            // Exibe o subtotal e o total parcial da compra
            gotoxy(0, 18);
            printf("Subtotal deste item: R$ %.2f\n", subtotal);
            gotoxy(32, 9);
            printf("%.2f\n", total_compra + subtotal);

            // Exibe o menu e obtém a escolha do usuário
            gotoxy(0, linha_inicial_menu - 1);
            printf("Escolha uma opção:\n");
            opcao = menuSelecao(opcoes, num_opcoes, linha_inicial_menu);

            if (opcao == 1) {
                total_compra += subtotal;
            } else if (opcao == 2) { // Pagar
                total_compra += subtotal;
                continuar = 0;
            } else if (opcao == 3) { // Cancelar venda
                total_compra = 0.0f;
                continuar = 0;
            } else if (opcao == 4) { // Sair
                continuar = 0;
            }
        } else {
            // Exibe mensagem de erro para produto não encontrado
            system("cls");
            Ascii(5);
            gotoxy(0, 8);
            printf("\033[1;31m╔═════════════════════════════════════════╗\033[0m\n");
            printf("\033[1;31m║        Produto Não Encontrado!          ║\033[0m\n");
            printf("\033[1;31m║ Pressione qualquer tecla para continuar ║\033[0m\n");
            printf("\033[1;31m╚═════════════════════════════════════════╝\033[0m\n");
            _getch(); // Aguarda uma tecla ser pressionada
        }
    }

    // Finaliza a compra
    system("cls");
    Ascii(5);
    if (total_compra > 0) {
        printf("   ╔════════════════════════════════════════════════════╗\n");
        printf("   ║ Compra finalizada. Total a pagar: R$               ║\n");
        printf("   ║                                                    ║\n");
        printf("   ║           Obrigado por comprar conosco!            ║\n");
        printf("   ║      Pressione qualquer tecla para continuar       ║\n");
        printf("   ╚════════════════════════════════════════════════════╝\n");
        gotoxy(42, 9);
        printf("%.2f", total_compra);
        _getch(); // Aguarda uma tecla ser pressionada
    } else {
        printf("   ╔══════════════════════════════════════════════╗\n");
        printf("   ║ Venda cancelada. Nenhum valor foi cobrado.   ║\n");
        printf("   ╚══════════════════════════════════════════════╝\n");
    }

    return 0;
}
