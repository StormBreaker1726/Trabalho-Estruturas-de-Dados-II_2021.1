#include <string.h>
#include "Artist.h"

Artist::Artist(char* id, float followers, char* genre, char* name, int popularity) {
    strcpy(this->id, id);
    this->followers = followers;
    strcpy(this->genre, genre);
    strcpy(this->name, name);
    this->popularity = popularity;
}

Artist::~Artist() {
}

void Artist::printArtist() {
  
    //Imprimindo os atributos do Artist no console/terminal/tela:

    cout<<"----------------------------------------------------------------"<<endl;

    cout<<"Artist:"<<endl;

    cout<<"ID--> ";
    cout<<this->id<<endl;

    cout<<"Followers--> ";
    cout<<this->followers<<endl;

    cout<<"Genres--> ";
    cout<<this->genre<<endl;

    cout<<"Name--> ";
    cout<<this->name<<endl;

    cout<<"Popularity--> ";
    cout<<this->popularity<<endl;

    cout<<"----------------------------------------------------------------"<<endl;
}

void Artist::textSave(fstream &OUT_FILE) {

    OUT_FILE<<this->id<<",";
    OUT_FILE<<this->followers<<",";
    OUT_FILE<<this->genre<<",";
    OUT_FILE<<this->name<<",";
    OUT_FILE<<this->popularity<<endl;
}

float Artist::getFollowers(){
    return this->followers;
}

int Artist::size() {

    //calculando e retornando o tamanho de cada registro no arquivo:
    return (sizeof(int) + sizeof(float) + (ARTIST_ID_SIZE + ARTIST_GENRE_SIZE + ARTIST_NAME)*sizeof(char));
}