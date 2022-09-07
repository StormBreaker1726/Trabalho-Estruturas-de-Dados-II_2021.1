/**
    Universidade Federal de Juiz de Fora
    BTreeAnalysis.h
    Propósito: Arquivo que implementar o BTreeAnalysis usando para fazer as analises na ArvoreB
    @author Ivanylson HG

*/
#ifndef SRC_TRABALHO2_ARVOREB_H
#define SRC_TRABALHO2_ARVOREB_H

#include <iostream> //biblioteca padrão
#include <cmath>
#include <vector> //std::vector
#include <algorithm> //std::find
#include <stdlib.h> //rand, srand
#include <time.h> //time
#include <stdio.h>
#include <fstream>
#include <string>
#include "Artist.h"
#include "const.h"
#include "getBinaryData.h"
#include "ArvoreB.h"
#include "NoB.h"
using namespace std;


void subMenu(char *path);
void analiseBTree(int tam, int ordem,char *path);
void buscarDados(int ordem,char *path);
void setOpsB(int n,char *path);

#endif //SRC_TRABALHO2_ARVOREB_H
