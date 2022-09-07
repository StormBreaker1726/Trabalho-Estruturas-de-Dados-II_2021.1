/**
    Universidade Federal de Juiz de Fora
    ArvoreB.h
    Propósito: Classe para implementar a arvore B
    @author Ivanylson HG

*/

#ifndef SRC_TRABALHO2_ARVOREB_H
#define SRC_TRABALHO2_ARVOREB_H

#include <iostream>
#include <cstring>
#include <string>
#include <string.h>
#include "NoB.h"
#include "Contador.h"

class ArvoreB
{
private:
    NoB *raiz; //ponteiro pra raiz
    int t;     // grau minimo

public:
    ArvoreB(int _t) //construtor arvore
    {
        raiz = NULL;
        t = _t;
    }
    // função que percorre a arvore chamando a função equivalente no Nó, começando pela raiz

    void percorre()
    {
        if (raiz != NULL)
            raiz->percorre();
    }
    // função que procura um Nó arvore chamando a função equivalente no Nó

    NoB *procura(char *nome_artista)
    {
        return (raiz == NULL) ? NULL : raiz->procura(nome_artista);
    }
    // Função que insere na arvore usando os metodos "inserenaocheio" e "dividefilho", implementadas no Nó

    void insert(char *nome_artista, char *cod_artista, int localizacao)
    {

        if (raiz == NULL)
        {

            raiz = new NoB(t, true);
            strcpy(raiz->chave[0].nome,nome_artista);
            strcpy(raiz->chave[0].cod_artista,cod_artista);
            raiz->chave[0].localizacao = localizacao;
            raiz->n = 1;
        }
        else
        {
            if (raiz->n == 2 * t - 1)
            {
                NoB *s = new NoB(t, false);

                s->C[0] = raiz;
                Contador::getInstance().registraCopia();

                s->dividefilho(0, raiz);

                int i = 0;
                if (strcmp(s->chave[0].nome, nome_artista)<1)
                {
                    Contador::getInstance().registraComparacao();
                    i++;
                }
                s->C[i]->inserenaocheio(nome_artista,cod_artista,localizacao);

                raiz = s;
            }
            else
            {
                raiz->inserenaocheio(nome_artista,cod_artista,localizacao);
            }
        }
    }

    // Função que remove um Nó passado, utiliza a função "remove" implementada no Nó.
/*
    void remove(int k)
    {
        if (!raiz)
        {
            cout << "A arvore está vazia\n";
            return;
        }

        raiz->remove(k);

        if (raiz->n == 0)
        {
            Contador::getInstance().registraComparacao();
            NoB *tmp = raiz;
            if (raiz->folha)
                raiz = NULL;
            else
            {
                raiz = raiz->C[0];
                Contador::getInstance().registraCopia();
            }
            delete tmp;
        }
        return;
    }*/
};
#endif //SRC_TRABALHO2_ARVOREB_H
