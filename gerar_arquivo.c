#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "gerar_arquivo.h"

void criar_arquivo(){
    FILE *arquivo;
    arquivo = fopen("numeros.txt", "w+");
    int num;
    int max = 0;

    srand(time(NULL));


    max = rand() % 20;


    for (int i = 0; i < max; i++)
        {
            /* gerando valores aleatórios entre zero e 1000 */
            num = rand() % 1000;
            fprintf(arquivo, "%i", num);
            fprintf(arquivo, "%s", " ");
        }

    printf("ta");
    fclose(arquivo);

}