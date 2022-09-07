#ifndef F5DF5853_EFC7_4E0E_819E_592BFBBA9A40
#define F5DF5853_EFC7_4E0E_819E_592BFBBA9A40

/* Programa C ++ para heurística de Bad Character de Boyer
Algoritmo de correspondência de strings de Moore */
#include <iostream>
#include <string>
#include <fstream>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include "const.h"
#define MAX 1000000

using namespace std;
# define NFCHARS 256

// A função de pré-processamento para Boyer Moore's
// heurística de mau caráter
void roughCharHeuristic( string doc, int proportion,
                       int roughChar[NFCHARS])
{
    int i;

    // Inicializa todas as ocorrências como -1
    for (i = 0; i < NFCHARS; i++)
        roughChar[i] = -1;

    // Preencha o valor real da última ocorrência
    // de um personagem
    for (i = 0; i < proportion; i++)
        roughChar[(int) doc[i]] = i;
}

/* Uma função de pesquisa de padrões que usa Bad
Heurística de Caráter do Algoritmo de Boyer Moore */
void inspection( string document, string arrangement)
{
    int m = arrangement.size();
    int n = document.size();

    int roughChar[NFCHARS];

    /* Preencha o array de caracteres inválidos chamando
    a função de pré-processamento roughCharHeuristic ()
    para determinado padrão */
    roughCharHeuristic(arrangement, m, roughChar);

    int changeText = 0;  // changeText é a mudança do padrão com
    // respeito ao texto
    while(changeText <= (n - m))
    {
        int j = m - 1;

        /* Continue reduzindo o índice j do padrão enquanto
            caracteres de padrão e texto são
            combinando neste turno s */
        while(j >= 0 && arrangement[j] == document[changeText + j])
            j--;

        /* Se o padrão estiver presente no atual
            shift, então o índice j se tornará -1 após
            o loop acima */
        if (j < 0)
        {
            //printf("pattern occurs on change = %d \n",changeText);

            /* Muda o padrão para que o próximo
            caractere no texto alinha-se com o último
            ocorrência dele no padrão.
            A condição changeText + m <n é necessária para
            o caso quando o padrão ocorre no final
            de texto */
            changeText += (changeText + m < n)? m-roughChar[document[changeText + m]] : 1;

        }

        else
            /* Muda o padrão para que o mau caráter
                no texto alinha-se com a última ocorrência de
                no padrão. A função max é usada para
                certifique-se de obter uma mudança positiva.
                Podemos obter uma mudança negativa se o último
                ocorrência de mau caráter no padrão
                está do lado direito da corrente
                personagem. */
            changeText += max(1, j - roughChar[document[changeText + j]]);
    }
}

void bhmMain(char *path, const char *path1,const char *path2)
{
    string text,pattern;

    string entradaTxtPath = "";
    entradaTxtPath.append(path).append(path1);
    char entradaFinalTxtPath[entradaTxtPath.size()+1];
    strcpy(entradaFinalTxtPath,entradaTxtPath.c_str());
    FILE *input = fopen(entradaFinalTxtPath,"r");

    string entradaTxtPath2 = "";
    entradaTxtPath2.append(path).append("/inputbmh.txt");
    char entradaFinalTxtPath2[entradaTxtPath2.size()+1];
    strcpy(entradaFinalTxtPath2,entradaTxtPath2.c_str());

    FILE *fout = fopen(entradaFinalTxtPath2,"w");
    char c;
    while((c = fgetc(input))!=EOF)
    {
        if(c!='\n')
            fputc(c,fout);
    }
    fclose(input);
    fclose(fout);
    string entradaTxtPath3 = "";
    entradaTxtPath3.append(path).append("/inputbmh.txt");
    ifstream filename(entradaTxtPath3);
    while(getline(filename,text,'\n'))
    {

    }
    //cout<<"entering with pattern:";

    string entradaTxtPath4 = "";
    entradaTxtPath4.append(path).append(path2);
    ifstream filename2(entradaTxtPath4);

    while(getline(filename2,pattern,'\n'))
    {

    }
    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);
    inspection(text, pattern);
    gettimeofday(&tv2, NULL);
    //printf ("Total time = %f seconds \n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));

    filename.close();
    filename2.close();


}

void bhmMainStart(char path[]) {
    for (int i = 1; i<= N; i++) {
        string filename1 = "/dna" + to_string(i) + ".txt";
        string filename2 = "/padrao" + to_string(i) + ".txt";
        bhmMain(path,filename1.c_str() ,filename2.c_str());
    }
}
#endif /* F5DF5853_EFC7_4E0E_819E_592BFBBA9A40 */
