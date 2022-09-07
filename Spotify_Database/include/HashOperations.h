#ifndef A7A0F832_C278_42A2_8D49_53831EA61BE9
#define A7A0F832_C278_42A2_8D49_53831EA61BE9
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdio.h>
#include "Artist.h"
#include "const.h"
#include "Track.h"
#include "HashTable.h"
#include "getBinaryData.h"
#include "getCsvData.h"

using namespace std;


void splitIdArtist(vector<string> *arrIdArtists, char*id_artist) {
    string strIdArtist(id_artist);
    int i = 0, step = TRACK_ID - 1;

    if (strIdArtist[i] == '"') i++;
    if (strIdArtist[i] == '[') i++;

    while (i < strIdArtist.length()) {
        if (strIdArtist[i] == '\'') i++;
        arrIdArtists->push_back(strIdArtist.substr(i, step));
        i += TRACK_ID;
        while (strIdArtist[i] == ',' || strIdArtist[i] == ' ' || strIdArtist[i] == ']') i++;
    }
}


void getArtistsFromTracks(HashTable *hashTable, vector<int> trackIndexes, char *path) {
    string trackBinPath;
    trackBinPath.append(path).append("/tracks.bin");

    fstream binaryFile;
    binaryFile.open(trackBinPath, ios::in|ios::binary);

    int index;

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

    int size = trackIndexes.size();
    int s_file = Track::size();

    int dados;
    vector<string> arrIdArtists;
    for(int index:trackIndexes){


        
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

        splitIdArtist(&arrIdArtists, id_artist);

        for(string idArtist : arrIdArtists) {

            char tempora[idArtist.length() + 1];
            strcpy(tempora, idArtist.c_str());
            dados = hashTable->find(tempora, id, popularity);
            if (dados == -1) { 
                int dado = hashTable->insert(tempora, 1, id, popularity);
            }
        }

        for(string s:arrIdArtists) {
            s.clear();
        }
        arrIdArtists.clear();

        memset(id, 0, TRACK_ID);
        memset(name, 0, TRACK_NAME);
        memset(artist, 0, TRACK_ARTISTS_NAME);
        memset(id_artist, 0, TRACK_ARTIST_ID);
        memset(release_date, 0, TRACK_DATE);
    }
}


int * leHashDat(char path[]) {
    int * dados = new int [2];
    
    string line;

    cout<<"Checking if the hash.dat files exist in the path..."<<endl;
    string hashDatPath;
    hashDatPath.append(path).append("/hash.dat");

    ifstream hashDat;
    hashDat.open(hashDatPath, ios::in);

    if(!hashDat){
        cout<<"Error, hash.dat file was not found in path!"<<endl;
        exit(25);
    }

    cout<<"hash.dat file found."<<endl;

    // n
    std::getline(hashDat, line, ' ');
    dados[0] = std::stoi(line);

    // m
    std::getline(hashDat, line);
    dados[1] = std::stoi(line);

    hashDat.close();
    return dados;
}

void hashOperationsFn(char path[], int n, int m, bool teste) {
    vector<int> randomTrackIndexes;
    cout<<"Generating random indexes..."<<endl;
    generateRandomIndexes(&randomTrackIndexes, n, TRACK_TOTAL_ROWS);

    HashTable  hashTable(n*60, path);

    
    cout<<"Getting artists from tracks..."<<endl;
    getArtistsFromTracks(&hashTable, randomTrackIndexes, path);
    
    cout<<"Getting most frequent artists..."<<endl;
    hashTable.getMostFrequentArtists(m, teste);
}


void hashStep(char path[]) {
    int *hashDatParams = leHashDat(path);
    int n = hashDatParams[0], m = hashDatParams[1];

    hashOperationsFn(path, n, m, false);

    delete []hashDatParams;
}


#endif /* A7A0F832_C278_42A2_8D49_53831EA61BE9 */
