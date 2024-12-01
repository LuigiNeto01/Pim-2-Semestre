// dashboard.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "utils.h"
#include "venda.h"  // Inclui a definição de Produto e Venda

#define MAX_PRODUTOS 100
#define MAX_VENDAS 1000
#define MAX_LINHA 1024

// Função para substituir vírgulas por pontos em uma string
void substituir_virgula(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
}

// Funções auxiliares para carregar os dados
int carregar_vendas(Venda vendas[]) {
    FILE *fp = fopen("data/registro_vendas.csv", "r");
    if (!fp) {
        printf("Erro ao abrir data/registro_vendas.csv\n");
        mostrar_cursor();
        system("pause");
        return 0;
    }

    char linha[MAX_LINHA];
    int count = 0;

    // Ignorar a primeira linha (cabeçalho)
    fgets(linha, MAX_LINHA, fp);

    while (fgets(linha, MAX_LINHA, fp)) {
        Venda v;
        char *token = strtok(linha, ";\n");
        if (token == NULL) continue;
        strcpy(v.timestamp, token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        v.id_funcionario = atoi(token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        substituir_virgula(token);
        v.preco_venda = atof(token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        strcpy(v.produtos_qnt, token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        strcpy(v.tipo, token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        strcpy(v.cpf, token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        v.modalidade = atoi(token);

        vendas[count++] = v;
    }

    fclose(fp);
    return count;
}

int carregar_produtos(Produto produtos[]) {
    FILE *fp = fopen("data/produtos.csv", "r");
    if (!fp) {
        printf("Erro ao abrir data/produtos.csv\n");
        mostrar_cursor();
        system("pause");
        return 0;
    }

    char linha[MAX_LINHA];
    int count = 0;

    // Ignorar a primeira linha (cabeçalho)
    fgets(linha, MAX_LINHA, fp);

    while (fgets(linha, MAX_LINHA, fp)) {
        Produto p;
        char *token = strtok(linha, ";\n");
        if (token == NULL) continue;
        p.id_produto = atoi(token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        strcpy(p.nome_item, token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        strcpy(p.tipo, token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        substituir_virgula(token);
        p.preco_venda = atof(token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        substituir_virgula(token);
        p.preco_compra = atof(token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        strcpy(p.validade, token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        strcpy(p.unidade_medida, token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        strcpy(p.valor_nutricional, token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        p.quantidade_estoque = atoi(token);

        token = strtok(NULL, ";\n");
        if (token == NULL) continue;
        substituir_virgula(token);
        p.volume = atof(token);

        produtos[count++] = p;
    }

    fclose(fp);
    return count;
}

// Função para desenhar uma caixa na tela
void desenhar_caixa(int x1, int y1, int x2, int y2) {
    int i;
    gotoxy(x1, y1); printf("╔");
    for (i = x1 + 1; i < x2; i++) printf("═");
    printf("╗");

    for (i = y1 + 1; i < y2; i++) {
        gotoxy(x1, i); printf("║");
        gotoxy(x2, i); printf("║");
    }

    gotoxy(x1, y2); printf("╚");
    for (i = x1 + 1; i < x2; i++) printf("═");
    printf("╝");
}

// Função para centralizar texto
void centralizar_texto(int y, const char* texto) {
    int largura = 80;
    int x = (largura - strlen(texto)) / 2;
    gotoxy(x, y);
    printf("%s", texto);
}

void dashboard(int id_funcionario) {
    ocultar_cursor();
    system("cls");

    Produto produtos[MAX_PRODUTOS];
    Venda vendas[MAX_VENDAS];
    int total_produtos = carregar_produtos(produtos);
    int total_vendas = carregar_vendas(vendas);

    float total_vendas_func = 0;
    int num_transacoes_func = 0;
    float media_venda_func = 0;
    int qtd_produtos_vendidos[MAX_PRODUTOS] = {0};
    int i, j;

    // Cálculos para funcionário específico ou administrador
    for (i = 0; i < total_vendas; i++) {
        if (id_funcionario == 1 || vendas[i].id_funcionario == id_funcionario) {
            if (vendas[i].modalidade == 1) { // Somente vendas
                total_vendas_func += vendas[i].preco_venda;
                num_transacoes_func++;
            }

            // Processar produtos e quantidades
            char produtos_qnt[500];
            strcpy(produtos_qnt, vendas[i].produtos_qnt);

            char *token = strtok(produtos_qnt, "|");
            while (token != NULL) {
                int id_prod;
                float qtd;
                sscanf(token, "%d:%f", &id_prod, &qtd);
                qtd_produtos_vendidos[id_prod - 1] += qtd;

                token = strtok(NULL, "|");
            }
        }
    }

    if (num_transacoes_func > 0)
        media_venda_func = total_vendas_func / num_transacoes_func;

    // Exibir dashboard
    desenhar_caixa(2, 1, 78, 24);
    centralizar_texto(2, "DASHBOARD");

    gotoxy(4, 4);
    printf("Total de Vendas: R$ %.2f", total_vendas_func);
    gotoxy(4, 5);
    printf("Numero de Transacoes: %d", num_transacoes_func);
    gotoxy(4, 6);
    printf("Media por Venda: R$ %.2f", media_venda_func);

    // Produtos mais vendidos
    typedef struct {
        int id_produto;
        float quantidade;
    } ProdutoVendido;

    ProdutoVendido produtos_vendidos[MAX_PRODUTOS];
    int count_prod_vendidos = 0;

    for (i = 0; i < total_produtos; i++) {
        if (qtd_produtos_vendidos[i] > 0) {
            produtos_vendidos[count_prod_vendidos].id_produto = produtos[i].id_produto;
            produtos_vendidos[count_prod_vendidos].quantidade = qtd_produtos_vendidos[i];
            count_prod_vendidos++;
        }
    }

    // Ordenar produtos por quantidade vendida
    for (i = 0; i < count_prod_vendidos - 1; i++) {
        for (j = i + 1; j < count_prod_vendidos; j++) {
            if (produtos_vendidos[j].quantidade > produtos_vendidos[i].quantidade) {
                ProdutoVendido temp = produtos_vendidos[i];
                produtos_vendidos[i] = produtos_vendidos[j];
                produtos_vendidos[j] = temp;
            }
        }
    }

    gotoxy(4, 8);
    printf("Produtos Mais Vendidos:");
    for (i = 0; i < 5 && i < count_prod_vendidos; i++) {
        gotoxy(6, 9 + i);
        int id_prod = produtos_vendidos[i].id_produto;
        printf("%d. %s - %.2f unidades", i + 1, produtos[id_prod - 1].nome_item, produtos_vendidos[i].quantidade);
    }

    // Modalidade de Vendas
    int vendas_online = 0, vendas_presencial = 0;
    for (i = 0; i < total_vendas; i++) {
        if (id_funcionario == 1 || vendas[i].id_funcionario == id_funcionario) {
            if (vendas[i].modalidade == 1) { // Somente vendas
                if (strcmp(vendas[i].tipo, "Online") == 0)
                    vendas_online++;
                else if (strcmp(vendas[i].tipo, "Presencial") == 0)
                    vendas_presencial++;
            }
        }
    }

    int total_modalidades = vendas_online + vendas_presencial;
    float perc_online = (total_modalidades > 0) ? (vendas_online * 100.0) / total_modalidades : 0;
    float perc_presencial = (total_modalidades > 0) ? (vendas_presencial * 100.0) / total_modalidades : 0;

    gotoxy(4, 15);
    printf("Modalidade de Vendas:");
    gotoxy(6, 16);
    printf("Online: %.1f%% (%d vendas)", perc_online, vendas_online);
    gotoxy(6, 17);
    printf("Presencial: %.1f%% (%d vendas)", perc_presencial, vendas_presencial);

    // Se for administrador, mostrar mais informações
    if (id_funcionario == 1) {
        // Vendas por funcionário
        typedef struct {
            int id_funcionario;
            float total_vendas;
        } VendasFuncionario;

        VendasFuncionario vendas_funcionarios[10];
        int count_funcionarios = 0;

        for (i = 0; i < total_vendas; i++) {
            if (vendas[i].modalidade == 1) { // Somente vendas
                int idx = -1;
                for (j = 0; j < count_funcionarios; j++) {
                    if (vendas_funcionarios[j].id_funcionario == vendas[i].id_funcionario) {
                        idx = j;
                        break;
                    }
                }
                if (idx == -1) {
                    vendas_funcionarios[count_funcionarios].id_funcionario = vendas[i].id_funcionario;
                    vendas_funcionarios[count_funcionarios].total_vendas = vendas[i].preco_venda;
                    count_funcionarios++;
                } else {
                    vendas_funcionarios[idx].total_vendas += vendas[i].preco_venda;
                }
            }
        }

        // Ordenar por total de vendas
        for (i = 0; i < count_funcionarios - 1; i++) {
            for (j = i + 1; j < count_funcionarios; j++) {
                if (vendas_funcionarios[j].total_vendas > vendas_funcionarios[i].total_vendas) {
                    VendasFuncionario temp = vendas_funcionarios[i];
                    vendas_funcionarios[i] = vendas_funcionarios[j];
                    vendas_funcionarios[j] = temp;
                }
            }
        }

        gotoxy(48, 4);
        printf("Vendas por Funcionario:");
        for (i = 0; i < count_funcionarios; i++) {
            gotoxy(50, 5 + i);
            printf("ID %d - R$ %.2f", vendas_funcionarios[i].id_funcionario, vendas_funcionarios[i].total_vendas);
        }

        // Produtos com baixo estoque
        gotoxy(48, 10);
        printf("Produtos com Baixo Estoque:");
        int linha = 11;
        for (i = 0; i < total_produtos; i++) {
            if (produtos[i].quantidade_estoque < 50) {
                gotoxy(50, linha++);
                printf("%s - %d unidades", produtos[i].nome_item, produtos[i].quantidade_estoque);
            }
        }
    }

    gotoxy(4, 22);
    printf("Pressione Enter para voltar...");

    gotoxy(0, 25);
    mostrar_cursor();
    // Esperar o usuário pressionar Enter
    while(getch() != 13); // 13 é o código ASCII para Enter
}
