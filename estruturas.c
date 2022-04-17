#include "estruturas.h"
#include <stddef.h>
typedef struct no{
    int chave;
    struct no *esquerda;
    struct no *direita;
    int altura;
    int fator;
}No;

//Criando novo no e retornando seu endereço
No* novoNo(int x){
    No *novo = malloc(sizeof(No));

    if(novo){
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->chave = x;
        novo->altura= 0;
    }else{
        printf("Erro ao alocar no.");
    }
    return novo;
}

//Maior valor
int maior(int x, int y){
    if(x>y)
        return x;
    else
        return y;
}

//Altura do nó
int alturaNo(struct no* no) {
    if(no==NULL)
        return -1;
    else
        return no->altura;
}
//Calculando fator de balanceamento
int fatorBalanceamento(No *raiz){
    if(raiz){
        int direito=fatorBalanceamento(raiz->direita);
        int esquerdo=fatorBalanceamento(raiz->esquerda);
        int Balanceamento=direito-esquerdo;
        raiz->fator=Balanceamento;
        return (alturaNo(raiz->esquerda) - alturaNo(raiz->direita));
    }else{
        return 0;
    }
}

//Rotacação simples à1 esquerda
No* RotacaoSimplesEsquerda(No *raiz){
    No *y, *f;
    y = raiz->direita;
    f = y->esquerda;

    y->esquerda = raiz;
    raiz->direita = f;

    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    y->altura = maior(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;

    return y;
}

//Rotação simples à direita
No* RotacaoSimplesDireita(No *raiz){
    No *y, *f;
    y = raiz->esquerda;
    f = y->direita;

    y->direita = raiz;
    raiz->esquerda = f;

    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    y->altura = maior(alturaNo(y->esquerda), alturaNo(y->direita)) + 1;

    return y;
}

//Rotação dupla à esquerda
No* RotacaoDuplaEsquerda(No *raiz){
    raiz->direita = RotacaoSimplesDireita(raiz->direita);
    return RotacaoSimplesEsquerda(raiz);
}

//Rotação dupla à direita
No* RotacaoDuplaDireita(No *raiz){
    raiz->esquerda = RotacaoSimplesEsquerda(raiz->esquerda);
    return RotacaoSimplesDireita(raiz);
}

//Balanceando
No* balancear(No *raiz){
    short fatorBalanca = fatorBalanceamento(raiz);

    if(fatorBalanca < -1 && fatorBalanceamento(raiz->direita) <= 0){
        raiz = RotacaoSimplesEsquerda(raiz);
    }else if( fatorBalanca > 1 && fatorBalanceamento(raiz ->esquerda) >= 0){
        raiz = RotacaoSimplesDireita(raiz);
    }else if( fatorBalanca > 1 && fatorBalanceamento(raiz->esquerda) < 0){
        raiz = RotacaoDuplaDireita(raiz);
    }else if( fatorBalanca < -1 && fatorBalanceamento(raiz->direita) > 0){
        raiz = RotacaoDuplaEsquerda(raiz);
    }

    return raiz;
}

//Inserindo nó na árvore e retornando o seu endereço
No* inserir(No *raiz, int valor){
    if(raiz == NULL){
        return novoNo(valor);
    }else if(valor < raiz->chave){
            raiz->esquerda = inserir(raiz->esquerda,valor);
    }else if(valor > raiz->chave){
            raiz->direita = inserir(raiz->direita,valor);
    }else{
       printf("Insercao nao realizada. %d existe", valor);
    }
    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita))+1;
    raiz = balancear(raiz);
    fatorBalanceamento(raiz);

    return raiz;
}

void imprimirArvore(No *raiz, int nivel){
    int i;
    if(raiz){
        imprimirArvore(raiz->direita, nivel+1);
        printf("\n\n");
        for(i = 0; i<nivel;i++){
            printf("\t");
        }
        printf("%d", raiz->chave);
        imprimirArvore(raiz->esquerda, nivel+1);
    }

}

//Imprimindo as chaves e o fator de balanceamento
void imprimir(struct no *raiz){
    if(raiz!=NULL){
        imprimir(raiz->esquerda);
        printf("Chave:%d ||| FatorBalanceamento:%d \n", raiz->chave, raiz->fator);
        imprimir(raiz->direita);
    }
}

//Desalocando nós da Árvore Binária
void liberaNo(No *no){
    if(no==NULL){
        return;
    }
    liberaNo(no->esquerda);
    liberaNo(no->direita);
    free(no);
    no=NULL;
}


