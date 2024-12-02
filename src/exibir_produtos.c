#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "components/ascii.h"

// Função para contar o número de caracteres UTF-8
int utf8_strlen(const char *s) {
    int len = 0;
    while (*s) {
        if ((*s & 0xC0) != 0x80) len++;
        s++;
    }
    return len;
}

// Função para imprimir uma string com padding baseado no número de caracteres
void print_padded(const char *s, int width) {
    fputs(s, stdout);
    int len = utf8_strlen(s);
    for(int i = len; i < width; i++) {
        fputc(' ', stdout);
    }
}

void exibir_tabela() {
    system("chcp 65001 > nul"); // Define a página de código para UTF-8 silenciosamente
    system("cls");
    Ascii(3);
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
    printf("╔══════╦════════════════════╦════════════════╦════════════╦═════════════╦════════════════╗\n");
    printf("║ ID   │ Nome Item          │ Tipo           │ Preço      │ Validade    │ Unidade Medida ║\n");
    printf("╟──────┼────────────────────┼────────────────┼────────────┼─────────────┼────────────────╢\n");

    // Ler e descartar a primeira linha (cabeçalho)
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        // Se não houver linhas no arquivo, simplesmente retorna
        fclose(arquivo);
        return;
    }

    // Ler cada linha do arquivo e exibir
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int id_produto;
        char nome_item[50], tipo[20], preco[20], validade[20], unidade_medida[20], valor_nutricional[20];
        
        // Separar os valores da linha usando ';' como delimitador
        sscanf(linha, "%d;%49[^;];%19[^;];%19[^;];%19[^;];%19[^;];%19[^\n]", 
               &id_produto, nome_item, tipo, preco, validade, unidade_medida, valor_nutricional);

        // Exibir linha formatada com bordas
        printf("║ ");
        printf("%-4d │ ", id_produto);
        print_padded(nome_item, 18);
        printf(" │ ");
        print_padded(tipo, 14);
        printf(" │ ");
        print_padded(preco, 10);
        printf(" │ ");
        print_padded(validade, 11);
        printf(" │ ");
        print_padded(unidade_medida, 14);
        printf(" ║\n");
        
        // Imprimir a linha separadora
        printf("╟──────┼────────────────────┼────────────────┼────────────┼─────────────┼────────────────╢\n");
    }

    // Fechar o arquivo
    fclose(arquivo);

    // Exibir rodapé da tabela
    printf("╚══════╩════════════════════╩════════════════╩════════════╩═════════════╩════════════════╝\n");
    _getch();
}
