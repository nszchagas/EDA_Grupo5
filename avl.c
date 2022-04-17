#include <stdio.h>
#include <stdlib.h>
#include "arquivos.c"
#include "estruturas.c"
/**
* Objetivo: Arvore binaria balanceada
* Entrada: Opcao escolhida pelo usuario de arquivo
* Saida: Arvore binaria e fator de balanceamento
*/
            /*

                    O QUE ESTA FALTANDO?
                    >> Calcular o fator de balanceamento na opcao 2
                    >> Imprimir fator de balanceamento na opcao 3
                    >> Desalocar os nos na opcao 4

                    IMPORTANTE:
                    Nao mudar o codigo. Se quiser acrescentar algo,
                    crie uma funcao separada em estruturas.c
                    e a partir dali mude o codigo

            */
int main(){
    // Declaracoes
    char endereco_arquivo[30]; // Ponteiro para endereço do arquivo
    FILE *arquivo_csv = NULL;
    int aux, opcao, valor;
    No *raiz = NULL;
    No *fator = NULL;
    // Instrucoes
    aux = 0, valor = 0;
    // Sinal onde goto deve retornar
    inicio:
    // Limpar a tela após retorno
    if(opcao < 1 && opcao > 5 || opcao >= 1){
        getch();
        limpar();
    }
    menu(); // Chamar menu de escolhas
    scanf("%d", &opcao);
    // Limpar a tela
    limpar();
    switch(opcao){
        /** Concluído. Nao alterar. */
        case 1:
            opcoes();
            opcao = 0;
            scanf("%d", &opcao);
            switch(opcao){
                case 1:
                    printf("Digite o endereco do arquivo a ser aberto: ");
                    scanf("%s", endereco_arquivo);
                    arquivo_csv = abrir_arquivo_leitura(endereco_arquivo);
                    goto continua;
                    break;
                case 2:
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
            // Avaliar arquivo aberto e gerar arvore
            if(arquivo_csv == NULL){
                //Não aberto
                printf("Erro! Arquivo %s nao pode ser aberto.\n", endereco_arquivo);
            }else{
                rewind(arquivo_csv);
                // Inserir todos os numeros do arquivo na arvore
                while((aux = fscanf(arquivo_csv, "%d", &valor) != EOF)){
                    raiz = inserir(raiz, valor);
                    fator = calculaFator(raiz, valor);
                    fseek(arquivo_csv, 1, SEEK_CUR);
                }
            }

            goto inicio;
            break;
        /** Não feito */
        case 2:
            /* funcao() */
            imprimir(fator, 1);
            goto inicio;
            break;
        /** Falta imprimir os fatores de balanceamento */
        case 3:
            imprimir(raiz, 1); // Imprimir a arvore binaria
            /* funcao() */
            goto inicio;
            break;
        /** A funcao liberarNo nao funciona */
        case 4:
            liberaNo(raiz);
            if (raiz == NULL){
                printf("Desalocao realizada com sucesso! \n");
            }
            sair();
            break;
        default:
            printf("Invalido!\n");
            goto inicio;
    }
    return 0;
}
