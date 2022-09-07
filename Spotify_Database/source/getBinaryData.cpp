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
#include "getBinaryData.h"

using namespace std;

bool vectorCheck(vector<int> *array, int key){
    if(std::find(array->begin(), array->end(), key) != array->end()){
        return true;
    }
    else{
        return false;
    }
}

void generateRandomIndexes(vector<int> *random_array, int size, int range){

    srand(time(NULL));//inicializando a srand
    
    int value;//declaracao da viariavel auxiliar

    //Limpando a variavel de tipo vector, para garantir que nao ocorrerao erros
    random_array->clear();

    //Resize da variavel de tipo vector para economizar espaco na memoria

    for (int i = 0; i < size; i++)
    {
        value = rand() % range;
        
        while (vectorCheck(random_array, value))
        {
            value = rand() % range + 1;        
        }
        
        random_array->push_back(value);
    }
}

void loadArtist(bool userChoice, char *path){

    cout<<"Generating the artists output..."<<endl;

    string artistBinPath;
    artistBinPath.append(path).append("/artists.bin");

    fstream binaryFile;
    binaryFile.open(artistBinPath, ios::in|ios::binary);
    fstream textFile;
    
    int size;
    int index;

    char id[ARTIST_ID_SIZE];
    float followers;
    char genre[ARTIST_GENRE_SIZE];
    char name[ARTIST_NAME];
    int popularity;

    if(userChoice){
        size = 10;
    }
    else{
        size = 100;
        string artistTxtPath;
        artistTxtPath.append(path).append("/artists.txt");
        textFile.open(artistTxtPath, ios::in| ios::out|ios::app);
    }

    int s_file = Artist::size(); 

    vector<int> randomIndexes;
    generateRandomIndexes(&randomIndexes, size, ARTIST_TOTAL_ROWS);

    if(userChoice){
        for (int i = 0; i < size; i++)
        {
            index = randomIndexes[i];
            binaryFile.seekg((index-1)*s_file, ios::beg);
            binaryFile.read((char*)id, sizeof(id));
            binaryFile.read((char*)&followers, sizeof(followers));
            binaryFile.read((char*)genre, sizeof(genre));
            binaryFile.read((char*)name, sizeof(name));
            binaryFile.read((char*)&popularity, sizeof(popularity));
            
            Artist a(id, followers, genre, name, popularity);

            a.printArtist();
        }
    }
    else if(userChoice == false){
        for (int i = 0; i < size; i++)
        {
            index = randomIndexes[i];
            binaryFile.seekg((index-1)*s_file, ios::beg);
            binaryFile.read((char*)id, sizeof(id));
            binaryFile.read((char*)&followers, sizeof(followers));
            binaryFile.read((char*)genre, sizeof(genre));
            binaryFile.read((char*)name, sizeof(name));
            binaryFile.read((char*)&popularity, sizeof(popularity));
            
            Artist a(id, followers, genre, name, popularity);

            a.textSave(textFile);
        }
    }

    binaryFile.close();
    if(textFile.is_open()){
        textFile.close();
        cout<<"Artists output generated successfully."<<endl;
    }

    
}


void loadTrack(bool userChoice, char *path){

    cout<<"Generating the tracks output..."<<endl;

    string trackBinPath;
    trackBinPath.append(path).append("/tracks.bin");

    fstream textFile;
    fstream binaryFile;
    binaryFile.open(trackBinPath, ios::in|ios::binary);//OK

    int size, index;

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

    if(userChoice){ //OK
        size = 10;
    }
    else{
        size = 100;
        string trackTxtPath;
        trackTxtPath.append(path).append("/tracks.txt");
        textFile.open(trackTxtPath, ios::in| ios::out|ios::app);
    }

    

    int s_file = Track::size();//OK

    vector<int> randomIndexes;//OK
    generateRandomIndexes(&randomIndexes, size, TRACK_TOTAL_ROWS);//OK

    

    if(userChoice){
        for(int i = 0; i < size; i++){
            index = randomIndexes[i];
            binaryFile.seekg((index-1)*s_file, ios::beg);
            
            binaryFile.read(/*(char*)*/id, sizeof(id));
            binaryFile.read((char*)name, sizeof(name));
            binaryFile.read((char*)&popularity, sizeof(popularity));
            binaryFile.read((char*)&duration, sizeof(duration));
            binaryFile.read((char*)&isExp, sizeof(isExp));
            binaryFile.read((char*)artist, sizeof(artist));
            binaryFile.read((char*)id_artist, sizeof(id_artist));
            binaryFile.read((char*)release_date, sizeof(release_date));
            binaryFile.read((char*)&danceability, sizeof(danceability));
            binaryFile.read((char*)&energy, sizeof(energy));
            binaryFile.read((char*)&key, sizeof(key));
            binaryFile.read((char*)&loudness, sizeof(loudness));
            binaryFile.read((char*)&mode, sizeof(mode));
            binaryFile.read((char*)&speechiness, sizeof(speechiness));
            binaryFile.read((char*)&acousticness, sizeof(acousticness));
            binaryFile.read((char*)&instrumentalness, sizeof(instrumentalness));
            binaryFile.read((char*)&liveness, sizeof(liveness));
            binaryFile.read((char*)&valence, sizeof(valence));
            binaryFile.read((char*)&tempo, sizeof(tempo));
            binaryFile.read((char*)&time_signature, sizeof(time_signature));

            Track t(id, name, artist, id_artist, release_date, isExp, popularity, duration, danceability, energy, key, loudness, mode, speechiness, acousticness, 
            instrumentalness, liveness, valence, tempo, time_signature);

            t.printTrack();
        }
    }
    else if(userChoice == false){
        for(int i = 0; i < size; i++){
            index = randomIndexes[i];
            binaryFile.seekg((index-1)*s_file, ios::beg);
            
            binaryFile.read((char*)id, sizeof(id));
            binaryFile.read((char*)name, sizeof(name));
            binaryFile.read((char*)&popularity, sizeof(popularity));
            binaryFile.read((char*)&duration, sizeof(duration));
            binaryFile.read((char*)&isExp, sizeof(isExp));
            binaryFile.read((char*)artist, sizeof(artist));
            binaryFile.read((char*)id_artist, sizeof(id_artist));
            binaryFile.read((char*)release_date, sizeof(release_date));
            binaryFile.read((char*)&danceability, sizeof(danceability));
            binaryFile.read((char*)&energy, sizeof(energy));
            binaryFile.read((char*)&key, sizeof(key));
            binaryFile.read((char*)&loudness, sizeof(loudness));
            binaryFile.read((char*)&mode, sizeof(mode));
            binaryFile.read((char*)&speechiness, sizeof(speechiness));
            binaryFile.read((char*)&acousticness, sizeof(acousticness));
            binaryFile.read((char*)&instrumentalness, sizeof(instrumentalness));
            binaryFile.read((char*)&liveness, sizeof(liveness));
            binaryFile.read((char*)&valence, sizeof(valence));
            binaryFile.read((char*)&tempo, sizeof(tempo));
            binaryFile.read((char*)&time_signature, sizeof(time_signature));

            Track t(id, name, artist, id_artist, release_date, isExp, popularity, duration, danceability, energy, key, loudness, mode, speechiness, acousticness, 
            instrumentalness, liveness, valence, tempo, time_signature);

            t.textSave(textFile);

        }
    }
    binaryFile.close();
    if(textFile.is_open()){
        textFile.close();
        cout<<"Artists output generated successfully."<<endl;
    }
}