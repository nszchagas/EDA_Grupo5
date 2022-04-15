#ifndef ARQUIVOS_H_INCLUDED
#define ARQUIVOS_H_INCLUDED
#include <stdio.h>
FILE *abrir_arquivo_leitura(char *f_endereco_ptr);
FILE *abrir_arquivo_escrita(char *f_endereco_ptr);
void criar_arquivo_aleatorio();
void menu();
void sair();
void limpar();
#endif // ARQUIVOS_H_INCLUDED
