#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "utils.h"
#include "doacao.c"


// Função para exibir o menu e retornar a opção selecionada
int exibir_menu_caixa() {
    int escolha = 1; // Índice inicial
    int opcao_selecionada = 1;
    int num_opcoes = 4;
    int linha_inicial = 10;


    system("cls"); // Limpa a tela a cada exibição do menu
    Ascii(8);

    printf("╔════════════════════════════════╗\n");
    printf("║      *Escolha uma opção*       ║\n");
    printf("║~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~║\n");
    printf("║    1- Venda                    ║\n");
    printf("║    2- Compra                   ║\n");
    printf("║    3- Doação                   ║\n");
    printf("║    4- Voltar                   ║\n");
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

int fluxo_caixa(int login_resultado){
        
        while (1) {
            int escolha = exibir_menu_caixa();

            switch (escolha) {
                case 1:
                    venda(login_resultado);
                    break;
                case 2:
                    
                    break;
                case 3:
                    doacao(login_resultado);
                    break;

            }

            // Verifica se foi feito o logout
            if (escolha == 4) {

                break; // Sai do loop do menu e volta para o login
            }
        }
}