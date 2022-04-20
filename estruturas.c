#include "estruturas.h"
#include <stddef.h>
typedef struct no{
    int chave;
    struct no *esquerda;
    struct no *direita;
    int altura;
    int fator;
}No;

//Criando novo no e retornando seu endereco
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

//Altura do n�
int alturaNo(struct no* no) {
    if(no==NULL)
        return -1;
    else
        return no->altura;
}

//Calculando fator de balanceamento
int fatorBalanceamento(struct no *raiz){
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

//Rotacao simples a esquerda
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

//Rotacao simples a direita
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

//Rotacao dupla a esquerda
No* RotacaoDuplaEsquerda(No *raiz){
    raiz->direita = RotacaoSimplesDireita(raiz->direita);
    return RotacaoSimplesEsquerda(raiz);
}

//Rota��o dupla a direita
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

//Inserindo no na Arvore e retornando o seu endereco
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

void imprimirCalculo(struct no *raiz){
    if(raiz){
        int direito=fatorBalanceamento(raiz->direita);
        int esquerdo=fatorBalanceamento(raiz->esquerda);
        imprimirCalculo(raiz->direita);
        imprimirCalculo(raiz->esquerda);
        printf("[%d] %d - %d = %d \n", raiz->chave, direito, esquerdo, raiz->fator);
    }else{
    return 0;
    }
}

//Desalocando nos da Arvore Binaria
void liberaNo(struct no *no){
    if(no!=NULL){
        liberaNo(no->esquerda);
        liberaNo(no->direita);
        free(no);
        no=NULL;
    }

}

No* reiniciar(struct no *raiz){
    if(raiz!=NULL){
        liberaNo(raiz->esquerda);
        liberaNo(raiz->direita);
        raiz=NULL;
    }
    return raiz;

}
