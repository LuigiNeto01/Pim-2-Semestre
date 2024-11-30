#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// Importando funcoes de codigos auxiliares 
#include "src/login.c"
#include "src/components/ascii.c"
#include "src/utils.h"
#include "src/utils.c"
#include "src/cadastrar_produto.c"
#include "src/exibir_produtos.c"
#include "src/venda.c"
#include "src/fluxo_estoque.c"

// Função para exibir o menu e retornar a opção selecionada
int exibir_menu(int login_resultado) {
    int escolha = 1; // Índice inicial
    int opcao_selecionada = 1;
    int num_opcoes = 6;
    int linha_inicial = 10;

    // Se login_resultado for 1, adicionamos mais uma opção
    if (login_resultado == 1) {
        num_opcoes = 7;
    }

    system("cls"); // Limpa a tela a cada exibição do menu
    Ascii(1);

    printf("╔════════════════════════════════╗\n");
    printf("║      *Escolha uma opção*       ║\n");
    printf("║~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~║\n");
    printf("║    1- Fluxo de Caixa           ║\n");
    printf("║    2- Tabela de Produtos       ║\n");
    printf("║    3- Cadastrar Produtos       ║\n");
    printf("║    4- Dashboards               ║\n");
    printf("║    5- Avisos                   ║\n");
    printf("║    6- Sair                     ║\n");
    if(login_resultado == 1){
        printf("║    7- Cadastrar funcionários   ║\n");
    }
    printf("║~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~║\n");
    printf("╚════════════════════════════════╝\n");
    
    while (1) {
        // Oculta o cursor
        ocultar_cursor();

        // Exibe o cursor '>' na opção atual
        for (int i = 1; i <= num_opcoes; i++) {
            gotoxy(2, linha_inicial + i); // Move para a posição da opção
            printf("%c", (escolha == i ? '>' : ' '));
        }

        int ch = _getch();
        if (ch == 224) {  // Tecla de seta pressionada
            ch = _getch();
            if (ch == 72) { // Seta para cima
                escolha--;
                if (escolha < 1) escolha = num_opcoes; // Loop para o último item
            } else if (ch == 80) { // Seta para baixo
                escolha++;
                if (escolha > num_opcoes) escolha = 1; // Loop para o primeiro item
            }
        } else if (ch == 13) { // Enter pressionado
            opcao_selecionada = escolha;
            break; // Sair do loop ao selecionar a opção
        }

        // Atualiza o cursor '>' com base na nova escolha
        for (int i = 1; i <= num_opcoes; i++) {
            gotoxy(2, linha_inicial + i); // Move para a posição da opção
            printf("%c", (escolha == i ? '>' : ' '));
        }
    }

    mostrar_cursor();

    return opcao_selecionada;
}

int main() {
    int login_resultado;
    system("chcp 65001"); // Configura o código de página para UTF-8

    while (1) {
        // Realiza o login
        login_resultado = login();
        system("cls");

        if (login_resultado == 0) {
            return 1;
        }

        // Loop principal do software
        while (1) {
            int escolha = exibir_menu(login_resultado);

            switch (escolha) {
                case 1:
                    venda(login_resultado);
                    break;
                case 2:
                    exibir_fluxo_estoque();
                    break;
                case 3:
                    cadastro_produto();
                    break;
                case 4:
                    // Função ou código para Dashboards
                    printf("Funcionalidade Dashboards não implementada.\n");
                    break;
                case 5:
                    // Função ou código para Avisos
                    printf("Funcionalidade Avisos não implementada.\n");
                    break;
                case 6:
                    system("cls");
                    break; // Sai do loop interno para retornar ao login
                case 7:
                    if (login_resultado == 1) {
                        // Função para Cadastrar funcionários
                        printf("Funcionalidade Cadastrar funcionários não implementada.\n");
                    }
                    break;
            }

            // Verifica se foi feito o logout
            if (escolha == 6) {
                break; // Sai do loop do menu e volta para o login
            }
        }
    }

    return 0;
}