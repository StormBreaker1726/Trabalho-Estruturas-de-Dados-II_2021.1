#ifndef C9FEF2BA_4B8B_4BFC_B374_723361B711E0
#define C9FEF2BA_4B8B_4BFC_B374_723361B711E0

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <utility> //std::pair
#include <stdexcept> //std::runtime_error
#include <sstream> //std::stringstream
#include <algorithm>

using namespace std;

/**
 * @brief Funcao que captura os dados do arquivo artists.csv e passa para um arquivo nomeado artists.bin
 * 
 * @param path, variável de tipo vetor de caracteres que recebe o endereço (caminho) onde o usuário salvou o csv e onde 
 * deseja salvar o arquivo binário
 */
void csvToBinaryArtists(char *path);

/**
 * @brief Funcao que captura os dados do arquivo racks.csv e passa para um arquivo nomeado tracks.bin
 * 
 * @param path, variável de tipo vetor de caracteres que recebe o endereço (caminho) onde o usuário salvou o csv e onde 
 * deseja salvar o arquivo binário 
 */
void csvToBinaryTracks(char *path); 


#endif /* C9FEF2BA_4B8B_4BFC_B374_723361B711E0 */
