#include <stdio.h>
#include <stdlib.h>
#include "ascii.h"

void Ascii(int opcao) {
    switch (opcao) {
        case 1:
            printf("\n");
            printf("\033[32m███╗   ███╗███████╗███╗   ██╗██╗   ██╗\033[0m\n");
            printf("\033[32m████╗ ████║██╔════╝████╗  ██║██║   ██║\033[0m\n");
            printf("\033[32m██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║\033[0m\n");
            printf("\033[32m██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║\033[0m\n");
            printf("\033[32m██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝\033[0m\n");
            printf("\033[32m╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝ \033[0m\n");
            printf("\n");
            
            break;
        case 2:
            printf("\n");
            printf("\033[32m██╗      ██████╗  ██████╗ ██╗███╗   ██╗\033[0m\n");
            printf("\033[32m██║     ██╔═══██╗██╔════╝ ██║████╗  ██║\033[0m\n");
            printf("\033[32m██║     ██║   ██║██║  ███╗██║██╔██╗ ██║\033[0m\n");
            printf("\033[32m██║     ██║   ██║██║   ██║██║██║╚██╗██║\033[0m\n");
            printf("\033[32m███████╗╚██████╔╝╚██████╔╝██║██║ ╚████║\033[0m\n");
            printf("\033[32m╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝  ╚═══╝\033[0m\n");
            printf("\n");
            
            break;

        case 3:
            printf("\n");
            printf("\033[32m██████╗ ██████╗  ██████╗ ██████╗ ██╗   ██╗████████╗ ██████╗ ███████╗\033[0m\n");
            printf("\033[32m██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██║   ██║╚══██╔══╝██╔═══██╗██╔════╝\033[0m\n");
            printf("\033[32m██████╔╝██████╔╝██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║███████╗\033[0m\n");
            printf("\033[32m██╔═══╝ ██╔══██╗██║   ██║██║  ██║██║   ██║   ██║   ██║   ██║╚════██║\033[0m\n");
            printf("\033[32m██║     ██║  ██║╚██████╔╝██████╔╝╚██████╔╝   ██║   ╚██████╔╝███████║\033[0m\n");
            printf("\033[32m╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝    ╚═╝    ╚═════╝ ╚══════╝\033[0m\n");
            printf("\n");

        case 4:
            printf("\n");
            printf("\033[32m███████╗███████╗████████╗ ██████╗  ██████╗ ██╗   ██╗███████╗\033[0m\n");
            printf("\033[32m██╔════╝██╔════╝╚══██╔══╝██╔═══██╗██╔═══██╗██║   ██║██╔════╝\033[0m\n");
            printf("\033[32m█████╗  ███████╗   ██║   ██║   ██║██║   ██║██║   ██║█████╗  \033[0m\n");
            printf("\033[32m██╔══╝  ╚════██║   ██║   ██║   ██║██║▄▄ ██║██║   ██║██╔══╝  \033[0m\n");
            printf("\033[32m███████╗███████║   ██║   ╚██████╔╝╚██████╔╝╚██████╔╝███████╗\033[0m\n");
            printf("\033[32m╚══════╝╚══════╝   ╚═╝    ╚═════╝  ╚══▀▀═╝  ╚═════╝ ╚══════╝\033[0m\n");
            printf("\n");
        default:
            printf("\033[31mOpção inválida! Por favor, escolha uma opção válida. ❌\033[0m\n");
            break;
    }
}
