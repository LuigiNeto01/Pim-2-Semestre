#include "components/ascii.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 512
#define DATA_FILE_PATH "data/credenciais_funcionarios.csv"

int get_id(const char *nome_funcionario, const char *senha_acesso) {
    FILE *file = fopen(DATA_FILE_PATH, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de credenciais: %s\n", DATA_FILE_PATH);
        return 0;
    }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        // Remove possíveis quebras de linha
        line[strcspn(line, "\r\n")] = '\0';

        // Tokeniza a linha usando ';' como delimitador
        char *id_funcionario_str = strtok(line, ";");
        char *nome = strtok(NULL, ";");
        char *data_entrada = strtok(NULL, ";");
        char *senha = strtok(NULL, ";");

        // Verifica se todos os campos estão presentes
        if (id_funcionario_str == NULL || nome == NULL || senha == NULL) {
            continue; // Linha malformada; ignora e passa para a próxima
        }

        // Compara o nome e a senha fornecidos com os do arquivo
        if (strcmp(nome, nome_funcionario) == 0 && strcmp(senha, senha_acesso) == 0) {
            int id_funcionario = atoi(id_funcionario_str);
            fclose(file);
            return id_funcionario;
        }
    }

    fclose(file);
    return 0; // Credenciais não encontradas ou inválidas
}

int login() {
    system("cls");
    int id_user = 0;
    char login[50], senha[50];
    while(id_user == 0) {
        system("cls");
        Ascii(2);

        printf("╔═══════════════════╗\n");
        printf("║ Digite seu login: ║\n");
        printf("╚═══════════════════╝\n");

        fgets(login, sizeof(login), stdin);
        login[strcspn(login, "\n")] = '\0';
        
        system("cls");
        Ascii(2);
        printf("╔═══════════════════╗\n");
        printf("║ Digite seu senha: ║\n");
        printf("╚═══════════════════╝\n");

        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = '\0';

        id_user = get_id(login, senha);
        
        if(id_user == 0){
            printf("╔═══════════════════════╗\n");
            printf("║ Senha ou login errado ║\n");
            printf("╚═══════════════════════╝\n");
        }
    }
    return id_user;
}
