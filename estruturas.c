#include "estruturas.h"
#include <stddef.h>
typedef struct no{ // Nao retirar de avl.c
    int valor;
    struct no *esquerdo, *direito;
    short altura; // Altura do no
    short fator; // Fator de balanceamento
}No;
/**
* Criar novo no.
* Retorna o endereco do novo no.
*/
No* novoNo(int x){
    No *novo = malloc(sizeof(No));

    if(novo){
        novo->valor = x;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
        novo->fator = 0;
    }else{
        printf("Erro ao alocar no.");
    }
    return novo;
}

/**
* Receber duas alturas e verificar a maior altura.
* Retorna a maior altura.
*/
short maior(short a, short b){
    return (a>b)? a: b;
}

/**
* Receber um no e verificar valor NULL.
* Retorna altura se no nao for NULL, -1 caso contrario.
*/
short altura(No *no){
    if(no == NULL){
        return -1;
    }else{
        return no->altura;
    }
}

/**
* Calcular o fator de balanceamento de um no.
* Retorna o fator de balanceamento.
*/
short fator(No *no){
    if(no){
        return (altura(no->esquerdo) - altura(no->direito));
    }else{
        return 0;
    }
}

/**
* Rotacionar no a esquerda.
* Retorna
*/
No* esquerda(No *r){
    No *y, *f;
    y = r->direito;
    f = y->esquerdo;

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(altura(r->esquerdo), altura(r->direito)) + 1;
    y->altura = maior(altura(y->esquerdo), altura(y->direito)) + 1;

    return y;
}

/**
* Rotacionar no a direita.
* Retorna
*/
No* direita(No *r){
    No *y, *f;
    y = r->esquerdo;
    f = y->direito;

    y->direito = r;
    r->esquerdo = f;

    r->altura = maior(altura(r->esquerdo), altura(r->direito)) + 1;
    y->altura = maior(altura(y->esquerdo), altura(y->direito)) + 1;

    return y;
}

/**
* Rotacionar para direita e para esquerda
*/
No* dupla_d_e(No *r){
    r->direito = direita(r->direito);
    return esquerda(r);
}

/**
* Rotacionar para a esquerda e para a direita
*/
No* dupla_e_d(No *r){
    r->esquerdo = esquerda(r->esquerdo);
    return direita(r);
}

/**
*
*/
No* balancear(No *raiz){
    short ft = fator(raiz);

    if(ft <-1 && fator(raiz->direito) <= 0){
        raiz = esquerda(raiz);
    }else if( ft > 1 && fator(raiz ->esquerdo) >= 0){
        raiz = direita(raiz);
    }else if( ft > 1 && fator(raiz->esquerdo) < 0){
        raiz = dupla_e_d(raiz);
    }else if( ft < -1 && fator(raiz->direito) > 0){
        raiz = dupla_d_e(raiz);
    }

    return raiz;
}

/**
* Inserir um novo no na arvore
* Retorna endereco
*/
No* inserir(No *raiz, int x){
    if(raiz == NULL){
        return novoNo(x);
    }else if(x < raiz->valor){
            raiz->esquerdo = inserir(raiz->esquerdo,x);
    }else if(x > raiz->valor){
            raiz->direito = inserir(raiz->direito,x);
    }else{
        printf("Insercao do valor %d nao realizada. O elemento ja existe.\nDemais valores inseridos.\n", x);
    }
    raiz->altura = maior(altura(raiz->esquerdo), altura(raiz->direito))+1;
    raiz = balancear(raiz);
    fator(raiz);

    return raiz;
}

/**
*
*/
No* remover(No *raiz, int chave){
    if(raiz == NULL){
        printf("Valor nao encontrado.\n");
        return NULL;
    }else{
        if(raiz->valor == chave){
            if(raiz->esquerdo == NULL && raiz->direito == NULL){
                free(raiz);
                printf("Elemento %d removido.\n", chave);
                return NULL;
            }
            else{
                if(raiz->esquerdo != NULL && raiz->direito != NULL){
                    No *aux = raiz->esquerdo;
                    while(aux->direito != NULL){
                        aux = aux->direito;
                    }
                raiz->valor = aux->valor;
                aux->valor = chave;
                printf("Elemento %d trocado.\n", chave);
                raiz->esquerdo = remover(raiz->esquerdo, chave);
                return raiz;
            }
            else{
                No *aux;
                if(raiz->esquerdo != NULL){
                    aux = raiz->esquerdo;
                }else{
                    aux = raiz->direito;
                }
                free(raiz);
                printf("Elemento %d com um no removido.\n", chave);
                return aux;
            }
        }
    }else{
        if(chave < raiz->valor){
            raiz->esquerdo = remover(raiz->esquerdo, chave);
        }else{
            raiz->direito = remover(raiz->direito, chave);
        }
    }
    raiz->altura = maior(altura(raiz->esquerdo), altura(raiz->direito))+1;
    raiz=balancear(raiz);
    return raiz;
    }
}

/**
*
*/
void imprimir(No *raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz->direito, nivel+1);
        printf("\n\n");
        for(i = 0; i<nivel;i++){
            printf("\t");
        }
        printf("%d", raiz->valor);
        imprimir(raiz->esquerdo, nivel+1);
    }

}
/**
*
*/

/**
* Desalocar nos da arvore
*/
int liberaNo(No *no){
    if(no == NULL){
        return;
    }
    liberaNo(no->esquerdo);
    liberaNo(no->direito);
    free(no);
    no = NULL;
}
