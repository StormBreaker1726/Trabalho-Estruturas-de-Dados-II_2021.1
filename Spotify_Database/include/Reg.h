#ifndef BBE91544_FD1E_4021_8BC9_9E88DB711BF8
#define BBE91544_FD1E_4021_8BC9_9E88DB711BF8

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "const.h"
/**
 * @brief Estrutura de registro dos dados da tabela hash
 */
class Register{
    private:

        char id[23];

        int number_of_occurrences;

        char mostPopularMusicId[23];

        int mostPopularMusicPopularity;

    public:

        Register(char *id, int number_of_occurrences, char *mostPopularMusicId, int mostPopularMusicPopularity);

        ~Register();

        void setOccurrences(int newOccurrences);

        void setMostPopularMusicId(char *newmostPopularMusicId);

        void setMostPopularMusicPopularity(int newMostPopularMusicPopularity);


        char* getId();

        int getOccurrences();

        char* getMostPopularMusicId();

        int getMostPopularMusicPopularity();

        
};


#endif /* BBE91544_FD1E_4021_8BC9_9E88DB711BF8 */
