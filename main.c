#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// Importando funcoes de codigos auxiliares 
#include "src/login.c"
#include "src/components/ascii.c"
#include "src/utils.h"
#include "src/utils.c"

void tela_menu(int login_resultado) {
    int escolha;
    
    Ascii(1);
    printf("╔═════════════════════════════╗\n");
    printf("║     *Escolha uma opção*     ║\n");
    printf("║ 1- Vendas                   ║\n");
    printf("║ 2- Registros                ║\n");
    printf("║ 3- Cadastrar produtos       ║\n");
    printf("║ 4- Dashboards               ║\n");
    printf("║ 5- Avisos                   ║\n");
    printf("║ 6- Sair                     ║\n");
    if(login_resultado == 1){
        printf("║ 7- Cadastrar funcionarios   ║\n");
    }
    printf("╚═════════════════════════════╝\n");

    // Imprimir a caixa para entrada de escolha centralizada
    gotoxy(0, 18);
    printf("╔════════════════════╗\n");
    gotoxy(0, 19);
    printf("║ Sua escolha:       ║\n");
    gotoxy(0, 20);
    printf("╚════════════════════╝\n\n");

    gotoxy(15, 19);
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            // Função ou código para Vendas
            break;
        case 2:
            // Função ou código para Registros
            break;
        case 3:
            // Função ou código para Cadastrar produtos
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
