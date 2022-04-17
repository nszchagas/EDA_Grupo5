#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED
typedef struct no No;
int maior(int x, int y);
int alturaNo(struct no* no);
int fatorBalanceamento(No *raiz);
No* RotacaoSimplesEsquerda(No *raiz);
No* RotacaoSimplesDireita(No *raiz);
No* RotacaoDuplaEsquerda(No *raiz);
No* RotacaoDuplaDireita(No *raiz);
No* balancear(No *raiz);
No* inserir(No *raiz, int valor);
void imprimir(struct no *raiz);
void liberaNo(struct no *no);
#endif // ESTRUTURAS_H_INCLUDED
