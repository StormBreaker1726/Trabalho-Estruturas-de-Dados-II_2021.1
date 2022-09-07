#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include "bmh.h"
#include "bruteforce.h"
#include "kmp.h"
#include "rabinKarp.h"
#include "Huffman.h"
#include "testModule.h"

using namespace std;


void verifyIfFileExists(char path[], char filename[]) {

    cout<<"Checking if " << filename << " txt file exists in path..."<<endl;
    string filePath;
    filePath.append(path).append(filename);

    ifstream file;

    file.open(filePath, ios::in);

    if(!file){
        cout<<"Error, file not found in path!"<<endl;
        exit(23);
    }else{
        cout<<"File found."<<endl;
        file.close();
    }    
}



int userOutputSubMenu1() {
    int option;

    cout << "Choose the next step:" << endl;
    cout << "1. Brute Force" << endl;
    cout << "2. KMP" << endl;
    cout << "3. BMH" << endl;
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
            return userOutputSubMenu1();
        break;
    }
}

int userOutputSubMenu2() {
    int option;

    cout << "Choose the next step:" << endl;
    cout << "1. Compression" << endl;
    cout << "2. Decompression" << endl;
    cout << "Option: ";
    cin >> option;

    switch (option) {
        case 2:
        case 1:
            return option;
            break;    
        default:
            cout << "Invalid option! Try again." << endl << endl;
            return userOutputSubMenu2();
        break;
    }
}

void startSubMenu1(int option, char* path) { // MÉTODOS
    switch (option) {
        case 1:
            cout << "--------------------" << endl;
            cout << "Brute Force..." << endl;
			bruteForceMainStart(path);
			break;
		case 2:
            cout << "--------------------" << endl;
            cout << "KMP..." << endl;
			KmpMainStart(path);
			break;
		case 3:
            cout << "--------------------" << endl;
            cout << "BMH..." << endl;
			bhmMainStart(path);
			break;
		default:
            cout << "Unknown error!" << endl;
            exit(42);
        break;
    }
}

void startSubMenu2(int option, char* path) { // MÉTODOS
    switch (option) {
        case 1:
            cout << "--------------------" << endl;
            cout << "Compressing..." << endl;
            huffmanCompressionStart(path);
            break;
        case 2:
            cout << "--------------------" << endl;
            cout << "Decompressing..." << endl;
            huffmanDecompressionStart(path);
            break;  
        default:
            cout << "Unknown error!" << endl;
            exit(42);
        break;
    }
}

void subMenu1(char* path) {
    int userOption = userOutputSubMenu1();

    startSubMenu1(userOption, path);
}

void subMenu2(char* path) {
    int userOption = userOutputSubMenu2();

    startSubMenu2(userOption, path);
}

void start(int option, char* path, char* path2) { // MÉTODO TESTE 
    switch (option) {
        case 1:
            cout << "--------------------" << endl;
            cout << "Standard Matching..." << endl;
            subMenu1(path2);
            break;
        case 2:
            cout << "--------------------" << endl;
            cout << "Huffman..." << endl;
            subMenu2(path);
            break;
        case 3:
            cout << "--------------------" << endl;
            cout << "Test Module..." << endl;
            testModule(path, path2);
            break; 
        case 0:
            cout << "exit" << endl << endl;
            break;
        default:
            cout << "Unknown error!" << endl;
            exit(42);
        break;
    }
}

int userOutput() {
    int option;

    cout << "--------------------" << endl;
    cout << endl << "Main Menu:" << endl << endl;

    cout << "Choose the next step:" << endl;
    cout << "1. Standard Matching" << endl;
    cout << "2. Huffman" << endl;
    cout << "3. Test Module" << endl;
    cout << "0. Exit" << endl;
    cout << "Option: ";
    cin >> option;

    switch (option) {
        case 3:
        case 2:
        case 1:
        case 0:
            return option;
            break;    
        default:
            cout << "Invalid option! Try again." << endl << endl;
            return userOutput();
        break;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        cout << "Error! Insufficient Parameters" << endl;
        exit(0);
    }

    int userChoice;
    
    do {
        userChoice = userOutput();

        start(userChoice, argv[1], argv[2]);
    } while (userChoice);

    return 0;
}

