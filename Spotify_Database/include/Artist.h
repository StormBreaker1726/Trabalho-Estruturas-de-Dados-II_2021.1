#ifndef DBCBE8CF_4DDC_4C09_8FE8_5D2EC2CEE13A
#define DBCBE8CF_4DDC_4C09_8FE8_5D2EC2CEE13A

#include <iostream>
#include <string>

#include "const.h"
#include <fstream>

using namespace std;

class Artist {
    private:
        char id[ARTIST_ID_SIZE];
        float followers;
        char genre[ARTIST_GENRE_SIZE];
        char name[ARTIST_NAME];
        int popularity;

    public:
        /**
         * @brief Constrói um objeto do tipo Artist recebendo os parâmetros que são inicializados com
         * o valor das colunas do csv
         * @param id, parâmetro de tipo vetor de caracteres
         * @param followers, variável do tipo float
         * @param genre, parâmetro de tipo vetor de caracteres
         * @param name, parâmetro de tipo vetor de caracteres
         * @param popularity, variável do tipo inteiro
         */
        Artist(char* id, float followers, char* genre, char* name, int popularity);

        /**
         * @brief Destrói o objeto de tipo Artist; NÃO PRECISA SER CHAMADO!
         * 
         */
        ~Artist();

        /**
         * @brief Imprime, na tela, as informações do objeto de tipo Artist que chamou a chamou
         * 
         */
        void printArtist();

        /**
         * @brief Imprime, em um arquivo de texto, as informações do objeto de tipo Artist que a chamou
         * 
         * @param OUT_FILE, endereço de memória para um arquivo de saída de tipo texto
         */
        void textSave(fstream &OUT_FILE);

        /**
         * @brief Calcula, através dos tamanhos máximos contidos no arquivo const.h, o tamanho de um registro
         * no arquivo (no caso do csv, uma linha)
         * 
         * @return o tamanho do registro (no caso do csv, uma linha)
         */

        /**
         * @brief Get the Followers object
         * 
         * @return float 
         */
        float getFollowers();

        static int size(); 
};

#endif /* DBCBE8CF_4DDC_4C09_8FE8_5D2EC2CEE13A */
