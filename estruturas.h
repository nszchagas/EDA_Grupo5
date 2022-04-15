#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED
typedef struct no No;
No* novoNo(int x);
short maior(short a, short b);
short altura(No *no);
short fator(No *no);
No* esquerda(No *r);
No* direita(No *r);
No* dupla_d_e(No *r);
No* dupla_e_d(No *r);
No* balancear(No *raiz);
No* inserir(No *raiz, int x);
No* remover(No *raiz, int chave);
void imprimir(No *raiz, int nivel);



#endif // ESTRUTURAS_H_INCLUDED
