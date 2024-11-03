#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "utils.h"
#include "components/ascii.h"

int cadastrar_produto(const char *nome_item, const char *tipo, float preco, const char *validade, const char *unidade_medida, const char *valor_nutricional){
    // Define o locale para garantir que caracteres especiais e acentos sejam tratados corretamente
    setlocale(LC_ALL, "");
    char cwd[1024];
    char caminho_arquivo[2048]; // Variável para armazenar o caminho completo do arquivo

    // Obter o diretório atual
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // Construir o caminho completo para "data/produtos.csv"
        snprintf(caminho_arquivo, sizeof(caminho_arquivo), "%s/data/produtos.csv", cwd);
    }
    else{
        printf("Erro ao obter o caminho");
    }

    // Abre o arquivo em modo de anexação (append)
    FILE *arquivo = fopen(caminho_arquivo, "a+");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo produtos.csv");
        return -1;
    }

    // Escreve os dados no formato CSV separado por ponto e vírgula
    fprintf(arquivo, "%s;%s;%.2f;%s;%s;%s\n", 
            nome_item, 
            tipo, 
            preco, 
            validade, 
            unidade_medida, 
            valor_nutricional);

    // Fecha o arquivo
    if (fclose(arquivo) != 0) {
        perror("Erro ao fechar o arquivo produtos.csv");
        return -1;
    }

    return 0; // Sucesso
}

void capturaValidade(char *validade) {
    int i = 0;
    char c;
    
    while (i < 10) {
        c = getch(); // Captura um caractere sem exibir na tela
        
        if (i == 2 || i == 5) {
            // Insere as barras '/' automaticamente
            validade[i++] = '/';
            printf("/");
        }
        
        // Verifica se o caractere é um número (dígito)
        if (c >= '0' && c <= '9') {
            validade[i++] = c;
            printf("%c", c); // Exibe o caractere capturado
        }
    }
    validade[i] = '\0'; // Finaliza a string com o caractere nulo
}

// Função auxiliar para capturar e validar o preço
float capturaPreco() {
    char preco_str[20];
    int i = 0, ponto = 0;
    char c;

    while (1) {
        c = getch(); // Captura um caractere sem exibir na tela
        
        if (c == '\r') { // Enter pressionado
            if (i == 0) {
                // Nenhum caractere digitado
                continue;
            }
            if (preco_str[i-1] == ',') {
                // Último caractere não pode ser vírgula
                continue;
            }
            break;
        }
        
        if (c == 8) { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b"); // Remove o último caractere na tela
                if (preco_str[i] == ',') {
                    ponto = 0;
                }
            }
            continue;
        }

        if ((c >= '0' && c <= '9') || (c == ',' && !ponto)) {
            if (c == ',') {
                ponto = 1;
            }
            if (i < sizeof(preco_str) - 1) {
                preco_str[i++] = c;
                printf("%c", c);
            }
        }
        // Ignora qualquer outro caractere
    }
    preco_str[i] = '\0';

    // Substitui a vírgula por ponto para conversão
    for(int j = 0; j < i; j++) {
        if(preco_str[j] == ',') {
            preco_str[j] = '.';
            break;
        }
    }
    return atof(preco_str);
}

void cadastro_produto(){
    char nome_item[50], tipo[50], validade[11], unidade_medida[50], valor_nutricional[50];
    float preco;

    system("cls"); // Limpa a tela (Windows)
    Ascii(3);

    // Interface para Nome do Produto
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite o Nome do Produto:                                                          ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");

    // Interface para Tipo do Produto
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite o Tipo do Produto:                                                          ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");

    // Interface para Preço do Produto
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite o Preço do Produto: R$                                                      ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");

    // Obter o nome do produto
    gotoxy(28, 9); 
    fgets(nome_item, sizeof(nome_item), stdin);
    nome_item[strcspn(nome_item, "\n")] = '\0';

    // Obter o tipo do produto
    gotoxy(28, 12); 
    fgets(tipo, sizeof(tipo), stdin);
    tipo[strcspn(tipo, "\n")] = '\0';

    // Obter o preço do produto com validação
    gotoxy(32, 15); 
    preco = capturaPreco();

    // Limpar para manter apenas 3 itens por vez na tela
    system("cls");
    Ascii(3);

    // Interface para Validade do Produto
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite a Validade do Produto: __/__/____                                           ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");

    // Interface para Unidade de Medida do Produto
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite a Unidade de Medida do Produto:                                             ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");

    // Interface para Valor Nutricional do Produto
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite o Valor Nutricional do Produto:                                             ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");

    // Obter a validade do produto
    gotoxy(32, 9); 
    capturaValidade(validade);

    // Obter a unidade de medida do produto
    gotoxy(41, 12); 
    fgets(unidade_medida, sizeof(unidade_medida), stdin);
    unidade_medida[strcspn(unidade_medida, "\n")] = '\0';

    // Obter o valor nutricional do produto
    gotoxy(41, 15); 
    fgets(valor_nutricional, sizeof(valor_nutricional), stdin);
    valor_nutricional[strcspn(valor_nutricional, "\n")] = '\0';

    // Chamada à função de cadastro do produto
    if (cadastrar_produto(nome_item, tipo, preco, validade, unidade_medida, valor_nutricional) == 0) {
        printf("Produto cadastrado com sucesso!\n");
    } else {
        printf("Falha ao cadastrar o produto.\n");
    }
    return;
}