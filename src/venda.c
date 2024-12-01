#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include "utils.h"
#include "components/ascii.h"
#include "venda.h"

// Protótipos das funções de validação
int validarInteiro(const char *str);
int validarQuantidade(const char *str);

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
int selecionarTipoVenda(char *tipo, int ascii) {
    int selecionado = 1; // 1 para Presencial, 2 para Online
    int ch;

    system("cls");
    Ascii(ascii);
    printf("   ╔═════════════════════════════════════════════════════════════════════════╗\n");
    printf("   ║ \033[1;33mSerá cobrada uma taxa de frete de R$15,00 para todos os pedidos online  \033[0m║\n");
    printf("   ╚═════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("   ╔═══════════════════════════════════╗\n");
    printf("   ║                                   ║\n");
    printf("   ╚═══════════════════════════════════╝\n");
    ocultar_cursor();

    while (1) {
        // Exibe as opções com os símbolos ▢ e ▣
        gotoxy(7, 13);
        printf("%s Presencial   \t%s Online  ", (selecionado == 1 ? "▣" : "▢"), (selecionado == 2 ? "▣" : "▢"));

        ch = _getch();
        if (ch == 224) {  // Tecla de seta pressionada
            ch = _getch();
            if (ch == 75) { // Seta para a esquerda
                selecionado = 1;
                return 0;
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

    if(selecionado==2){
        return 15;
    } else {
        return 0;
    }
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

    // Lê o cabeçalho e ignora
    fgets(line, sizeof(line), file);

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

// Função para verificar disponibilidade no estoque
int verificarDisponibilidade(Produto produtos[], int num_produtos, int id_produto, float quantidade_requerida, ProdutoCompra compra_produtos[], int num_compra_produtos) {
    Produto *produto = buscarProduto(produtos, num_produtos, id_produto);
    if (!produto) {
        // Produto não encontrado
        return 0;
    }

    // Calcula a quantidade já adicionada para este produto na compra
    float quantidade_adicionada = 0.0f;
    for (int i = 0; i < num_compra_produtos; i++) {
        if (compra_produtos[i].id_produto == id_produto) {
            quantidade_adicionada += compra_produtos[i].quantidade;
        }
    }

    // Verifica se a quantidade total requerida excede o estoque
    if (quantidade_adicionada + quantidade_requerida > produto->quantidade_estoque) {
        // Quantidade indisponível
        return 0;
    } else {
        // Quantidade disponível
        return 1;
    }
}

// Função para atualizar o estoque após a efetivação da compra
// Função para atualizar o estoque após a efetivação da compra ou venda
void atualizarEstoque(Produto produtos[], int num_produtos, ProdutoCompra compra_produtos[], int num_compra_produtos, int isCompra) {
    for (int i = 0; i < num_compra_produtos; i++) {
        Produto *produto = buscarProduto(produtos, num_produtos, compra_produtos[i].id_produto);
        if (produto) {
            if (isCompra) {
                produto->quantidade_estoque += compra_produtos[i].quantidade; // Adicionar ao estoque
            } else {
                produto->quantidade_estoque -= compra_produtos[i].quantidade; // Subtrair do estoque
                if (produto->quantidade_estoque < 0) {
                    produto->quantidade_estoque = 0; // Garantir que não fique negativo
                }
            }
        }
    }

    // Reescrever o arquivo CSV com os novos valores de estoque
    FILE *file = fopen("data/produtos.csv", "w");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo data/produtos.csv para escrita\n");
        return;
    }

    // Escrever o cabeçalho
    fprintf(file, "id_produto;nome_item;tipo;preco_venda;preco_compra;validade;unidade_medida;valor_nutricional;quantidade_estoque;volume\n");

    // Escrever cada produto
    for (int i = 0; i < num_produtos; i++) {
        // Substituir '.' por ',' no preço e volume para manter o formato original
        char preco_venda_str[20], preco_compra_str[20], volume_str[20];
        snprintf(preco_venda_str, sizeof(preco_venda_str), "%.2f", produtos[i].preco_venda);
        snprintf(preco_compra_str, sizeof(preco_compra_str), "%.2f", produtos[i].preco_compra);
        snprintf(volume_str, sizeof(volume_str), "%.2f", produtos[i].volume);
        for (int j = 0; preco_venda_str[j]; j++) {
            if (preco_venda_str[j] == '.') preco_venda_str[j] = ',';
        }
        for (int j = 0; preco_compra_str[j]; j++) {
            if (preco_compra_str[j] == '.') preco_compra_str[j] = ',';
        }
        for (int j = 0; volume_str[j]; j++) {
            if (volume_str[j] == '.') volume_str[j] = ',';
        }

        fprintf(file, "%d;%s;%s;%s;%s;%s;%s;%s;%d;%s\n",
            produtos[i].id_produto,
            produtos[i].nome_item,
            produtos[i].tipo,
            preco_venda_str,
            preco_compra_str,
            produtos[i].validade,
            produtos[i].unidade_medida,
            produtos[i].valor_nutricional,
            produtos[i].quantidade_estoque,
            volume_str);
    }

    fclose(file);
}

// Função principal de venda refatorada
int venda(int id_funcionario) {
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
    int frete = selecionarTipoVenda(tipo_venda, 5);

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
        printf("   ║  Total atual da venda: R$           ║\n");
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

            // Verifica disponibilidade
            if (!verificarDisponibilidade(produtos, num_produtos, id_produto, quantidade, compra_produtos, num_compra_produtos)) {
                system("cls");
                Ascii(5);
                gotoxy(0, 8);
                printf("   ╔══════════════════════════════════════════════════════════╗\n");
                printf("   ║    Quantidade solicitada excede o estoque disponível.    ║\n");
                printf("   ╚══════════════════════════════════════════════════════════╝\n");

                // Menu de opções após indisponibilidade
                char *opcoesIndisponivel[] = {
                    "Continuar com a venda",
                    "Ir para o pagamento",
                    "Cancelar venda",
                    "Sair"
                };
                int num_opcoes_indisponivel = 4;
                int linha_inicial_menu_indisponivel = 12;
                int opcao_indisponivel = menuSelecao(opcoesIndisponivel, num_opcoes_indisponivel, linha_inicial_menu_indisponivel);

                switch (opcao_indisponivel) {
                    case 1:
                        // Continuar com a compra
                        continue;
                    case 2:
                        // Ir para o pagamento
                        goto pagamento;
                    case 3:
                        // Cancelar venda
                        total_compra = 0.0f;
                        lista_produtos_ids[0] = '\0'; // Limpa a lista de produtos
                        num_compra_produtos = 0;
                        printf("Venda cancelada.\n");
                        _getch();
                        continuar = 0;
                        break;
                    case 4:
                        // Sair
                        continuar = 0;
                        break;
                    default:
                        // Opção inválida
                        continue;
                }
                continue;
            }

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
            float subtotal = produto->preco_venda * quantidade;

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
                "Vender",
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
                case 2:
                    // Ir para o pagamento
                    goto pagamento;
                case 3:
                    // Cancelar venda
                    total_compra = 0.0f;
                    lista_produtos_ids[0] = '\0'; // Limpa a lista de produtos
                    num_compra_produtos = 0;
                    printf("Venda cancelada.\n");
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
            Ascii(5);
            gotoxy(0, 8);
            printf("   ╔═════════════════════════════════════════╗\n");
            printf("   ║        Produto Não Encontrado!          ║\n");
            printf("   ║ Pressione qualquer tecla para continuar ║\n");
            printf("   ╚═════════════════════════════════════════╝\n");
            _getch(); // Aguarda uma tecla ser pressionada
        }
    }

pagamento:

    // Verifica se há produtos na compra
    if (num_compra_produtos > 0) {
        // Atualizar estoque
        atualizarEstoque(produtos, num_produtos, compra_produtos, num_compra_produtos, 0);

        // Gerar lista_produtos_ids
        // Calcula o tamanho necessário para a string
        // Estima o tamanho máximo: cada produto pode ocupar até 20 caracteres (id:quantidade|)
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
        salvar_venda_csv(id_funcionario, total_compra+frete, lista_produtos_ids, tipo_venda, cpf_formatted);
        continuar = 0;
    } else {
        // Nenhum produto na compra
        printf("Nenhum produto na venda para efetuar o pagamento.\n");
        _getch();
        continuar = 0;
    }

    // Finaliza a venda
    system("cls");
    Ascii(5);
    if (total_compra > 0) {
        printf("   ╔════════════════════════════════════════════════════╗\n");
        printf("   ║ Venda finalizada. Total a pagar: R$                ║\n");
        printf("   ║                                                    ║\n");
        printf("   ║           Obrigado por comprar conosco!            ║\n");
        printf("   ║      Pressione qualquer tecla para continuar       ║\n");
        printf("   ╚════════════════════════════════════════════════════╝\n");
        gotoxy(42, 9);
        printf("%.2f", (total_compra + frete));
        _getch();
    } else {
        printf("   ╔══════════════════════════════════════════════╗\n");
        printf("   ║ Venda cancelada. Nenhum valor foi cobrado.   ║\n");
        printf("   ╚══════════════════════════════════════════════╝\n");
    }

    // Libera a memória alocada
    free(produtos);
    free(lista_produtos_ids);
    free(compra_produtos);

    return 0;
}