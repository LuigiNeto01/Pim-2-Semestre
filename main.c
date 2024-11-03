#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// Importando funcoes de codigos auxiliares 
#include "src/login.c"
#include "src/components/ascii.c"
#include "src/utils.h"
#include "src/utils.c"
#include"src/cadastrar_produto.c"

void tela_menu(int login_resultado) {
    int escolha = 1; // Índice inicial
    int opcao_selecionada;
    int num_opcoes = 6;
    int linha_inicial = 9;

    // Se login_resultado for 1, adicionamos mais uma opção
    if (login_resultado == 1) {
        num_opcoes = 7;
    }
    
    Ascii(1);
    // Oculta o cursor
    ocultar_cursor();

    printf("╔════════════════════════════════╗\n");
    printf("║      *Escolha uma opção*       ║\n");
    printf("║~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~║\n");
    printf("║    1- Vendas                   ║\n");
    printf("║    2- Registros                ║\n");
    printf("║    3- Cadastrar produtos       ║\n");
    printf("║    4- Dashboards               ║\n");
    printf("║    5- Avisos                   ║\n");
    printf("║    6- Sair                     ║\n");
    if(login_resultado == 1){
        printf("║    7- Cadastrar funcionarios   ║\n");
    }
    printf("║~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~║\n");
    printf("╚════════════════════════════════╝\n");

    while (1) {
        // Atualiza o cursor '>' com base na linha inicial
        for (int i = 1; i <= num_opcoes; i++) {
            gotoxy(2, linha_inicial + i); // Mover para a linha da opção com o deslocamento
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
    }
    mostrar_cursor();

    switch (escolha) {
        case 1:
            // Função ou código para Vendas
            break;
        case 2:
            // Função ou código para Registros
            break;
        case 3:
            // Função para Cadastrar produtos
            cadastro_produto();
            break;
        case 4:
            // Função ou código para Dashboards
            break;
        case 5:
            // Função ou código para Avisos
            break;
        case 6:
            system("main");
            break;
        case 7:

            break;
        default:

            break;
    }
}

int main() {
    int login_resultado;
    system("chcp 65001");

    login_resultado = login();
    system("cls"); 
    tela_menu(login_resultado);

    return 0;
}
