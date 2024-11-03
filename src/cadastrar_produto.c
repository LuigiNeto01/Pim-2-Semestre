#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "utils.h"
#include "components/ascii.h"

// Função para cadastrar um produto no CSV com id_produto automático
int cadastrar_produto(const char *nome_item, const char *tipo, float preco_venda, float preco_compra, const char *validade, const char *unidade_medida, const char *valor_nutricional, float volume){
    // Declaração de variáveis
    char cwd[1024], linha[1024], caminho_arquivo[2048]; // Variável para armazenar o caminho completo do arquivo
    int max_id = 0, id_atual, novo_id;
    char *token;
    FILE *arquivo;

    // Obter o diretório atual
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // Construir o caminho completo para "data/produtos.csv"
        snprintf(caminho_arquivo, sizeof(caminho_arquivo), "%s/data/produtos.csv", cwd);
    }
    else{
        printf("Erro ao obter o caminho\n");
        return -1;
    }

    // Abre o arquivo em modo de leitura e anexação (read and append)
    arquivo = fopen(caminho_arquivo, "a+");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo produtos.csv");
        return -1;
    }

    // Move o ponteiro para o início do arquivo para ler
    rewind(arquivo);

    // Lê cada linha para encontrar o maior id_produto
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Ignora linhas vazias
        if (strlen(linha) <= 1) continue;

        // Usa strtok para separar os campos pelo delimitador ';'
        token = strtok(linha, ";");
        if(token != NULL){
            id_atual = atoi(token);
            if(id_atual > max_id){
                max_id = id_atual;
            }
        }
    }

    // Define o próximo id_produto
    novo_id = max_id + 1;

    // Escreve os dados no formato CSV separado por ponto e vírgula, incluindo o id_produto
    fprintf(arquivo, "%d;%s;%s;%.2f;%.2f;%s;%s;%s;0;%.2f\n",
            novo_id,
            nome_item,
            tipo,
            preco_venda,
            preco_compra,
            validade,
            unidade_medida,
            valor_nutricional,
            volume);

    // Fecha o arquivo
    if (fclose(arquivo) != 0) {
        perror("Erro ao fechar o arquivo produtos.csv");
        return -1;
    }

    return 0; // Sucesso
}

// Função auxiliar para capturar e validar o preço
float capturaPreco() {
    // Declaração de variáveis
    int j, i = 0, ponto = 0;
    char preco_str[20];
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
    for(j = 0; j < i; j++) {
        if(preco_str[j] == ',') {
            preco_str[j] = '.';
            break;
        }
    }
    return atof(preco_str);
}

// Função para realizar o cadastro do produto com interface de usuário
void cadastro_produto(){
    // Declaração de variáveis
    char nome_item[50];
    char tipo[50];
    char unidade_medida[50];
    char valor_nutricional[50];
    char validade[50];
    float preco_compra, preco_venda, volume;
    int resultado;

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

    // Interface para Validade do Produto
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite a Validade do Produto em Dias:                                              ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");

    // Obter o nome do produto
    gotoxy(28, 9); 
    fgets(nome_item, sizeof(nome_item), stdin);
    nome_item[strcspn(nome_item, "\n")] = '\0';

    // Obter o tipo do produto
    gotoxy(28, 12); 
    fgets(tipo, sizeof(tipo), stdin);
    tipo[strcspn(tipo, "\n")] = '\0';

    // Obter a validade do produto
    gotoxy(40, 15); 
    fgets(validade, sizeof(validade), stdin);
    validade[strcspn(validade, "\n")] = '\0';
    
    // Limpar para manter apenas 3 itens por vez na tela
    system("cls");
    Ascii(3);

    // Interface para Valor Nutricional do Produto
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite o Valor Nutricional do Produto:                                             ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");

    // Interface para Unidade de Medida do Produto
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite a Unidade de Medida do Produto:                                             ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");

    // Obter o valor nutricional do produto
    gotoxy(41, 9); 
    fgets(valor_nutricional, sizeof(valor_nutricional), stdin);
    valor_nutricional[strcspn(valor_nutricional, "\n")] = '\0';
    
    // Obter a unidade de medida do produto
    gotoxy(41, 12); 
    fgets(unidade_medida, sizeof(unidade_medida), stdin);
    unidade_medida[strcspn(unidade_medida, "\n")] = '\0';

    // Limpar para manter apenas 3 itens por vez na tela
    system("cls");
    Ascii(3);

    // Interface para Preco de Compra do Produto
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite o Preço de Compra do Produto: R$                                            ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");

    // Interface para Preco de Venda do Produto
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite o Preço de Venda do Produto: R$                                             ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");

    // Intyerface para Volume do Produto
    printf("╔════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite o Volume do Produto (m³):                                                   ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════╝\n");

    // Obter o preço comrpa do produto com validação
    gotoxy(42, 9);
    preco_compra = capturaPreco();

    // Obter o preço venda do produto com validação
    gotoxy(41, 12);
    preco_venda = capturaPreco();

    // Obter o volume do produto
    gotoxy(34, 15);
    volume = capturaPreco(); // sim, eu estou utilizando assim pq fiquei com preguica de renomear, mas funcio igual kk

    // Chamada à função de cadastro do produto
    resultado = cadastrar_produto(nome_item, tipo, preco_venda, preco_compra, validade, unidade_medida, valor_nutricional, volume);
    if (resultado == 0) {
        printf("Produto cadastrado com sucesso!\n");
    } else {
        printf("Falha ao cadastrar o produto.\n");
    }
    return;
}
