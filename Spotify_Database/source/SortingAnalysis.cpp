#include <iostream> //biblioteca padrão
#include <vector> //std::vector
#include <algorithm> //std::find
#include <stdlib.h> //rand, srand
#include <time.h> //time
#include <stdio.h>
#include <fstream>
#include <string>
#include "Artist.h"
#include "Track.h"
#include "const.h"
#include "getBinaryData.h"
#include "SortingAlgorithmFollowers.h"

using namespace std;

void loadData(int n, string sortMethod, char *path, ofstream &textFile)
{
    string artistBinPath;

    artistBinPath.append(path).append("/artists.bin");


    fstream binaryFile;

    binaryFile.open(artistBinPath, ios::in|ios::binary);

    int s_file = Artist::size();

    float followersArr[n];

    string metricsResult;

    vector<int> randomIndexes;

    int index;

    char id[ARTIST_ID_SIZE];
    float followers;
    char genre[ARTIST_GENRE_SIZE];
    char name[ARTIST_NAME];
    int popularity;

    clock_t timeStart, timeStop;
    int comparation[] = {0, 0, 0};
    int movimentation[] = {0, 0, 0};
    float time[] = {0.0, 0.0, 0.0};
    float movimentationMedia = 0;
    float comparationMedia = 0;
    float timeMedia = 0;

    for (int i = 0; i < STEP_1_ATTEMPTS; i++)
    {
        generateRandomIndexes(&randomIndexes, n, ARTIST_TOTAL_ROWS);

        for (int j = 0; j < n; j++)
        {
            index = randomIndexes[j];
            binaryFile.seekg((index-1)*s_file, ios::beg);
            binaryFile.read((char*)id, sizeof(id));
            binaryFile.read((char*)&followers, sizeof(followers));
            binaryFile.read((char*)genre, sizeof(genre));
            binaryFile.read((char*)name, sizeof(name));
            binaryFile.read((char*)&popularity, sizeof(popularity));

            Artist a(id, followers, genre, name, popularity);
            a.printArtist();
            followersArr[j] = a.getFollowers();

        }
        if (sortMethod.compare("quicksort"))
        {
            timeStart = clock();
            quicksortFollowers(followersArr,n,comparation[i], movimentation[i]);
            timeStop = clock();
            time[i] = ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);

        }
        else if (sortMethod.compare("heapsort"))
        {
            timeStart = clock();
            heapSortFollowers(followersArr, n,comparation[i], movimentation[i]);
            timeStop = clock();
            time[i] = ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        }
        else if (sortMethod.compare("timsort"))
        {
            timeStart = clock();
            timSortFollowers(followersArr, n,comparation[i], movimentation[i]);
            timeStart = clock();
            time[i] = ((double)(timeStop - timeStart) / CLOCKS_PER_SEC);
        }
        else
        {
            cout << "Unknown sort method!" << endl;
            exit(69);
        }
        timeMedia += time[i];
        movimentationMedia += movimentation[i];
        comparationMedia += comparation[i];

        randomIndexes.clear();

        comparation[i] = 0;
        movimentation[i] = 0;
    }

    textFile << "Tempo médio gasto do " << sortMethod << " com " << n << " registros aleatórios: " << timeMedia / 3 << endl;
    textFile << "Comparacoes médias gasto do " << sortMethod << " com " << n << " registros aleatórios : " << comparationMedia / 3 << endl;
    textFile << "Movimentacoes médias gastas do " << sortMethod << " com " << n << " registros aleatórios : " << movimentationMedia / 3 << endl
             << endl
             << endl;

    movimentationMedia = 0;
    comparationMedia = 0;
    timeMedia = 0;

    binaryFile.close();



}

void runSorts(int n, char *path,ofstream &textFile)
{
    loadData(n, "quicksort", path,textFile);
    loadData(n, "heapsort", path,textFile);
    loadData(n, "timsort", path,textFile);
}

void setOpsTeste(char *path) {
    ofstream textFile;
    string saidaTxtPath;

    saidaTxtPath.append("./data").append("/teste.txt");
    textFile.open(saidaTxtPath, ios::out);

    runSorts(100, path, textFile);
}

void setOps(char *path)
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
    ofstream textFile;
    string saidaTxtPath;

    saidaTxtPath.append("./data").append("/saida.txt");
    textFile.open(saidaTxtPath, ios::out);
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
        runSorts(v[l],path,textFile);
    }
    textFile.close();

}
