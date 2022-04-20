#include "arquivos.h"

//Menu de op��es
void menu(){
    printf("------------------------ [ Menu ] --------------------------\n"
	"                 1 -   Gerar ABP\n"
    "                 2 -   Calcular fator de balanceamento\n"
	"                 3 -   Imprimir ABP\n"
	"                 4 -   Sair\n"
    "-------------------------------------------------------------\n");
    printf("Escolha uma das opcoes: ");
}
void opcoes(){
    printf("------------------------ [ Escolha ] --------------------------\n"
	"                 1 -   Abrir arquivo especifico\n"
    "                 2 -   Abrir arquivo aleatorio\n"
    "-------------------------------------------------------------\n");
    printf("Abrir arquivo especifico ou abrr arquivo gerado pelo sistema?\n");
    printf("Escolha uma das opcoes: ");
}
// Abrir arquivo existente para leiturua.
FILE *abrir_arquivo_leitura(char *f_endereco_ptr){
    //Retornar arquivo existente aberto para leitura
    return fopen(f_endereco_ptr, "r");
}
// Abrir novo arquivo para escrita
FILE *abrir_arquivo_escrita(char *f_endereco_ptr){
    //Retorna o arquivo aberto para escrita
    return fopen(f_endereco_ptr, "w");
}
// Gerar arquivo aleatorio
void criar_arquivo_aleatorio(){
    FILE *arquivo;
    arquivo = fopen("numeros.csv", "w+");
    int num;
    int max = 0;

    srand(time(NULL));
    max = rand() % 20;
    for (int i = 0; i < max; i++){
        /* Gerar valores aleat�rios entre zero e 1000 */
        num = rand() % 300;
        fprintf(arquivo, "%i", num);
        fprintf(arquivo, "%s", ",");
    }
    printf("Arquivo aleatorio criado com sucesso.");
    fclose(arquivo);
}
// Limpar tela
void limpar(){
    system("cls || clear");
}
// Sair do programa:
void sair(){
    printf("\n ----- Encerrado com sucesso ----- \n");
    getch();
}
