#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // Para _getch()
#include <unistd.h> // Para getcwd()

void exibir_fluxo_estoque() {
    system("cls");
    // Ascii(4); // Remova ou mantenha dependendo da sua implementação

    char cwd[1024];
    char caminho_arquivo[2048];
    char linha[2048];

    // Obter o diretório atual
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // Construir o caminho completo para "data/registro_vendas.csv"
        snprintf(caminho_arquivo, sizeof(caminho_arquivo), "%s/data/registro_vendas.csv", cwd);
    } else {
        printf("Erro ao obter o caminho\n");
        return;
    }

    // Abre o arquivo em modo de leitura
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo registro_vendas.csv");
        return;
    }

    // Exibir cabeçalho da tabela com larguras ajustadas
    printf("╔══════════════════════╦════════════╦══════════════╦═══════════════════════════════════════════╦════════════╦══════════════════╦══════════════╗\n");
    printf("║ Data                 │ ID Func    │ Preço Venda  │ Produto                                   │ Tipo       │ CPF              │ Modalidade   ║\n");
    printf("╟──────────────────────┼────────────┼──────────────┼───────────────────────────────────────────┼────────────┼──────────────────┼──────────────╢\n");

    // Ler cada linha do arquivo e exibir
    // Ignorar a primeira linha (cabeçalho)
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char timestamp[20];
        int id_funcionario;
        float preco_venda;
        char produtos_qnt[1024];
        char tipo[20];
        char cpf[20];
        int modalidade;

        // Remover o caractere de nova linha
        linha[strcspn(linha, "\n")] = 0;

        // Tokenizar a linha usando ';' como delimitador
        char *token;
        int field_count = 0;

        token = strtok(linha, ";");
        while (token != NULL) {
            switch (field_count) {
                case 0:
                    strncpy(timestamp, token, sizeof(timestamp));
                    break;
                case 1:
                    id_funcionario = atoi(token);
                    break;
                case 2:
                    preco_venda = atof(token);
                    break;
                case 3:
                    strncpy(produtos_qnt, token, sizeof(produtos_qnt));
                    break;
                case 4:
                    strncpy(tipo, token, sizeof(tipo));
                    break;
                case 5:
                    strncpy(cpf, token, sizeof(cpf));
                    break;
                case 6:
                    modalidade = atoi(token);
                    break;
            }
            field_count++;
            token = strtok(NULL, ";");
        }

        // Formatar CPF
        if (strcmp(cpf, "0") == 0) {
            strcpy(cpf, "Não Informado   ");
        }

        // Formatar Modalidade
        char modalidade_str[15];
        switch (modalidade) {
            case 1:
                strcpy(modalidade_str, "Venda");
                break;
            case 0:
                strcpy(modalidade_str, "Doação");
                break;
            case 2:
                strcpy(modalidade_str, "Compra");
                break;
            default:
                strcpy(modalidade_str, "Desconhecido");
                break;
        }

        // Reformatar Data para "DD/MM/AAAA HH:MM"
        int year, month, day, hour, minute, second;
        sscanf(timestamp, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);

        char data[20]; // "DD/MM/AAAA HH:MM\0"
        snprintf(data, sizeof(data), "%02d/%02d/%04d %02d:%02d", day, month, year, hour, minute);

        // Processar 'produtos_qnt' para formatação
        // Armazenar os produtos em arrays para facilitar a impressão
        char produtos_ids[100][20];
        char produtos_quantidades[100][20];
        int produtos_count = 0;

        char produtos_qnt_copy[1024];
        strncpy(produtos_qnt_copy, produtos_qnt, sizeof(produtos_qnt_copy));

        char *produto_token = strtok(produtos_qnt_copy, "|");
        while (produto_token != NULL && produtos_count < 100) {
            char *colon_pos = strchr(produto_token, ':');
            if (colon_pos != NULL) {
                *colon_pos = '\0';
                char *product_id = produto_token;
                char *quantity = colon_pos + 1;

                strncpy(produtos_ids[produtos_count], product_id, sizeof(produtos_ids[produtos_count]));
                strncpy(produtos_quantidades[produtos_count], quantity, sizeof(produtos_quantidades[produtos_count]));
                produtos_count++;
            }
            produto_token = strtok(NULL, "|");
        }

        // Imprimir a tabela, uma linha para cada produto
        for (int i = 0; i < produtos_count; i++) {
            // Preparar a string de informação do produto
            char produto_info[50];
            snprintf(produto_info, sizeof(produto_info), "ID %-6s Quant: %-10s", produtos_ids[i], produtos_quantidades[i]);

            if (i == 0) {
                // Primeira linha, imprimir todos os campos
                printf("║ %-20s │ %-10d │ %-12.2f │ %-41s │ %-10s │ %-16s │ %-12s ║\n",
                       data, id_funcionario, preco_venda, produto_info, tipo, cpf, modalidade_str);
            } else {
                // Linhas seguintes, deixar campos em branco exceto o produto e quantidade
                printf("║ %-20s │ %-10s │ %-12s │ %-41s │ %-10s │ %-16s │ %-12s ║\n",
                       "", "", "", produto_info, "", "", "");
            }
        }

        // Se não houver produtos, ainda imprimir a linha
        if (produtos_count == 0) {
            printf("║ %-20s │ %-10d │ %-12.2f │ %-41s │ %-10s │ %-16s │ %-12s ║\n",
                   data, id_funcionario, preco_venda, "", tipo, cpf, modalidade_str);
        }
        // Imprimir uma linha separadora
        printf("╟──────────────────────┼────────────┼──────────────┼───────────────────────────────────────────┼────────────┼──────────────────┼──────────────╢\n");
    }

    // Fechar o arquivo
    fclose(arquivo);

    // Exibir rodapé da tabela
    printf("╚══════════════════════╩════════════╩══════════════╩═══════════════════════════════════════════╩════════════╩══════════════════╩══════════════╝\n");
    _getch();
}
