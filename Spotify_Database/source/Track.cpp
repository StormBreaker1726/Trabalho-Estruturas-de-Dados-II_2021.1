#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include "Track.h"

using namespace std;

Track::Track(char *id, char *name, char *artist, char *id_artist, char *release_date, int isExp, int popularity, int duration, float danceability, float energy, 
int key, float loudness, int mode, float speechiness, float acousticness, float instrumentalness, float liveness, float valence, float tempo, int time_signature){
//Inicializando os atributos de cada uma das tracks com os valores fornecidos:

//inicializando as variáveis de tipo vetor de char:
    strcpy(this->id, id);
    strcpy(this->name, name);
    strcpy(this->artist, artist);
    strcpy(this->id_artist, id_artist);
    strcpy(this->release_date, release_date);

//inicializando as variáveis de tipo bool:
    this->isExp = isExp;

//inicializando as variáveis de tipo int e float:
    this->popularity = popularity;
    this->duration = duration;
    this->danceability = danceability;
    this->energy = energy;
    this->key = key;
    this->loudness = loudness;
    this->mode = mode;
    this->speechiness = speechiness;
    this->acousticness = acousticness;
    this->instrumentalness = instrumentalness;
    this->liveness = liveness;
    this->valence = valence;
    this->tempo = tempo;
    this->time_signature = time_signature;

}

Track::~Track() {
}

void Track::printTrack(){

//Imprimindo os atributos da Track no console/terminal/tela:
    cout<<"----------------------------------------------------------------"<<endl;

    cout<<"Track: "<<endl;

    cout<<"Music ID--> ";
    cout<<this->id<<endl;

    cout<<"Music Name--> ";
    cout<<this->name<<endl;

    cout<<"Music Artist--> ";
    cout<<this->artist<<endl;

    cout<<"Music Id Artist--> ";
    cout<<this->id_artist<<endl;

    cout<<"Music Release Date--> ";
    cout<<this->release_date<<endl;

    cout<<"Is the Music Explicit--> ";
    cout<<boolalpha<<this->isExp<<endl;

    cout<<"Music Popularity--> ";
    cout<<this->popularity<<endl;

    cout<<"Music Duration (ms)--> ";
    cout<<this->duration<<endl;

    cout<<"Music Danceability--> ";
    cout<<this->danceability<<endl;

    cout<<"Music Energy--> ";
    cout<<this->energy<<endl;

    cout<<"Music Key--> ";
    cout<<this->key<<endl;

    cout<<"Music Loudness--> ";
    cout<<this->loudness<<endl;

    cout<<"Music Mode--> ";
    cout<<this->mode<<endl;

    cout<<"Music Speechiness--> ";
    cout<<this->speechiness<<endl;

    cout<<"Music Acousticness--> ";
    cout<<this->acousticness<<endl;

    cout<<"Music Instrumentalness--> ";
    cout<<this->instrumentalness<<endl;

    cout<<"Music Liveness--> ";
    cout<<this->liveness<<endl;

    cout<<"Music Valence--> ";
    cout<<this->valence<<endl;

    cout<<"Music Tempo--> ";
    cout<<this->tempo<<endl;

    cout<<"Music Time Signature--> ";
    cout<<this->time_signature<<endl;

    cout<<"----------------------------------------------------------------"<<endl;

}

void Track::textSave(fstream &OUT_FILE){

//Escrevendo os vetores de char:
    OUT_FILE<<this->id<<",";
    OUT_FILE<<this->name<<",";
    OUT_FILE<<this->artist<<",";
    OUT_FILE<<this->id_artist<<",";
    OUT_FILE<<this->release_date<<",";

//Escrevendo o bool:
    OUT_FILE<<this->isExp<<",";

//Escrevendo os inteiros e float:
    OUT_FILE<<this->popularity<<",";
    OUT_FILE<<this->duration<<"ms"<<",";
    OUT_FILE<<this->danceability<<",";
    OUT_FILE<<this->energy<<",";
    OUT_FILE<<this->key<<",";
    OUT_FILE<<this->loudness<<",";
    OUT_FILE<<this->mode<<",";
    OUT_FILE<<this->speechiness<<",";
    OUT_FILE<<this->acousticness<<",";
    OUT_FILE<<this->instrumentalness<<",";
    OUT_FILE<<this->liveness<<",";
    OUT_FILE<<this->valence<<",";
    OUT_FILE<<this->tempo<<",";
    OUT_FILE<<this->time_signature<<endl;

}

int Track::size(){

//calculando e retornando o tamanho de cada registro no arquivo:
    return (5*sizeof(int) + 9*sizeof(float) + (TRACK_DATE+TRACK_ARTIST_ID+TRACK_ARTISTS_NAME+TRACK_NAME+TRACK_ID)*sizeof(char) + sizeof(int));

}
//Fim do Track.cpp
