#ifndef B3C9F33D_1DA5_4146_B908_44B64CA5A423
#define B3C9F33D_1DA5_4146_B908_44B64CA5A423

#include <iostream> //biblioteca padrão
#include <vector> //std::vector
#include <algorithm> //std::find
#include <stdlib.h> //rand, srand
#include <time.h> //time
#include <stdio.h>
#include <fstream>
#include "Artist.h"
#include "Track.h"
#include "const.h"

using namespace std;

/**
 * @brief Checa se um valor numérico já está presente no vector de inteiros
 * 
 * @param array, ponteiro para uma variável de tipo vector<int>
 * @param key, valor numérico de tipo inteiro que deverá ser analisado
 * @return true, se o valor já está no vector 
 * @return false, se o valor não está no vector
 */
bool vectorCheck(vector<int> *array, int key);

/**
 * @brief Gera de maneira pseudoaleatória valores para preencher o vetor, partindo de 1 e indo até o máximo (range).
 * 
 * @param random_array, ponteiro para a variável de tipo vector<int> 
 * @param size, variável do tipo inteiro, que consiste no tamanho máximo do vector
 * @param range, variável do tipo inteiro, que consiste no maior número que pode ser gerado aleatoriamente
 */
void generateRandomIndexes(vector<int> *random_array, int size, int range);

/**
 * @brief Faz a análise da opção do usuário, e, após isso, imprime (em tela ou em arquivo de tipo texto), as informações de um registro
 * do csv de artistas.
 * 
 * @param userChoice, variável de tipo booleano que representa se o usuário quis imprimir em tela (true), ou em arquivo (false). 
 * @param path, representa o endereço do diretório onde o usuário escoheu salvar o arquivo e onde está o arquivo de tipo binário
 */
void loadArtist(bool userChoice, char *path);

/**
 * @brief Faz a análise da opção do usuário, e, após isso, imprime (em tela ou em arquivo de tipo texto), as informações de um registro
 * do csv de trilhas.
 * 
 * @param userChoice, variável de tipo booleano que representa se o usuário quis imprimir em tela (true), ou em arquivo (false). 
 * @param path, representa o endereço do diretório onde o usuário escoheu salvar o arquivo e onde está o arquivo de tipo binário
 */
void loadTrack(bool userChoice, char *path);

#endif /* B3C9F33D_1DA5_4146_B908_44B64CA5A423 */
