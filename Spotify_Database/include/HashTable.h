#ifndef E9290305_9116_44CE_AD2F_E9A81EF08EA9
#define E9290305_9116_44CE_AD2F_E9A81EF08EA9
#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
#include <string>
#include "Reg.h"


using namespace std;

/**
 * @brief Cria a tabela hash
 */
class HashTable{
    private:

        int size;

        Register **table;

        unsigned int ocPositions;

        string path;

        long long getHashFinalFunction(string const& s);

        int h1(long long key);

        int h2(long long key);

        int hashFinalFunction(long long key, int cont);

        void insertInVector(int *array, int tam);

        void getRegisters(int *array, int tam, bool teste);

        void printMostFrequentArtists(int *arrayWithFrequency, 
            char* *idMostFrequentArtists, char* *idMostPopularMusic, int *mostPopularMusicPopularity, vector<string> namesMostFrequentArtists, int tam, bool teste);

        void getNamesFromBinary(vector<string> *namesMostFrequentArtists, char* *idMostFrequentArtists, int tam);
    public:

        HashTable(int size, char* path);

        ~HashTable();

        int insert(char *idArtist, int occurrences, char *musicId, int musicPopularity);

        int find(char *idArtist, char *musicId, int musicPopularity);

        void printHashTable();

        int occupPositions();

        void getMostFrequentArtists(int m, bool teste);
};




#endif /* E9290305_9116_44CE_AD2F_E9A81EF08EA9 */
