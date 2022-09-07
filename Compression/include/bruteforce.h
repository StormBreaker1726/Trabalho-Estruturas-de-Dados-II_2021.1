#ifndef BC01A45A_E814_433F_BF8B_B967FBE27C4B
#define BC01A45A_E814_433F_BF8B_B967FBE27C4B


#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/time.h>
#include "const.h"
#define MAX 1000000

using namespace std;
int countt = 0;

/* Tenta encontrar o padrão fornecido na string de pesquisa */
int bruteForce(char *search, char *pattern, int slen, int plen)
{
    int i, j, k;

    for (i = 0; i <= slen - plen; i++)
    {
        countt++;
        for (j = 0, k = i; (search[k] == pattern[j]) && (j < plen); j++, k++);
        if (j == plen)
            return k-j+1;
    }

    return -1;
}


void bruteForceMain(char *path,const char *fileName1,const char *fileName2)
{
    char *search = new char [MAX];
    char *pattern = new char [MAX];
    char *temp = new char [MAX];
    char *temp2 = new char [MAX];

    string entradaTxtPath = "";
    entradaTxtPath.append(path).append(fileName1);
    char entradaFinalTxtPath[entradaTxtPath.size()+1];
    strcpy(entradaFinalTxtPath,entradaTxtPath.c_str());
    FILE *input = fopen(entradaFinalTxtPath, "r");

    string entradaTxtPath2 = "";
    entradaTxtPath2.append(path).append("/inputBruteForce.txt");
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
    entradaTxtPath3.append(path).append("/inputBruteForce.txt");
    char entradaFinalTxtPath3[entradaTxtPath3.size()+1];
    strcpy(entradaFinalTxtPath3,entradaTxtPath3.c_str());

    FILE *input1 = fopen(entradaFinalTxtPath3,"r");

    int pos=0;
    int control=0;
    char v;

    //printf("Text in which the pattern should be searched:\n");

    string entradaTxtPath4 = "";
    entradaTxtPath4.append(path).append(fileName2);
    char entradaFinalTxtPath4[entradaTxtPath4.size()+1];
    strcpy(entradaFinalTxtPath4,entradaTxtPath4.c_str());
    FILE *input3= fopen(entradaFinalTxtPath4,"r");

    fgets(pattern, MAX, input3);
    fclose(input3);
    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);

    pattern[strlen(pattern) - 1] = '\0';

    int leng = strlen(pattern);
    int slen=0,plen=0,sum=0,i=0,g=0;
    int start=0;
    while(!feof(input1))
    {
        if(fgets (search, MAX, input1)!=NULL)
        {
            search[strlen(search) - 1] = '\0';
            slen = strlen(search);
            plen = strlen(pattern);
            while(start < slen)
            {
                pos=bruteForce(search-start,pattern,slen,plen);
                sum +=countt;

                if(pos>=0)
                {
                    printf("The desired pattern was found from %d. line at position %d \n",g+1,pos-1);
                    control++;
                    start = pos;
                }
                else
                {
                    break;
                }
            }
            if(pos!=-1)
            {
                strncpy(temp, search, pos);
                temp[pos] = '\0';

                for(i=0; i<MAX; i++)
                {
                    if((pos+leng+i)<strlen(search))
                        temp2[i] = search[pos+leng+i];
                    else
                        temp2[i] = v;
                }
            }
        }
        g++;
    }

    if(control==0)
    {
        printf("\nPattern not found in text provided \n\n");
    }

    gettimeofday(&tv2, NULL);
    printf ("Total time = %f seconds\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));

    fclose(input1);

    printf("The character comparison number: %d\n",sum);
    delete search;
    delete pattern;
    delete temp;
    delete temp2;
}

void bruteForceMainStart(char path[])
{
    for (int i = 1; i <= N; i++)
    {
        string filename1 = "/dna" + to_string(i) + ".txt";
        string filename2 = "/padrao" + to_string(i) + ".txt";
        bruteForceMain(path,filename1.c_str(),filename2.c_str());
    }
}
#endif /* BC01A45A_E814_433F_BF8B_B967FBE27C4B */
