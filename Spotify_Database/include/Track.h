#ifndef C0A4E5D4_463B_41BC_8C19_A1A6EC2BAF03
#define C0A4E5D4_463B_41BC_8C19_A1A6EC2BAF03

#include "const.h"
#include <fstream>

using namespace std;

class Track{

    private:
        char id[TRACK_ID];
        char name[TRACK_NAME];
        char artist[TRACK_ARTISTS_NAME];
        char id_artist[TRACK_ARTIST_ID];
        char release_date[TRACK_DATE];
        int isExp;
        int popularity;
        int duration;
        int key;
        int mode;
        int time_signature;
        float speechiness;
        float acousticness;
        float instrumentalness;
        float liveness;
        float valence;
        float tempo;
        float loudness;
        float danceability;
        float energy;

    public:
        /**
         * @brief Constrói um objeto do tipo Track recebendo os parâmetros que são inicializados com
         * o valor das colunas do csv
         * 
         * @param id, variável do tipo vetor de caracteres
         * @param name, variável do tipo vetor de caracteres 
         * @param artist, variável do tipo vetor de caracteres 
         * @param id_artist, variável do tipo vetor de caracteres 
         * @param release_date, variável do tipo vetor de caracteres 
         * @param isExp, variável do tipo inteiro 
         * @param popularity, variável do tipo inteiro
         * @param duration, variável do tipo inteiro
         * @param danceability, variável do tipo ponto flutuante
         * @param energy, variável do tipo ponto flutuante
         * @param key, variável do tipo inteiro 
         * @param loudness, variável do tipo ponto flutuante
         * @param mode, variável do tipo inteiro
         * @param speechiness, variável do tipo ponto flutuante
         * @param acousticness, variável do tipo ponto flutuante
         * @param instrumentalness, variável do tipo ponto flutuante
         * @param liveness, variável do tipo ponto flutuante
         * @param valence, variável do tipo ponto flutuante
         * @param tempo, variável do tipo ponto flutuante
         * @param time_signature, variável do tipo inteiro
         */
        Track(char *id, char *name, char *artist, char *id_artist, char *release_date, int isExp, int popularity, int duration, float danceability, float energy, 
        int key, float loudness, int mode, float speechiness, float acousticness, float instrumentalness, float liveness, float valence, float tempo,
        int time_signature);

        /**
         * @brief Destrói o objeto de tipo Track. NÃO PRECISA SER CHAMADO!!!
         * 
         */
        ~Track();

        /**
         * @brief Imprime, na tela, as informações do objeto de tipo Track que chamou a chamou
         * 
         */
        void printTrack();

        /**
         * @brief Imprime, em um arquivo de texto, as informações do objeto de tipo Track que a chamou
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
        static int size();

};
//Fim do Track.h
#endif /* C0A4E5D4_463B_41BC_8C19_A1A6EC2BAF03 */
