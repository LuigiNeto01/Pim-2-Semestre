#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include "utils.h"
#include "components/ascii.h"

// Protótipos das funções de validação
int validarInteiro(const char *str);
int validarQuantidade(const char *str);

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

// Função para capturar CPF com formatação ___.___.___-__
void capturarCPF(char *cpf_formatted) {
    char cpf_digits[12] = ""; // 11 dígitos + NULL
    int digit_count = 0;
    char ch;
    ocultar_cursor();

    // Inicializa a string formatada
    strcpy(cpf_formatted, "___.___.___-__");

    while (1) {
        ch = _getch();

        if (isdigit(ch)) {
            if (digit_count < 11) {
                cpf_digits[digit_count++] = ch;
                // Atualiza a string formatada
                if (digit_count == 1) {
                    cpf_formatted[0] = ch;
                } else if (digit_count == 2) {
                    cpf_formatted[1] = ch;
                } else if (digit_count == 3) {
                    cpf_formatted[2] = ch;
                } else if (digit_count == 4) {
                    cpf_formatted[4] = ch;
                } else if (digit_count == 5) {
                    cpf_formatted[5] = ch;
                } else if (digit_count == 6) {
                    cpf_formatted[6] = ch;
                } else if (digit_count == 7) {
                    cpf_formatted[8] = ch;
                } else if (digit_count == 8) {
                    cpf_formatted[9] = ch;
                } else if (digit_count == 9) {
                    cpf_formatted[10] = ch;
                } else if (digit_count == 10) {
                    cpf_formatted[12] = ch;
                } else if (digit_count == 11) {
                    cpf_formatted[13] = ch;
                }

                // Exibe o CPF formatado
                gotoxy(6, 14); // Ajuste conforme a posição da caixa
                printf("CPF: %s", cpf_formatted);
            }
        } else if (ch == '\b') { // Backspace
            if (digit_count > 0) {
                digit_count--;
                cpf_digits[digit_count] = '\0';
                // Atualiza a string formatada
                if (digit_count == 0) {
                    strcpy(cpf_formatted, "___.___.___-__");
                } else if (digit_count == 1) {
                    cpf_formatted[0] = '_';
                } else if (digit_count == 2) {
                    cpf_formatted[1] = '_';
                } else if (digit_count == 3) {
                    cpf_formatted[2] = '_';
                } else if (digit_count == 4) {
                    cpf_formatted[4] = '_';
                } else if (digit_count == 5) {
                    cpf_formatted[5] = '_';
                } else if (digit_count == 6) {
                    cpf_formatted[6] = '_';
                } else if (digit_count == 7) {
                    cpf_formatted[8] = '_';
                } else if (digit_count == 8) {
                    cpf_formatted[9] = '_';
                } else if (digit_count == 9) {
                    cpf_formatted[10] = '_';
                } else if (digit_count == 10) {
                    cpf_formatted[12] = '_';
                }

                // Exibe o CPF formatado
                gotoxy(6, 14); // Ajuste conforme a posição da caixa
                printf("CPF: %s", cpf_formatted);
            }
        } else if (ch == '\r') { // Enter
            break;
        }
    }

    // Se nenhum dígito foi inserido, define como "0"
    if (digit_count == 0) {
        strcpy(cpf_formatted, "0");
    } else if (digit_count < 11) {
        // Se menos de 11 dígitos foram inseridos, define como "0"
        strcpy(cpf_formatted, "0");
    }
    mostrar_cursor();
}

// Função para selecionar o tipo de venda (Presencial ou Online)
void selecionarTipoVenda(char *tipo) {
    int selecionado = 1; // 1 para Presencial, 2 para Online
    int ch;

    system("cls");
    Ascii(5);
    printf("   ╔═══════════════════════════════════╗\n");
    printf("   ║                                   ║\n");
    printf("   ╚═══════════════════════════════════╝\n");
    ocultar_cursor();

    while (1) {
        // Exibe as opções com os símbolos ▢ e ▣
        gotoxy(7, 9);
        printf("%s Presencial   \t%s Online  ", (selecionado == 1 ? "▣" : "▢"), (selecionado == 2 ? "▣" : "▢"));

        ch = _getch();
        if (ch == 224) {  // Tecla de seta pressionada
            ch = _getch();
            if (ch == 75) { // Seta para a esquerda
                selecionado = 1;
            } else if (ch == 77) { // Seta para a direita
                selecionado = 2;
            }
        } else if (ch == 13) { // Enter pressionado
            break;
        }
    }

    // Define o tipo de venda baseado na escolha
    if (selecionado == 1) {
        strcpy(tipo, "Presencial");
    } else {
        strcpy(tipo, "Online");
    }
    mostrar_cursor();
}

// Função para ler os produtos de um arquivo CSV
int lerProdutos(Produto produtos[], int max_produtos) {
    FILE *file;
    char line[1024]; // Aumentado para suportar linhas maiores
    int product_count = 0;
    char *token;
    char preco_venda_str[20];
    char preco_compra_str[20];
    char volume_str[20];

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

        // Lê o preço de venda e valida o formato
        token = strtok(NULL, ";");
        if (!token) continue;
        if (!validarQuantidade(token)) {
            fprintf(stderr, "Erro: Preço de venda inválido. Deve ser um número válido com até duas casas decimais.\n");
            continue;
        }
        strncpy(preco_venda_str, token, sizeof(preco_venda_str) - 1);
        preco_venda_str[sizeof(preco_venda_str) - 1] = '\0';
        for (int i = 0; preco_venda_str[i]; i++) {
            if (preco_venda_str[i] == ',') preco_venda_str[i] = '.'; // Substitui a vírgula por ponto
        }
        produtos[product_count].preco_venda = atof(preco_venda_str); // Converte o preço para float

        // Lê o preço de compra e valida o formato
        token = strtok(NULL, ";");
        if (!token) continue;
        if (!validarQuantidade(token)) {
            fprintf(stderr, "Erro: Preço de compra inválido. Deve ser um número válido com até duas casas decimais.\n");
            continue;
        }
        strncpy(preco_compra_str, token, sizeof(preco_compra_str) - 1);
        preco_compra_str[sizeof(preco_compra_str) - 1] = '\0';
        for (int i = 0; preco_compra_str[i]; i++) {
            if (preco_compra_str[i] == ',') preco_compra_str[i] = '.'; // Substitui a vírgula por ponto
        }
        produtos[product_count].preco_compra = atof(preco_compra_str); // Converte o preço para float

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

        // Lê a quantidade em estoque
        token = strtok(NULL, ";");
        if (!token) continue;
        if (!validarInteiro(token)) {
            fprintf(stderr, "Erro: Quantidade em estoque inválida. Deve ser um número inteiro.\n");
            continue;
        }
        produtos[product_count].quantidade_estoque = atoi(token);

        // Lê o volume e valida o formato
        token = strtok(NULL, ";");
        if (!token) continue;
        if (!validarQuantidade(token)) {
            fprintf(stderr, "Erro: Volume inválido. Deve ser um número válido com até duas casas decimais.\n");
            continue;
        }
        strncpy(volume_str, token, sizeof(volume_str) - 1);
        volume_str[sizeof(volume_str) - 1] = '\0';
        for (int i = 0; volume_str[i]; i++) {
            if (volume_str[i] == ',') volume_str[i] = '.'; // Substitui a vírgula por ponto
        }
        produtos[product_count].volume = atof(volume_str); // Converte o volume para float

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

// Função para salvar a venda no arquivo CSV
void salvar_venda_csv(int id_funcionario, double valor_venda, const char *lista_produtos, const char *tipo, const char *cpf) {
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
    fprintf(arquivo, "%s;%d;%.2f;%s;%s;%s;%d\n", timestamp, id_funcionario, valor_venda, lista_produtos, tipo, cpf, 1); // O 1 foi definido de forma fixa pq a ideia eh que ele seja referente ao venda

    // Fecha o arquivo
    fclose(arquivo);
    
    printf("Dados salvos com sucesso!\n");
}

// Função para adicionar produto à lista de vendas com separador '|'
void adicionar_produto_venda(char *lista_produtos_ids, int id_produto, float quantidade) {
    // Verifica se a lista já contém produtos para decidir se adiciona o separador
    if (strlen(lista_produtos_ids) > 0) {
        strcat(lista_produtos_ids, "|"); // Adiciona separador entre produtos
    }
    
    char produto_info[50];
    snprintf(produto_info, sizeof(produto_info), "%d:%.2f", id_produto, quantidade);
    strcat(lista_produtos_ids, produto_info);
}

// Função principal de venda refatorada
int venda(int id_funcionario) {
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
    selecionarTipoVenda(tipo_venda);

    // Limpa a tela e exibe a arte ASCII
    system("cls");
    Ascii(5);

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
        Ascii(5);

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

            // Calcula o subtotal
            float subtotal = produto->preco_venda * quantidade;

            // Adiciona o produto à lista de vendas
            adicionar_produto_venda(lista_produtos_ids, produto->id_produto, quantidade);

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
                "Pagar",
                "Cancelar venda",
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
                    salvar_venda_csv(id_funcionario, total_compra, lista_produtos_ids, tipo_venda, cpf_formatted);
                    continuar = 0;
                    break;
                }
                case 3: { // Cancelar venda
                    total_compra = 0.0f;
                    lista_produtos_ids[0] = '\0'; // Limpa a lista de produtos
                    printf("Venda cancelada.\n");
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
            Ascii(5);
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
        _getch();
    } else {
        printf("   ╔══════════════════════════════════════════════╗\n");
        printf("   ║ Venda cancelada. Nenhum valor foi cobrado.   ║\n");
        printf("   ╚══════════════════════════════════════════════╝\n");
    }

    return 0;
}
