#include <stdio.h>
#include <stdlib.h>

#ifndef main_h
#define main_h
//Definindo estrutura
typedef struct no{
    int chave;
    struct no *esquerda;
    struct no *direita;
    int altura;
    int fator;
}No;

int maior(int x, int y);
int alturaNo(struct no* no);
int fatorBalanceamento(No *raiz);
void imprimir(struct no *raiz);
void liberaNo(struct no *no);
void liberaArvoreBin(struct no *raiz);
int NumerosAleatorios();

#endif //main_h
