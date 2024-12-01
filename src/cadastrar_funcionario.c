#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "components/ascii.h"
// Função para obter o último ID no arquivo CSV
int obter_ultimo_id(const char* caminho_arquivo) {
    FILE* arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        // Caso o arquivo não exista ou esteja vazio, começamos com o ID 0
        return 0;
    }

    int ultimo_id = 0;
    char linha[256];

    // Ler o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char* token = strtok(linha, ";"); // Pegar o primeiro campo (ID)
        if (token != NULL) {
            ultimo_id = atoi(token); // Converter para inteiro
        }
    }

    fclose(arquivo);
    return ultimo_id;
}

// Função para salvar credenciais no arquivo CSV
void salvar_credenciais(const char* nome_funcionario, const char* data_entrada_empresa, const char* senha_acesso) {
    const char* caminho_arquivo = "data/credenciais_funcionarios.csv";

    // Obter o próximo ID
    int novo_id = obter_ultimo_id(caminho_arquivo) + 1;

    // Abrir o arquivo em modo append
    FILE* arquivo = fopen(caminho_arquivo, "a");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo"); // Log de erro
        return;
    }

    // Escrever os dados no arquivo
    fprintf(arquivo, "\n%d;%s;%s;%s;", novo_id, nome_funcionario, data_entrada_empresa, senha_acesso);

    fclose(arquivo);
    printf("Credenciais do funcionário ID %d salvas com sucesso! 📁✅\n", novo_id);
}


//    const char* nome = "Luigi Neto";
//    const char* data_entrada = "22/01/2006";
//    const char* senha = "123";
//    salvar_credenciais(nome, data_entrada, senha);
int cadastrar_funcionario(){

    char nome_funcionario[50];
    char senha_funcionario[50];
    char aniversario_funcionario[50];

    system("cls");
    Ascii(11);
    printf("╔════════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite o Nome do funcionario:                                                          ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════════╝\n");

    gotoxy(32, 16); 
    fgets(nome_funcionario, sizeof(nome_funcionario), stdin);
    nome_funcionario[strcspn(nome_funcionario, "\n")] = '\0';
    system("cls");
    Ascii(11);
    printf("╔════════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite a Senha do funcionario:                                                         ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════════╝\n");

    gotoxy(33, 16); 
    fgets(senha_funcionario, sizeof(senha_funcionario), stdin);
    senha_funcionario[strcspn(senha_funcionario, "\n")] = '\0';
    system("cls");
    Ascii(11);
    printf("╔════════════════════════════════════════════════════════════════════════════════════════╗\n"); 
    printf("║ Digite o aniversário do funcionario (dd/mm/aaaa):                                      ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════════════╝\n");

    gotoxy(52, 16); 
    fgets(aniversario_funcionario, sizeof(aniversario_funcionario), stdin);
    aniversario_funcionario[strcspn(aniversario_funcionario, "\n")] = '\0';

    salvar_credenciais(nome_funcionario, aniversario_funcionario, senha_funcionario);
}