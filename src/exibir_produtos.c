#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "components/ascii.h"

void exibir_tabela() {
    system("cls");
    Ascii(4);
    char cwd[1024];
    char caminho_arquivo[2048];
    char linha[1024];

    // Obter o diretório atual
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // Construir o caminho completo para "data/produtos.csv"
        snprintf(caminho_arquivo, sizeof(caminho_arquivo), "%s/data/produtos.csv", cwd);
    } else {
        printf("Erro ao obter o caminho\n");
        return;
    }

    // Abre o arquivo em modo de leitura
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo produtos.csv");
        return;
    }

    // Exibir cabeçalho da tabela
    printf("╔══════╦════════════════════╦════════════════╦════════════╦═════════════╦════════════════╦════════════════════╗\n");
    printf("║ ID   │ Nome Item          │ Tipo           │ Preço      │ Validade    │ Unidade Medida │ Valor Nutricional  ║\n");
    printf("╟──────┼────────────────────┼────────────────┼────────────┼─────────────┼────────────────┼────────────────────╢\n");

    // Ler cada linha do arquivo e exibir
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int id_produto;
        char nome_item[50], tipo[20], preco[20], validade[20], unidade_medida[20], valor_nutricional[20];
        
        // Separar os valores da linha usando ';' como delimitador
        sscanf(linha, "%d;%49[^;];%19[^;];%19[^;];%19[^;];%19[^;];%19[^\n]", 
               &id_produto, nome_item, tipo, preco, validade, unidade_medida, valor_nutricional);

        // Exibir linha formatada
        printf("║ %-4d │ %-18s │ %-14s │ %-10s │ %-11s │ %-14s │ %-16s ║\n", 
               id_produto, nome_item, tipo, preco, validade, unidade_medida, valor_nutricional);
    }

    // Fechar o arquivo
    fclose(arquivo);

    // Exibir rodapé da tabela
    printf("╚══════╩════════════════════╩════════════════╩════════════╩═════════════╩════════════════╩════════════════════╝\n");
    _getch();
}
