#ifndef C1F7F76E_7BCF_4CDF_A38C_04F430DD623A
#define C1F7F76E_7BCF_4CDF_A38C_04F430DD623A

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

int *pre_kmp(string arrangement)
{
    int proportion = arrangement.size();
    int *auxP = new int [proportion];
    auxP[0] = 0;
    int indiceK=0;
    for(int i=1; i<proportion; i++)
    {
        while(indiceK>0 && arrangement[indiceK] != arrangement[i] )
        {
            indiceK=auxP[indiceK-1];
        }
        if( arrangement[indiceK] == arrangement[i] )
        {
            indiceK=indiceK+1;
        }
        auxP[i]=indiceK;
    }

    return auxP;
}

void kmp(string text,string arrangement)
{
    int* auxP=pre_kmp(arrangement);
    int alike_pos=0;
    for(int ongoing=0; ongoing< text.length(); ongoing++)
    {
        while (alike_pos > 0 && arrangement[alike_pos] != text[ongoing] )
            alike_pos = auxP[alike_pos-1];

        if(arrangement[alike_pos] == text[ongoing])
            alike_pos = alike_pos+1;

        if( alike_pos == (arrangement.length()) )
        {
            //printf("The pattern occurs with change %ld \n",ongoing - (arrangement.length() -1 ));
            alike_pos = auxP[alike_pos-1];
        }
    }
}


void  KmpMain(char *path,const char *path1, const char *path2)
{
    string text,arrangement;

    string entradaTxtPath = "";
    entradaTxtPath.append(path).append(path1);
    char entradaFinalTxtPath[entradaTxtPath.size()+1];
    strcpy(entradaFinalTxtPath,entradaTxtPath.c_str());

    FILE *input = fopen(entradaFinalTxtPath,"r");
    string entradaTxtPath2 = "";
    entradaTxtPath2.append(path).append("/inputkmp.txt");
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
    entradaTxtPath3.append(path).append("/inputkmp.txt");
    ifstream filename01(entradaTxtPath3);
    while(getline(filename01,text,'\n'))
    {

    }
    //cout<<"enter pattern:";
    string entradaTxtPath4 = "";
    entradaTxtPath4.append(path).append(path2);
    ifstream filename02(entradaTxtPath4);
    while(getline(filename02,arrangement,'\n'))
    {

    }
    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);

    kmp(text,arrangement);
    gettimeofday(&tv2, NULL);
    //printf ("Total time = %f seconds \n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));

    filename01.close();
    filename02.close();
    //text = NULL;
}

void KmpMainStart(char path[])
{
    for (int i = 1; i<= N; i++) {
        string filename1 = "/dna" + to_string(i) + ".txt";
        string filename2 = "/padrao" + to_string(i) + ".txt";
        KmpMain(path,filename1.c_str(),filename2.c_str());
    }
}
#endif /* C1F7F76E_7BCF_4CDF_A38C_04F430DD623A */
