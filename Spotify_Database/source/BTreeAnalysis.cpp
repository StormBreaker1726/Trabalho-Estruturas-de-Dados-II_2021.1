/**
    Universidade Federal de Juiz de Fora
    BTreeAnalysis.cpp
    Propósito: Arquivo que implementar o BTreeAnalysis usando para fazer as analises na ArvoreB
    @author Ivanylson HG

*/
#include <iostream> //biblioteca padrão
#include <vector> //std::vector
#include <algorithm> //std::find
#include <stdlib.h> //rand, srand
#include <time.h> //time
#include <stdio.h>
#include <fstream>
#include <string>
#include "Artist.h"
#include "const.h"
#include "Contador.h"
#include "getBinaryData.h"
#include "ArvoreB.h"
#include "NoB.h"
#include "BTreeAnalysis.h"

using namespace std;

void analiseBTree(int tam, int ordem,char *path)
{
    ///Criando a arvore
    ArvoreB *avrb = new ArvoreB(ordem);

    ///Lendo o arquivo
    string artistBinPath;
    artistBinPath.append(path).append("/artists.bin");

    ///Pegando o binario
    fstream binaryFile;
    binaryFile.open(artistBinPath, ios::in|ios::binary);

    /**Vetor random**/
    vector<int> randomIndexes;
    int index;

    /**Metricas**/
    clock_t timeStart, timeStop;
    int comparation[M];
    float timeInsertion[M];
    float timeSearch[M];
    float comparationMedia;
    float timeInsertionMedia;
    float timeSearchMedia;

    /**Artist**/
    char id[ARTIST_ID_SIZE];
    float followers;
    char genre[ARTIST_GENRE_SIZE];
    char name[ARTIST_NAME];
    int popularity;

    char id2[ARTIST_ID_SIZE];
    float followers2;
    char genre2[ARTIST_GENRE_SIZE];
    char name2[ARTIST_NAME];
    int popularity2;

    ///Tamanho o arquivo de artist
    int s_file = Artist::size();


        /**Inserção**/
        for (int j = 0; j < s_file; j++)
        {
            int i=0;
            binaryFile.seekg(j*s_file, ios::beg);
            binaryFile.read((char*)id, sizeof(id));
            binaryFile.read((char*)&followers, sizeof(followers));
            binaryFile.read((char*)genre, sizeof(genre));
            binaryFile.read((char*)name, sizeof(name));
            binaryFile.read((char*)&popularity, sizeof(popularity));

            timeStart = clock();
            avrb->insert(name,id,j*s_file);
            timeStop = clock();

            timeInsertion[i] = ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
            timeInsertionMedia += timeInsertion[i];
            i++;
        }
        //comparation[i] = Contador::getInstance().getNumComparacoes();

        //comparationMedia+= comparation[i];
        //comparation[i] = 0;
        binaryFile.close();


    /**Busca**/
    binaryFile.open(artistBinPath, ios::in|ios::binary);
    for(int i = 0; i < M; i++)
    {
        generateRandomIndexes(&randomIndexes, tam, s_file);

        /**Radom**/
        index = randomIndexes[i];
        binaryFile.seekg(index*s_file, ios::beg);
        binaryFile.read((char*)id2, sizeof(id));
        binaryFile.read((char*)&followers2, sizeof(followers));
        binaryFile.read((char*)genre2, sizeof(genre));
        binaryFile.read((char*)name2, sizeof(name));
        binaryFile.read((char*)&popularity2, sizeof(popularity));

        timeStart = clock();
        NoB *qual = avrb->procura(name2);
        comparation[i] = Contador::getInstance().getNumComparacoes();
        if(qual !=NULL)
        {
            timeStop = clock();

        }
        else
        {
            timeStop = clock();
            delete qual;
        }
        comparationMedia+= comparation[i];
        comparation[i] = 0;
        timeSearch[i] = ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        randomIndexes.clear();
        timeSearchMedia += timeSearch[i];
    }


    /**--------------------------------------------------------------------------------**/
    /**Saida**/
    ofstream textFile;
    string saidaTxtPath;

    saidaTxtPath.append("./data").append("/saidaArvoreB.txt");
    textFile.open(saidaTxtPath, ios::out|ios::app);
    textFile << "T: " << ordem<< endl;
    textFile << "Tempo médio gasto com as inserções foi de: "<< timeInsertionMedia << endl;
    textFile << "Tempo médio gasto com as buscas dos registros aleatórios com:  "<< tam <<" : " << timeSearchMedia / M << endl;
    textFile << "Comparacoes médias gasto foi de:"<< comparationMedia / M << endl;


    timeInsertionMedia = 0;
    timeSearchMedia = 0;
    comparationMedia = 0;


    delete avrb;

    /**--------------------------------------------------------------------------------**/
}
void buscarDados(int ordem,char *path)
{
    ///Criando a arvore B
    ArvoreB *avrb = new ArvoreB(ordem);

    /**--------------------------------------------------------------------------------**/
    /**Leitura**/

    ///Lendo o arquivo
    string artistBinPath;
    artistBinPath.append(path).append("/artists.bin");

    ///Binario
    fstream binaryFile;
    binaryFile.open(artistBinPath, ios::in|ios::binary);

    ///Artists
    char id[ARTIST_ID_SIZE];
    float followers;
    char genre[ARTIST_GENRE_SIZE];
    char name[ARTIST_NAME];
    int popularity;

    /// Tamanho do arquivo Artist
    int s_file = Artist::size();

    ///Loop
    for (int j = 0; j < s_file; j++)
    {
        binaryFile.seekg(j*s_file, ios::beg);
        binaryFile.read((char*)id, sizeof(id));
        binaryFile.read((char*)&followers, sizeof(followers));
        binaryFile.read((char*)genre, sizeof(genre));
        binaryFile.read((char*)name, sizeof(name));
        binaryFile.read((char*)&popularity, sizeof(popularity));


        avrb->insert(name,id,j*s_file);
    }
    avrb->percorre();

    /**--------------------------------------------------------------------------------**/
    /**Procurando**/
    char nameProcura[ARTIST_NAME];
    cout << "Digite um nome para ser procurado" << endl;
    cin>>nameProcura;

    ///Procurando na arvore
    NoB *qual = avrb->procura(nameProcura);

    if(qual !=NULL)
    {
        cout << "Encontrado" << endl;
        cout <<"Localização: "<< qual->achachave(nameProcura) << endl;

        ///Arquivo
        string artistBinPath;
        artistBinPath.append(path).append("/artists.bin");

        ///Artists
        char id[ARTIST_ID_SIZE];
        float followers;
        char genre[ARTIST_GENRE_SIZE];
        char name[ARTIST_NAME];
        int popularity;

        ///Procurando
        binaryFile.seekg(qual->achachave(nameProcura), ios::beg);
        binaryFile.read((char*)id, sizeof(id));
        binaryFile.read((char*)&followers, sizeof(followers));
        binaryFile.read((char*)genre, sizeof(genre));
        binaryFile.read((char*)name, sizeof(name));
        binaryFile.read((char*)&popularity, sizeof(popularity));

        ///Retornando os dados
        cout << "Dados :"<< endl;
        cout << "ID :"<<id<< endl;
        cout << "FOLLOWERS :"<<followers<< endl;
        cout << "GENRE :"<<genre<< endl;
        cout << "NAME :"<<name<< endl;
        cout << "POPULARITY :"<<popularity<< endl;

        binaryFile.close();
    }
    delete qual;
    delete avrb;

}

void setOpsB(int n,char *path)
{
    string sortDats;
    sortDats.append("./data").append("/sort.dat");
    cout <<sortDats << endl;
    ifstream dataFile;
    dataFile.open(sortDats, ios::in);

    string temp;
    //vector<int> dataSizes;
    int tam=0;
    if(dataFile.is_open())
    {
        while (!dataFile.eof())
        {
            getline(dataFile, temp,'\n');
            tam++;//dataSizes.push_back(atoi(temp.c_str()));
            temp.clear();

        }
        dataFile.close();
    }
    else
    {
        cout << "ERROR" << endl;
    }
    cout << tam << endl;
    dataFile.open(sortDats, ios::in);

    string temp2;
    int v[tam-1];
    int i=0;
    if(dataFile.is_open())
    {
        while (!dataFile.eof())
        {
            getline(dataFile, temp2,'\n');
            v[i] = (atoi(temp2.c_str()));
            temp2.clear();
            i++;
        }
        dataFile.close();
    }
    else
    {
        cout << "ERROR" << endl;
    }

    for(int l=0; l< tam-1; l++)
    {
        analiseBTree(v[l],n,path);
    }
}


void subMenu(char *path)
{
    system("clear");
    int tamanho = 0;
    int option = 0;
    cout << "Digite a ordem minima da Arvore B:" << endl;
    cin >> tamanho;

    /**--------------------------------------------------------------------------------**/
    /**Menu**/

    cout << "\n Selecione uma opção abaixo:" << endl;
    cout << "1. Modo de analise" << endl;
    cout << "2. Modo de analise ArvoreB 20 e 200" << endl;
    cout << "3. Modo de teste (busca de um artista cujo nome ser lido pelo teclado)" << endl;
    cout << "4. Sair" << endl;
    cout << "Option: ";
    cin >> option;

    switch (option)
    {
    case 4:
        cout << "SAIR..." << endl;
        exit(0);
        break;
    case 3:
        buscarDados(tamanho,path);
        break;
    case 2:
        cout <<"Lendo sort.dat para fazer teste das metricas contendo o M" << endl;
        setOpsB(20,path);
        setOpsB(200,path);
        break;
    case 1:
        setOpsB(tamanho,path);
        break;

    default:
        cout << "Invalid option! Try again." << endl << endl;
        exit(0);
        break;
    }
}
/**--------------------------------------------------------------------------------**/
