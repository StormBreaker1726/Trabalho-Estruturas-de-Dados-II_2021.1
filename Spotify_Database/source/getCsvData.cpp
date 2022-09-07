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
#include "getCsvData.h"
#include "const.h"

using namespace std;

void csvToBinaryArtists(char *path){

    cout<<"Generating artists.bin..."<<endl;

    string artistCsvPath;
    artistCsvPath.append(path).append("/artists.csv");

    string artistBinPath;
    artistBinPath.append(path).append("/artists.bin");
    //Abertura dos arquivos:
    fstream artistsBinary; //ponteiro para o arquivo binário
    fstream artistsCSV; //ponteiro para o arquivo CSV

    artistsCSV.open(artistCsvPath, ios::in); //Abrindo o arquivo original em .csv apenas para leitura
    artistsBinary.open(artistBinPath, ios::out|ios::binary); //Abrindo e/ou criando o arquivo .bin para escrita

    //Criação as variáveis de armazenamento (no caso segui o nome das colunas do .csv)
    char id[ARTIST_ID_SIZE];
    float followers;
    char tmp[1];
    char genres[ARTIST_GENRE_SIZE];
    char name[ARTIST_NAME] = "";
    int popularity;

    //Variáveis auxiliares
    string line, temp, auxiliar;
    char auxBeg;

    int countComma;

    std::getline(artistsCSV, line);//le o header e o ignora

    while (std::getline(artistsCSV, line))
    {
        stringstream ss(line), oss;

        // ID
        std::getline(ss, temp, ',');
        strcpy(id, temp.c_str());

        // FOLLOWERS
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            followers = stof(temp);
        }
        else{
            followers = 0;
        }

        // GENRES

        if (ss.peek() == '"'){
            auxBeg = '"';
            std::getline(ss, temp, '[');
        }  

        std::getline(ss, temp, ']');
        strcpy(genres, temp.c_str());
        std::getline(ss, temp, ',');

        // NAME
        std::getline(ss, temp, '\n');

        countComma = std::count(temp.begin(), temp.end(), ',');
        oss.str(temp);

        while (countComma != 0) {
            std::getline(oss, temp, ',');
            strcat(name, temp.c_str());
            auxiliar = oss.str().substr(string(name).length() + 1);
            countComma = std::count(auxiliar.begin(), auxiliar.end(), ',');
        }

        // POPULARITY
        std::getline(oss, temp, '\n');

        if(temp.size() != 0){
            popularity = stoi(temp);
        }else{
            popularity = 0;
        }

        //Escrevendo os dados no arquivo .bin
        artistsBinary.write((char*)id, sizeof(id));
        artistsBinary.write((char*)&followers, sizeof(followers));
        artistsBinary.write((char*)genres, sizeof(genres));
        artistsBinary.write((char*)name, sizeof(name));
        artistsBinary.write((char*)&popularity, sizeof(popularity));

        memset(name, 0, strlen(name));
        memset(genres, 0, strlen(genres));
        memset(id, 0, strlen(id));

        artistsBinary.flush();
    }
    //Fechamento dos arquivos
    artistsBinary.close();
    artistsCSV.close();

    cout<<"artists.bin generated successfully."<<endl;
}

void csvToBinaryTracks(char *path){

    cout<<"Generating tracks.bin..."<<endl;

    string trackCsvPath;
    trackCsvPath.append(path).append("/tracks.csv");

    string trackBinPath;
    trackBinPath.append(path).append("/tracks.bin");

    //Abertura dos arquivos:
    fstream tracksBinary; //ponteiro para o arquivo binário
    fstream tracksCSV; //ponteiro para o arquivo CSV

    tracksCSV.open(trackCsvPath, ios::in); //Abrindo o arquivo original em .csv apenas para leitura
    tracksBinary.open(trackBinPath, ios::out|ios::binary); //Abrindo e/ou criando o arquivo .bin para escrita

    //Criação as variáveis de armazenamento (no caso segui o nome das colunas do .csv)
    char id[TRACK_ID] = "";
    char name[TRACK_NAME] = "";
    int popularity;
    int duration;
    int isExp;
    char artist[TRACK_ARTISTS_NAME] = "";
    char id_artist[TRACK_ARTIST_ID] = "";
    char release_date[TRACK_DATE] = "";
    float danceability;
    float energy;
    int key;
    float loudness;
    int mode;
    float speechiness;
    float acousticness;
    float instrumentalness;
    float liveness;
    float valence;
    float tempo;
    int time_signature;

    //Variáveis auxiliares
    string line, temp, auxiliar;
    char auxBeg;

    int countComma;

    getline(tracksCSV, line);//le o header e o ignora


    while (getline(tracksCSV, line))
    {

        stringstream ss(line), oss;

        // ID
        std::getline(ss, temp, ',');
        strcpy(id, temp.c_str());

        // NAME
        if (ss.peek() == '"') {
            while (ss.peek() == '"') {
                std::getline(ss, temp, '"');
                std::getline(ss, temp, '"');
                strcat(name, temp.c_str());
            }
            std::getline(ss, temp, ',');
        } else {
            std::getline(ss, temp, ',');
            strcpy(name, temp.c_str());   
        }

        // POPULARITY
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            popularity = stoi(temp);
        }
        else{
            popularity = 0;
        }

        // DURATION_MS
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            duration = stoi(temp);
        }
        else{
            duration = 0;
        }

        // EXPLICIT
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            isExp = stoi(temp);
        }
        else{
            isExp = 0;
        }

        // ARTISTS NAME
        if (ss.peek() == '"'){
            while(ss.peek() == '"') {
                std::getline(ss, temp, '"');
                std::getline(ss, temp, '"');
                strcat(artist, temp.c_str());
            }
        } else {
            std::getline(ss, temp, ']');
            strcpy(artist, temp.c_str());
        }
        std::getline(ss, temp, ',');

        // ARTISTS ID
        std::getline(ss, temp, ']');
        strcpy(id_artist, temp.c_str());
        std::getline(ss, temp, ',');

        // RELEASE DATE
        std::getline(ss, temp, ',');
        strcpy(release_date, temp.c_str());

        // DANCEABILITY
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            danceability = stof(temp);
        }
        else{
            danceability = 0;
        }

        

        // ENERGY
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            energy = stof(temp);
        }
        else{
            energy = 0;
        }

        

        // KEY
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            key = stoi(temp);
        }
        else{
            key = 0;
        }

        

        // LOUDNESS
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            loudness = stof(temp);
        }
        else{
            loudness = 0;
        }

        // MODE
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            mode = stoi(temp);
        }
        else{
            mode = 0;
        }

        // SPEECHINESS
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            speechiness = stof(temp);
        }
        else{
            speechiness = 0;
        }

        // ACOUSTICNESS
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            acousticness = stof(temp);
        }
        else{
            acousticness = 0;
        }

        // INSTRUMENTALNESS
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            instrumentalness = stof(temp);
        }
        else{
            instrumentalness = 0;
        }

        // LIVENESS
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            liveness = stof(temp);
        }
        else{
            liveness = 0;
        }

        // VALENCE
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            valence = stof(temp);
        }
        else{
            valence = 0;
        }

        // TEMPO
        std::getline(ss, temp, ',');
        if(temp.size() != 0){
            tempo = stof(temp);
        }
        else{
            tempo = 0;
        }

        // TIME_SIGNATURE
        std::getline(ss, temp, '\n');
        if(temp.size() != 0){
            time_signature = stoi(temp);
        }
        else{
            time_signature = 0;
        }


        //Escrevendo os dados no arquivo .bin
        tracksBinary.write((char*)id, sizeof(id));
        tracksBinary.write((char*)name, sizeof(name));
        tracksBinary.write((char*)&popularity, sizeof(popularity));
        tracksBinary.write((char*)&duration, sizeof(duration));
        tracksBinary.write((char*)&isExp, sizeof(isExp));
        tracksBinary.write((char*)artist, sizeof(artist));
        tracksBinary.write((char*)id_artist, sizeof(id_artist));
        tracksBinary.write((char*)release_date, sizeof(release_date));
        tracksBinary.write((char*)&danceability, sizeof(danceability));
        tracksBinary.write((char*)&energy, sizeof(energy));
        tracksBinary.write((char*)&key, sizeof(key));
        tracksBinary.write((char*)&loudness, sizeof(loudness));
        tracksBinary.write((char*)&mode, sizeof(mode));
        tracksBinary.write((char*)&speechiness, sizeof(speechiness));
        tracksBinary.write((char*)&acousticness, sizeof(acousticness));
        tracksBinary.write((char*)&instrumentalness, sizeof(instrumentalness));
        tracksBinary.write((char*)&liveness, sizeof(liveness));
        tracksBinary.write((char*)&valence, sizeof(valence));
        tracksBinary.write((char*)&tempo, sizeof(tempo));
        tracksBinary.write((char*)&time_signature, sizeof(time_signature));

        memset(id, 0, TRACK_ID);
        memset(name, 0, TRACK_NAME);
        memset(artist, 0, TRACK_ARTISTS_NAME);
        memset(id_artist, 0, TRACK_ARTIST_ID);
        memset(release_date, 0, TRACK_DATE);
        tracksBinary.flush();
    }

    //Fechamento dos arquivos
    tracksBinary.close();
    tracksCSV.close();

    cout<<"tracks.bin generated successfully."<<endl;
}