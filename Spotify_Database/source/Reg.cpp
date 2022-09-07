#include "Reg.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

using namespace std;


Register::Register(char* id, int number_of_occurrences, char *mostPopularMusicId, int mostPopularMusicPopularity){
    strcpy(this->id, id);
    strcpy(this->mostPopularMusicId, mostPopularMusicId);
    
    this->number_of_occurrences = number_of_occurrences;
    this->mostPopularMusicPopularity = mostPopularMusicPopularity;
}

Register::~Register() {
    /* delete []this->id;
    delete []this->mostPopularMusicId; */
}

void Register::setOccurrences(int newOccurrences){
    this->number_of_occurrences = newOccurrences;
}

void Register::setMostPopularMusicId(char *newmostPopularMusicId) 
{
    strcpy(this->mostPopularMusicId, newmostPopularMusicId);
}

void Register::setMostPopularMusicPopularity(int newMostPopularMusicPopularity) 
{
    this->mostPopularMusicPopularity = newMostPopularMusicPopularity;
}

char* Register::getId(){
    return id;
}

int Register::getOccurrences(){
    return number_of_occurrences;
}

char* Register::getMostPopularMusicId() 
{
    return mostPopularMusicId;
}

int Register::getMostPopularMusicPopularity() 
{
    return mostPopularMusicPopularity;
}
