/**
    Universidade Federal de Juiz de Fora
    NoB.h
    Propósito: Classe para implementar o NoB usando inteiros como chave
    @author Ivanylson HG

*/


#ifndef SRC_TRABALHO2_NoB_H
#define SRC_TRABALHO2_NoB_H

#include <iostream>
#include <cstring>
#include <string>
#include <string.h>
#include "Contador.h"

typedef struct
{
    char cod_artista[23];
    char nome[23];
    int localizacao;
} Dados_chaves;

class NoB
{
private:
    //int *chave; // ponteiro que aponta pra um vetor com as chaves
    int t;      // grau minimo
    NoB **C;    // ponteiro que aponta pra um vetor de ponteiros com os filhos
    int n;      // Numero de nos atuais
    bool folha; // booleano é folha
    Dados_chaves *chave; // ponteiro que aponta pra um vetor com as chaves

public:
    NoB(int t1, bool folha1) // construtor do Nó que recebe a ordem e se é folha
    {
        t = t1;

        folha = folha1;

        //chave = new int[2 * t - 1];
        chave = new Dados_chaves[2 * t - 1];

        C = new NoB *[2 * t];

        n = 0;
        /*
                for (int i = 0; i < 2*t-1; i++)
                {
                    this->chave[i] = NULL;
                }
                */
    }
    // Função que procura um  Nó, ela é um ponteiro e percorre a arvore usando a estrategia binaria
    NoB *procura(char *nome_artista)
    {
        int i = 0;
        while (i < n && strcmp(chave[i].nome,nome_artista)<0)
            i++;

        if (i < n && strcmp(chave[i].nome,nome_artista)==0)
            return this;

        if (folha == true)
            return NULL;

        return C[i]->procura(nome_artista);
    }
    // Função que procura uma chave especifica em um Nó, por meio do percorrimento da arvore
    void achachaveMostrar(char *nome_artista)
    {
        int idx = 0;
        while (idx < n && strcmp(chave[idx].nome,nome_artista)<0)
            idx++;

        if (idx < n && strcmp(chave[idx].nome,nome_artista)==0)
        {
            cout <<"Posição: "<< idx << endl;
            cout <<"\n"<<"Nome: " << chave[idx].nome<<"\n Cod: " << chave[idx].cod_artista<<"\n Chave: " << chave[idx].localizacao<<"\n";
        }
        //return idx;
    }
    int achachave(char *nome_artista)
    {
        int idx = 0;
        while (idx < n && strcmp(chave[idx].nome,nome_artista)<0)
            idx++;

        if (idx < n && strcmp(chave[idx].nome,nome_artista)==0)
            return chave[idx].localizacao;
    }
    // Insere num vetor que tem espaço sobrando, onde ele simplismente precisa achar a posição necessaria e inserir

    void inserenaocheio(char *nome_artista, char *cod_artista, int localizacao)
    {
        int i = n - 1;
        if (folha == true)
        {

            while (i >= 0 && strcmp(chave[i].nome,nome_artista)>0)
            {
                Contador::getInstance().registraComparacao();
                strcpy(chave[i + 1].nome,chave[i].nome);
                strcpy(chave[i + 1].cod_artista,chave[i].cod_artista);
                chave[i + 1].localizacao = chave[i].localizacao;

                Contador::getInstance().registraCopia();
                i--;
            }

            strcpy(chave[i + 1].nome,nome_artista);
            strcpy(chave[i + 1].cod_artista,cod_artista);
            chave[i + 1].localizacao = localizacao;

            Contador::getInstance().registraCopia();
            n = n + 1;
        }
        else
        {

            while (i >= 0 && strcmp(chave[i].nome,nome_artista)>0)
            {
                i--;
                Contador::getInstance().registraComparacao();
            }

            if (C[i + 1]->n == 2 * t - 1)
            {
                Contador::getInstance().registraComparacao();
                dividefilho(i + 1, C[i + 1]);

                if (strcmp(chave[i].nome,nome_artista)<0)
                {
                    i++;
                    Contador::getInstance().registraComparacao();
                }
            }
            C[i + 1]->inserenaocheio(nome_artista,cod_artista,localizacao);
        }
    }

    // Dá o split do filho pra inserção de um novo valor, a função dá um split classico onde ele divide o filho em dois, encaixa o valor requerido e depois retorna os dois vetores e qual numero irá "subir"
    void dividefilho(int i, NoB *y)
    {

        NoB *z = new NoB(y->t, y->folha);
        z->n = t - 1;

        for (int j = 0; j < t - 1; j++)
        {
            strcpy(z->chave[j].nome, y->chave[j + t].nome);
            strcpy(z->chave[j].cod_artista,y->chave[j + t].cod_artista);
            z->chave[j].localizacao = y->chave[j + t].localizacao;

            Contador::getInstance().registraCopia();
        }

        if (y->folha == false)
        {
            for (int j = 0; j < t; j++)
                z->C[j] = y->C[j + t];
        }

        y->n = t - 1;

        for (int j = n; j >= i + 1; j--)
        {
            Contador::getInstance().registraComparacao();
            C[j + 1] = C[j];
            Contador::getInstance().registraCopia();
        }

        C[i + 1] = z;
        Contador::getInstance().registraCopia();

        for (int j = n - 1; j >= i; j--)
        {
            Contador::getInstance().registraComparacao();
            strcpy(chave[j + 1].nome,chave[j].nome);
            strcpy(chave[j + 1].cod_artista,chave[j].cod_artista);
            chave[j + 1].localizacao = chave[j].localizacao;
            Contador::getInstance().registraCopia();
        }

        strcpy(chave[i].nome,y->chave[t - 1].nome);
        strcpy(chave[i].cod_artista,y->chave[t - 1].cod_artista);
        chave[i].localizacao = y->chave[t - 1].localizacao;
        Contador::getInstance().registraCopia();

        n = n + 1;
    }
    /*
    // Remove um Nó especificado, usando as duas funções auxiliares "removefolha" e "removenaofolha" permitindo que ele remova da forma mais eficiente possivel

    void remove(int k)
    {

        int idx = achachave(k);

        if (idx < n && chave[idx] == k)
        {
            Contador::getInstance().registraComparacao();

            if (folha)
                removefolha(idx);
            else
                removenaofolha(idx);
        }
        else
        {

            if (folha)
            {
                cout << "A chave " << k << " não existe na arvore\n";
                return;
            }

            bool flag = ((idx == n) ? true : false);

            if (C[idx]->n < t)
                preenche(idx);

            if (flag && idx > n)
                C[idx - 1]->remove(k);
            else
                C[idx]->remove(k);
        }
        return;
    }
    // Função chamada pela remove que faz uma remoção caso o Nó seja uma folha
    void removefolha(int idx)
    {

        for (int i = idx + 1; i < n; ++i)
        {
            chave[i - 1] = chave[i];
            Contador::getInstance().registraComparacao();
        }

        n--;

        return;
    }
    // Função chamada pela remove que faz uma remoção caso o Nó não seja uma folha, resolvendo as trocas de ponteiros e verificando se não são criadas chaves com tamanhos menores que a ordem

    void removenaofolha(int idx)
    {

        int k = chave[idx];

        if (C[idx]->n >= t)
        {
            Contador::getInstance().registraComparacao();
            int pred = getPred(idx);
            chave[idx] = pred;
            C[idx]->remove(pred);
        }

        else if (C[idx + 1]->n >= t)
        {
            Contador::getInstance().registraComparacao();
            int succ = getSucc(idx);
            chave[idx] = succ;
            C[idx + 1]->remove(succ);
        }

        else
        {
            juntar(idx);
            C[idx]->remove(k);
        }
        return;
    }

    int getPred(int idx) // Pega o predecessor
    {

        NoB *cur = C[idx];
        Contador::getInstance().registraCopia();
        while (!cur->folha)
            cur = cur->C[cur->n];

        return cur->chave[cur->n - 1];
    }

    int getSucc(int idx) // Pega o sucessor
    {
        NoB *cur = C[idx + 1];
        Contador::getInstance().registraCopia();
        while (!cur->folha)
            cur = cur->C[0];

        return cur->chave[0];
    }

    void preenche(int idx) // Função que preenche a arvore
    {

        if (idx != 0 && C[idx - 1]->n >= t)
        {
            Contador::getInstance().registraComparacao();
            emprestaant(idx);
        }
        else if (idx != n && C[idx + 1]->n >= t)
        {
            emprestaprox(idx);
            Contador::getInstance().registraComparacao();
        }
        else
        {
            Contador::getInstance().registraComparacao();
            if (idx != n)
            {
                juntar(idx);
            }
            else
                juntar(idx - 1);
        }
        return;
    }

    void emprestaant(int idx) //empresta o Nó anterior
    {

        NoB *filho = C[idx];
        NoB *irmao = C[idx - 1];
        Contador::getInstance().registraCopia();
        Contador::getInstance().registraCopia();

        for (int i = filho->n - 1; i >= 0; --i)
        {
            filho->chave[i + 1] = filho->chave[i];
            Contador::getInstance().registraCopia();
            Contador::getInstance().registraComparacao();
        }

        if (!filho->folha)
        {
            for (int i = filho->n; i >= 0; --i)
                filho->C[i + 1] = filho->C[i];
        }

        filho->chave[0] = chave[idx - 1];
        Contador::getInstance().registraCopia();

        if (!filho->folha)
            filho->C[0] = irmao->C[irmao->n];

        chave[idx - 1] = irmao->chave[irmao->n - 1];
        Contador::getInstance().registraCopia();

        filho->n += 1;
        irmao->n -= 1;

        return;
    }

    void emprestaprox(int idx) //empresta o Nó seguinte

    {

        NoB *filho = C[idx];
        NoB *irmao = C[idx + 1];
        Contador::getInstance().registraCopia();
        Contador::getInstance().registraCopia();

        filho->chave[(filho->n)] = chave[idx];
        Contador::getInstance().registraCopia();

        if (!(filho->folha))
            filho->C[(filho->n) + 1] = irmao->C[0];

        chave[idx] = irmao->chave[0];
        Contador::getInstance().registraCopia();

        for (int i = 1; i < irmao->n; ++i)
        {
            irmao->chave[i - 1] = irmao->chave[i];
            Contador::getInstance().registraCopia();
            Contador::getInstance().registraComparacao();
        }
        if (!irmao->folha)
        {
            for (int i = 1; i <= irmao->n; ++i)
                irmao->C[i - 1] = irmao->C[i];
        }

        filho->n += 1;
        irmao->n -= 1;

        return;
    }

    void juntar(int idx) //Função que dá o "merge" entre dois Nós
    {
        NoB *filho = C[idx];
        NoB *irmao = C[idx + 1];
        Contador::getInstance().registraCopia();
        Contador::getInstance().registraCopia();

        filho->chave[t - 1] = chave[idx];
        Contador::getInstance().registraCopia();

        for (int i = 0; i < irmao->n; ++i)
        {
            filho->chave[i + t] = irmao->chave[i];
            Contador::getInstance().registraCopia();
        }

        if (!filho->folha)
        {
            for (int i = 0; i <= irmao->n; ++i)
                filho->C[i + t] = irmao->C[i];
        }

        for (int i = idx + 1; i < n; ++i)
        {
            chave[i - 1] = chave[i];
            Contador::getInstance().registraCopia();
        }

        for (int i = idx + 2; i <= n; ++i)
        {
            C[i - 1] = C[i];
            Contador::getInstance().registraCopia();
        }
        filho->n += irmao->n + 1;
        n--;

        delete (irmao);
        return;
    }
    */
    void percorre() // função que percorre a arvore
    {

        int i;
        for (i = 0; i < n; i++)
        {

            if (folha == false)
                C[i]->percorre();
            cout <<"\n"<<"Nome: " << chave[i].nome<<"\n Cod: " << chave[i].cod_artista<<"\n Chave: " << chave[i].localizacao<<"\n";
        }

        if (folha == false)
            C[i]->percorre();
    }

    friend class ArvoreB; //Marcando a arvore que usa esses nós como "amiga" para permiti-la usar os seus privados
};

#endif //SRC_TRABALHO2_NoB_H
