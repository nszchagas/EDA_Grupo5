#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "gerar_arquivo.h"

//Criando novo no e retornando seu endere�o
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

//Rotaca��o simples � esquerda
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

//Rota��o simples � direita
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

//Rota��o dupla � esquerda
No* RotacaoDuplaEsquerda(No *raiz){
    raiz->direita = RotacaoSimplesDireita(raiz->direita);
    return RotacaoSimplesEsquerda(raiz);
}

//Rota��o dupla � direita
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

//Inserindo n� na �rvore e retornando o seu endere�o
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

    return raiz;
}

//Imprimindo as chaves e o fator de balanceamento
void imprimir(struct no *raiz){
    if(raiz!=NULL){
        imprimir(raiz->esquerda);
        printf("Chave:%d ||| FatorBalanceamento:%d \n", raiz->chave, raiz->fator);
        imprimir(raiz->direita);
    }
}


//Desalocando n�s da �rvore Bin�ria
void liberaNo(struct no *no){
    if(no==NULL){
        return;
    }
    liberaNo(no->esquerda);
    liberaNo(no->direita);
    free(no);
    no=NULL;
}


//Gerando N�meros Aleat�rios (Sem repetir)
void NumerosAleatorios(No *raiz){
    raiz=NULL;
    int i=0;
    int j;
    int igual;
    int valores[20];

    do{
        valores[i]=rand()%100;
        igual=0;
        for(j=0; j<i;j++){
            if(valores[j]==valores[i])
                igual=1;
        }
        if(igual==0)
            i++;
    }while(i<20);

    printf("Numeros Aleatorios: \n");
    for(i=0;i<20;i++){
        printf("%d ", valores[i]);
    }

    for(i=0;i<20;i++){
        raiz=inserir(raiz, valores[i]);
    }
}

int main(){
    int escolha;
    int valor;
    No *raiz = NULL;

    do{
    printf("\n \n \n");
    printf("------------------------ [ Menu ] --------------------------\n"
	"                 1 -   Gerar ABP                             \n"
    "                 2 -   Gerar CSV com numeros aleatorios      \n"
	"                 3 -   Fator de Balanceamento                \n"
	"                 4 -   Imprimir Chaves e FB                  \n"
	"                 5 -   Sair                                  \n"
    "-------------------------------------------------------------\n");
    printf("Escolha uma das opcoes acima: \n \n");
        scanf("%d", &escolha);
        switch(escolha){
            case 1:
                printf("Gerando numeros aleatorios... \n \n");
                NumerosAleatorios(raiz);
                printf("\n \n");
                printf("Inserindo nos na [ArvoreBinaria]... \n \n");
                if (raiz!=NULL)
                    printf("ABP gerada com sucesso!!");
                break;
            case 2:
                criar_arquivo();
                break;
            case 3:
                printf("Calculando o fator de Balanceamento... \n \n");
                fatorBalanceamento(raiz);
                if(raiz->fator<2 && raiz->fator>-2 )
                    printf("Arvore Balanceada com sucesso!");
                break;
            case 4:
                printf("Imprimindo Chaves e Balanceamento... \n \n");
                printf("Chaves e Fator de Balanceamento \n");
                imprimir(raiz);
                break;
            case 5:
                printf("Desalocando nos... \n \n");
                liberaNo(raiz);
                if (raiz==NULL);
                    printf("Desalocacao realizada com sucesso! \n");
                break;
            default:
                printf("Invalido!");
        }
    }while(escolha!=5);

    return 0;
}
