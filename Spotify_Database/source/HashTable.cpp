#include "HashTable.h"
#include <iostream>
#include <bits/stdc++.h>
#include <cmath>
#include <string>
#include "Reg.h"
#include "SortingAlgorithm.h"
#include "const.h"
#include "Artist.h"
#include "Track.h"


HashTable::HashTable(int size, char* path){
    this->ocPositions = 0;
    this->size = size;
    this->table = new Register* [size];
    for (int i = 0; i < size; i++)
    {
        this->table[i] = nullptr;
    }
    this->path.assign(path);
}

HashTable::~HashTable(){
    for (int i = 0; i < size; i++)
    {
        if(this->table[i] != nullptr){
            delete table[i];
        }
    }
    delete [](this->table);
}

int HashTable::h1(long long key){
    const double A = (sqrt(5)-1)/2;

    float fractionPart = (key*A) - ((int)(key*A));

    return ((int)(floor(this->size*fractionPart)));
}

int HashTable::h2(long long key){
    int size2 = size - 2;

    const double A = (sqrt(5)-1)/2;

    float fractionPart = (key*A) - ((int)(key*A));

    return ((int)(floor(size2*fractionPart)));
}

int HashTable::hashFinalFunction(long long key, int cont){
    int h1Result = h1(key);

    int h2Result = h2(key);

    return ((h1Result + cont*h2Result)%size);
}

int HashTable::insert(char *idArtist, int occurrences, char *musicId, int musicPopularity){
    long long key = getHashFinalFunction(idArtist);

    int cont = 0;
    int pos = hashFinalFunction(key, cont);
    while (table[pos] != nullptr && cont < size)
    {

        cont++;
        pos = hashFinalFunction(key, cont);
    }
    if(cont == size){
        return -1;
    }
    table[pos] = new Register(idArtist, occurrences, musicId, musicPopularity);
    ocPositions++;

    return pos;
}

void HashTable::printHashTable(){
    int h;
    for (int i = 0; i < size; i++)
    {
        h = i;
        cout<<h;

        if(table[h] != nullptr){
            Register *v = table[h];

            cout<<"\tID: "<<v->getId()
                <<"\tOccurrences: "<< v->getOccurrences()
                <<"\tMost Popular Music: "<<v->getMostPopularMusicId()
                <<"\tMost Popular Music Popularity: "<<v->getMostPopularMusicPopularity()<<endl<<endl;
        }
        else{
            cout<<"\tNULL"<<endl<<endl;
        }
    }
}

int HashTable::find(char *idArtist, char *musicId, int musicPopularity){
    long long key = getHashFinalFunction(idArtist);

    int cont = 0;
    int pos = hashFinalFunction(key, cont);

    while (table[pos] != nullptr && cont < size)
    {   
        Register *v = table[pos];
        if(strcmp(v->getId(), idArtist) == 0){
            v->setOccurrences(v->getOccurrences() + 1);
            if(v->getMostPopularMusicPopularity() < musicPopularity){
                v->setMostPopularMusicPopularity(musicPopularity);
                v->setMostPopularMusicId(musicId);
            }
            return pos;
        }
        cont++;
        pos = hashFinalFunction(key, cont);
    }
    return -1;
}

long long HashTable::getHashFinalFunction(string const& s){

    const int p = 52;
    const int m = 1e9 + 9;

    long long hash_value = 0;

    long long p_pow = 1;

    for(char c:s){
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    return abs(hash_value);
}


int HashTable::occupPositions(){
    return ocPositions;
}


void HashTable::insertInVector(int *array, int tam) {
    int h, j = 0;

    for (int i = 0; i < size; i++)
    {
        h = i;

        if(table[h] != nullptr){
            Register *v = table[h];
            array[j] = v->getOccurrences();
            j++;
        }
    }

    timSort(array, tam);
}


void HashTable::getMostFrequentArtists(int m, bool teste){
    int tam = occupPositions();
    int array[tam];

    int sortedArray[m];

    insertInVector(array, tam);

    int j = 0;
    for (int i = tam-1; i > 0; i--)
    {
        if(j == m){
            break;
        }
        sortedArray[j] = array[i];
        j++;
    }

    getRegisters(sortedArray, m, teste);
}

/********************************************************************************/

void HashTable::getRegisters(int *array, int tam, bool teste){

    char *idMostFrequentArtists[tam];
    char *idMostPopularMusic[tam];
    int mostPopularMusicPopularity[tam];
    vector<string> namesMostFrequentArtists;

    for (int i = 0; i < tam; i++){//Ele percorre o vetor com as ocorrencias dos m artistas mais frequentes e acha seus Registers
        int h;
        for (int j = 0; j < size; j++)
        {
            h = j;

            if(table[h] != nullptr){
                Register *v = table[h];
                if(v->getOccurrences() == array[i]){
                    idMostFrequentArtists[i] = v->getId();
                    idMostPopularMusic[i] = v->getMostPopularMusicId();
                    mostPopularMusicPopularity[i] = v->getMostPopularMusicPopularity();
                    table[h] = nullptr;
                    break;
                }
            }
        }
    }
    cout<<"Getting most frequent artists names..."<<endl;
    getNamesFromBinary(&namesMostFrequentArtists, idMostFrequentArtists, tam);

    printMostFrequentArtists(array, idMostFrequentArtists, idMostPopularMusic, mostPopularMusicPopularity, namesMostFrequentArtists, tam, teste);
}


void HashTable::printMostFrequentArtists(int *arrayWithFrequency, char* *idMostFrequentArtists, char* *idMostPopularMusic, 
int *mostPopularMusicPopularity, vector<string> namesMostFrequentArtists, int tam, bool teste){
    if (teste)
    {
        cout<<"Printing to file teste.txt"<<endl;
        // ...
        string testeTxtPath;
        testeTxtPath.append(this->path).append("/teste.txt");

        fstream testeTxtFile;
        testeTxtFile.open(testeTxtPath, ios::out|ios::app);

        testeTxtFile<<"\n\n";

        testeTxtFile<<"***************************************************************************"<<endl;
        testeTxtFile<<"Top "<<tam<<" of most frequent artists"<<endl;
        testeTxtFile<<endl;
        testeTxtFile<<"***************************************************************************"<<endl;

        for (int i = 0; i < tam; i++){
            testeTxtFile<<"***************************************************************************"<<endl;
            testeTxtFile<<"Position "<<i+1<<":"<<endl;
            testeTxtFile<<"Artist Id:  "<<idMostFrequentArtists[i]<<endl;
            testeTxtFile<<"Artist Name: "<<namesMostFrequentArtists[i]<<endl;
            testeTxtFile<<"Number of occurrences: "<<arrayWithFrequency[i]<<endl;
            testeTxtFile<<"Most Popular Music Id:  "<<idMostPopularMusic[i]<<endl;
            testeTxtFile<<"Most Popular Music - Popularity:  "<<mostPopularMusicPopularity[i]<<endl;
            testeTxtFile<<endl;
            testeTxtFile<<"***************************************************************************"<<endl;
        }

        testeTxtFile.close();
    }
    else
    {
        cout<<"\n\n";

        cout<<"***************************************************************************"<<endl;
        cout<<"Top "<<tam<<" of most frequent artists"<<endl;
        cout<<endl;
        cout<<"***************************************************************************"<<endl;

        for (int i = 0; i < tam; i++){
            cout<<"***************************************************************************"<<endl;
            cout<<"Position "<<i+1<<":"<<endl;
            cout<<"Artist Id:  "<<idMostFrequentArtists[i]<<endl;
            cout<<"Artist Name: "<<namesMostFrequentArtists[i]<<endl;
            cout<<"Number of occurrences: "<<arrayWithFrequency[i]<<endl;
            cout<<"Most Popular Music Id:  "<<idMostPopularMusic[i]<<endl;
            cout<<"Most Popular Music - Popularity:  "<<mostPopularMusicPopularity[i]<<endl;
            cout<<endl;
            cout<<"***************************************************************************"<<endl;
        }
    }
}


void HashTable::getNamesFromBinary(vector<string> *namesMostFrequentArtists, char** idMostFrequentArtists, int tam) {

    string artistBinPath;
    artistBinPath.append(this->path).append("/artists.bin");

    fstream binaryFile;
    binaryFile.open(artistBinPath, ios::in|ios::binary);
    
    int size = tam;
    int index;

    char id[ARTIST_ID_SIZE];
    float followers;
    char genre[ARTIST_GENRE_SIZE];
    char name[ARTIST_NAME];

    std::vector<string>::iterator it;

    it = namesMostFrequentArtists->begin();

    int s_file = Artist::size();
    int l = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < ARTIST_TOTAL_ROWS; j++) {
            binaryFile.seekg(j*s_file, ios::beg);
            binaryFile.read((char*)id, sizeof(id));
            binaryFile.read((char*)&followers, sizeof(followers));
            binaryFile.read((char*)genre, sizeof(genre));
            binaryFile.read((char*)name, sizeof(name));

            if (strcmp(idMostFrequentArtists[i], id) == 0) {
                namesMostFrequentArtists->insert(it, name);
                l++;

                it = namesMostFrequentArtists->begin()+l;
                
                break;
            }
        }
        if (namesMostFrequentArtists->size() != i + 1) {
            strcpy(name, "NOT IN FILE");
            namesMostFrequentArtists->insert(it, name);
            l++;

            it = namesMostFrequentArtists->begin()+l;
        }
    }
    binaryFile.close();  

}
