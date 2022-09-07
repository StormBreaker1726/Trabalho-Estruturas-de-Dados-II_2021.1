#ifndef F98D62F1_2052_4CFD_BCFE_C42DB2A9A6D3
#define F98D62F1_2052_4CFD_BCFE_C42DB2A9A6D3

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/time.h>
#define MAX 1000000

using namespace std;

// d é o número de caracteres no alfabeto de entrada
#define dChar 256
int cont = 0;

void search(char agement[], char doc[], int pNumber)
{
    int M = strlen(agement);
    int NN = strlen(doc);
    int i, j;
    int p = 0;// valor hash para o padrão
    int t = 0; // valor hash para doc
    int h = 1;

    // O valor de h seria "pow (dChar, M-1)% pNumber"
    for (i = 0; i < M - 1; i++)
    {
        h = (h * dChar) % pNumber;
        cont++;
    }
    // Calcule o valor hash do padrão e primeiro
    // janela de texto
    for (i = 0; i < M; i++)
    {
        cont++;
        p = (dChar * p + agement[i]) % pNumber;
        t = (dChar * t + doc[i]) % pNumber;
        cont++;
    }

    // Deslize o padrão sobre o texto um por um
    for (i = 0; i <= NN - M; i++)
    {
        cont++;
        // Verifique os valores de hash da janela de texto atual
        // e padrão. Se os valores de hash corresponderem, apenas
        // verifique os caracteres um por um
        if ( p == t )
        {
            /* Verifique os caracteres um por um */
            for (j = 0; j < M; j++)
            {
                if (doc[i+j] != agement[j])
                {
                    break;
                    cont++;
                }
            }

            // if p == t and agement[0...M-1] = doc[i, i+1, ...i+M-1]
            if (j == M)
                cout<<"Padrão encontrado no índice "<< i<<endl;
        }

        // Calcular o valor do hash para a próxima janela de texto: Remover
        // dígito inicial, adicionar dígito final
        if ( i < NN-M )
        {
            t = (dChar*(t - doc[i]*h) + doc[i+M])%pNumber;

            // Podemos obter o valor negativo de t, convertendo-o
            // para positivo
            if (t < 0)
                t = (t + pNumber);
        }
    }
}

/* Código do driver */
void RabinKarpMain(char path1[], char path2[])
{
    char *search2 = new char [MAX];
    char *pattern = new char [MAX];
    int pos=0;
    int control=0;
    FILE *input = fopen(path1,"r");
    FILE *fout = fopen("inputRabinKarp.txt","w");
    char c;
    while((c = fgetc(input))!=EOF)
    {
        if(c!='\n')
            fputc(c,fout);
    }
    fclose(input);
    fclose(fout);
    FILE *input1 = fopen("inputRabinKarp.txt","r");
    printf("The pattern must be searched:\n");
    FILE *input3= fopen(path2,"r");
    fgets(pattern, MAX, input3);
    fclose(input3);
    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);
    // Um ​​número primo
    int pNumber = 100000;

    pattern[strlen(pattern) - 1] = '\0';
    int leng = strlen(pattern);
    int slen=0,plen=0,sum=0,i=0,g=0;
    int start=0;
    while(!feof(input1))
    {
        if(fgets (search2, MAX, input1)!=NULL)
        {
            search(pattern, search2, pNumber);
            sum +=cont;
            control++;
        }
    }

    // Function Call
    if(control==0)
    {
        printf("\nPattern not found in text provided\n\n");
    }

    gettimeofday(&tv2, NULL);
    printf ("Total time = %f seconds\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));

    fclose(input1);

    printf("The character comparison number: %d\n",sum);

    delete search2;
    delete pattern;
}

#endif /* F98D62F1_2052_4CFD_BCFE_C42DB2A9A6D3 */
