#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"
#include "estruturas.h"

// Grupo 5 - Integrantes:
// Bruno Seiji Kishibe - 200072854
// Mateus de Siqueira Silva - 200024787
// Nicolas Chagas Souza - 200042327
// Pedro Henrique Ferreira - 200026151
// Pedro Lucas Garcia - 190115548

int main(){
    // Declaracoes
    char endereco_arquivo[30]; // Ponteiro para endere�o do arquivo
    FILE *arquivo_csv = NULL;
    int aux, opcao, valor;
    No *raiz = NULL;
    // Instrucoes
    aux = 0, valor = 0;
    // Sinal onde goto deve retornar
    inicio:
    // Limpando a tela ap�s retorno
    if(opcao < 1 && opcao > 5 || opcao >= 1){
        getch();
        limpar();
    }
    menu(); // Chamando menu de escolhas
    scanf("%d", &opcao);
    // Limpando a tela
    limpar();
    switch(opcao){
        /** Concluido. Nao alterar. */
        case 1:
            opcoes();
            opcao = 0;
            scanf("%d", &opcao);
            switch(opcao){
                case 1:
                    raiz = reiniciar(raiz);
                    printf("Digite o endereco do arquivo a ser aberto: ");
                    scanf("%s", endereco_arquivo);
                    arquivo_csv = abrir_arquivo_leitura(endereco_arquivo);
                    goto continua;
                    break;
                case 2:
                    raiz = reiniciar(raiz);
                    criar_arquivo_aleatorio();
                    arquivo_csv = abrir_arquivo_leitura("numeros.csv");
                    goto continua;
                    break;
                default:
                    limpar();
                    printf("Invalido!\n");
                    goto inicio;
                    break;
            }
            // Sinal 2 onde o goto deve continuar
            continua:
            // Avaliando arquivo aberto e gerar arvore
            if(arquivo_csv == NULL){
                //N�o aberto
                printf("Erro! Arquivo %s nao pode ser aberto.\n", endereco_arquivo);
            }else{
                rewind(arquivo_csv);
                // Inserindo todos os numeros do arquivo na arvore
                while((aux = fscanf(arquivo_csv, "%d", &valor) != EOF)){
                    raiz = inserir(raiz, valor);
                    fseek(arquivo_csv, 1, SEEK_CUR);
                }
            }
            goto inicio;
            break;
        case 2:
            printf("Calculando fatores de balanceamento: \n \n");
            fatorBalanceamento(raiz);
            printf("Calculo: \n");
            printf("[Chave] (No da esquerda) - (No da direita) = (Fator de Balanceamento) \n \n");
            imprimirCalculo(raiz);
            goto inicio;
            break;
        case 3:
            printf("- - - - - - - - - - - - - - - - - - - - - - \n");
            printf("Arvore Binaria: \n");
            imprimirArvore(raiz, 1); // Imprime a arvore binaria
            printf("\n");
            printf("- - - - - - - - - - - - - - - - - - - - - - \n");
            printf("Chaves e Fator de Balanceamento: \n");
            imprimir(raiz);
            goto inicio;
            break;
        case 4:
            printf("Desalocando Nos... \n");
            liberaNo(raiz);
            sair();
            break;
        default:
            printf("Invalido!\n");
            goto inicio;
    }
    return 0;
}
