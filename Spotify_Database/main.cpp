#include <iostream> //biblioteca padrão
#include <vector> //std::vector
#include <algorithm> //std::find
#include <stdlib.h> //rand, srand
#include <time.h> //time
#include <iomanip>
#include <fstream>
#include <string>
#include <stdio.h>
#include "Artist.h"
#include "const.h"
#include "getCsvData.h"
#include "getBinaryData.h"
#include "HashOperations.h"
#include "HashTable.h"
#include "SortingAnalysis.h"
#include "BTreeAnalysis.h"
#include "RBTree.h"

using namespace std;

/**
 * @brief Verifica, primeiramente, a existência dos arquivos csv no endereço fornecido pelo usuário. Se existirem,
 * verifica a presença dos arquivos binários. Se os binários não existem, chama a função que os cria.
 *
 * @param path, representa o endereço do diretório onde o usuário escoheu salvar o arquivo e onde está o arquivo de tipo binário
 */
void verificaBinarios(char path[])
{

    cout<<"Checking if the csv files exist in the path..."<<endl;
    string artistCsvPath;
    artistCsvPath.append(path).append("/artists.csv");
    string trackCsvPath;
    trackCsvPath.append(path).append("/tracks.csv");

    ifstream artistCsv;
    ifstream trackCsv;

    artistCsv.open(artistCsvPath, ios::in);
    trackCsv.open(trackCsvPath, ios::in);

    if(!artistCsv || !trackCsv)
    {
        cout<<"Error, csv file(s) were not found in path!"<<endl;
        exit(23);
    }
    else
    {
        cout<<"Csv files found."<<endl;
        artistCsv.close();
        trackCsv.close();
    }

    cout<<"Checking if the bin files exist in the path..."<<endl;

    string artistBinPath;
    artistBinPath.append(path).append("/artists.bin");
    string trackBinPath;
    trackBinPath.append(path).append("/tracks.bin");

    ifstream artistBin;
    ifstream trackBin;

    artistBin.open(artistBinPath, ios::binary);
    trackBin.open(trackBinPath, ios::binary);

    if (!artistBin)
    {
        cout<<"artists.bin not found in the path."<<endl;
        csvToBinaryArtists(path);
    }
    else
    {
        cout<<"artists.bin found in the path."<<endl;
        artistBin.close();
    }

    if (!trackBin)
    {
        cout<<"tracks.bin not found in the path."<<endl;
        csvToBinaryTracks(path);
    }
    else
    {
        cout<<"tracks.bin found in the path."<<endl;
        trackBin.close();
    }

}

/**
 * @brief Menu inicial que coleta a opção que o usuário deseja para a etapa de impressão
 *
 * @return true, se o usuário escolher tela/console
 * @return false, se o usuário escolher aruivo de tipo texto
 */
bool saidaUsuario()
{
    int choice;
    cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
    do
    {
        cout<<"Choose the output method:"<<endl;
        cout<<"[1]--> Console"<<endl<<"[2]--> Text file"<<endl;
        cout<<"Option: ";
        cin>>choice;
        cout<<endl;
        cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
    }
    while(choice != 1 && choice != 2);

    switch (choice)
    {
    case 1:
        return true;
        break;

    case 2:
        return false;
        break;
    default:
        cout<<"Unknown error!!!"<<endl;
        exit(34);
    }
}


/*int saidaUsuario2()
{
    int option;
    cout << "Choose the next step:" << endl;
    cout << "1. Sort" << endl;
    cout << "2. Hash" << endl;
    cout << "3. Test Module" << endl;
    cout << "Option: ";
    cin >> option;
    switch (option) {
        case 3:
        case 2:
        case 1:
            return option;
            break;
        default:
            cout << "Invalid option! Try again." << endl << endl;
            return saidaUsuario2();
        break;
    }
}
*/

int saidaUsuario3()
{
    int option;

    cout << "Choose the next step:" << endl;
    cout << "1. Arvore Vermelho-Preta" << endl;
    cout << "2. Arvore B" << endl;
    cout << "3. Sair" << endl;
    cout << "Option: ";
    cin >> option;

    switch (option) {
        case 3:
            return option;
            break;
        case 2:
            return option;
            break;
        case 1:
            return option;
            break;
        default:
            cout << "Invalid option! Try again." << endl << endl;
            return saidaUsuario3();
        break;
    }
}
/*
void testStep(char path[]) {
    //STEP 1
    cout<<"Testing STEP 1..."<<endl;
    setOpsTeste(path);
    //STEP 2
    cout<<"Testing STEP 2..."<<endl;
    hashOperationsFn(path, 1000, 10, true);
}
void trabalho2(int option, char path[]) {
    switch (option) {
        case 1:
            // METODO DE ORDENAÇÃO
            cout << "Sort..." << endl;
            setOps(path);
            break;
        case 2:
            // METODO DE HASH
            cout << "Hash..." << endl;
            hashStep(path);
            break;
        case 3:
            // MÓDULO DE TESTE
            cout << "Test Module..." << endl;
            testStep(path);
            break;
        default:
            cout << "Unknown error!" << endl;
            exit(42);
        break;
    }
}*/

void fillTreeRB(char* path){

    fstream fileOut;

    fileOut.open("saidaVermelhoPreto.txt", ios::in| ios::out|ios::app);

    RBTree myTree(path);

    string str;

    cout<<"Digite o nome que deseja buscar: "<<endl;
    cin>>str;
    cout<<endl;
    cout<<"ffff"<<endl;
    char name[str.length()];

    strcpy(name, str.c_str());
    cout<<"ffff"<<endl;
    myTree.fillTree();

    auto start = std::chrono::steady_clock::now();
    cout<<boolalpha<<myTree.isOnTree(name)<<endl;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    fileOut<<"Tempo de execução foi de " << elapsed_seconds.count()<<" segundos";

    fileOut.close();

}
void trabalho3(int option, char path[]) {
    switch (option) {
        case 1:
            // ARVORE VERMELHO PRETA
            cout << "ARVORE VERMELHO PRETA..." << endl;
            fillTreeRB(path);
            break;
        case 2:
            // ARVORE B
            cout << "ARVORE B..." << endl;
            subMenu(path);
            break;
        case 3:
            // SAIR
            cout << "SAIR..." << endl;
            exit(0);
            break;
        default:
            cout << "Unknown error!" << endl;
            exit(42);
        break;
    }
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        cout << "Error! Not sufficient parameters!!!" << endl;
        exit(0);
    }

    verificaBinarios(argv[1]);

    int userChoice = saidaUsuario3();

    trabalho3(userChoice, argv[1]);


    return 0;
}