#ifndef B1DF5179_BD33_42F2_A3F3_AC016307A5A0
#define B1DF5179_BD33_42F2_A3F3_AC016307A5A0

//Including the "main headers"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include "const.h"
#include <string>
#include <string.h>
#include <fstream>

using namespace std;

#include "MinHeap.h"
#include "Helper.h"

//Defines
#define MAX_TREE_HIGHT 100

char Bases[] = {'a','c','g','t'};
string binBases[] = {"10", "0", "111", "110"};

//Auxiliar Functions
MinHeapNode* buildHuffmanTree(char* data, int* frequency, int size){

    MinHeapNode* left;
    MinHeapNode* right;
    MinHeapNode* top;

    MinHeap minHeap(250);
    minHeap.createAndBuildMinHeap(data, frequency, size);

    while (!minHeap.isSizeOne())
    {
        left = minHeap.extractMin();
        right = minHeap.extractMin();

        top = new MinHeapNode('$', left->getFrequency() + right->getFrequency());

        top->setLeftSon(left);
        top->setRightSon(right);

        minHeap.insertMinHeap(top);
    }
    
    return minHeap.extractMin();
}

void printCodes(MinHeapNode* root, int* arr, int top){

    if(root->getLeftSon()){
        arr[top] = 0;
        printCodes(root->getLeftSon(), arr, top + 1);
    }

    if(root->getRightSon()){
        arr[top] = 1;
        printCodes(root->getRightSon(), arr, top + 1);
    }

    if(root->isLeaf()){
        cout<<root->getData()<<":  ";
        printArray(arr, top);
    }
}

string getEncodedValue(char data) {
    int size = sizeof(Bases) / sizeof(Bases[0]);
    for (int i = 0; i < size; i++) {
        if (Bases[i] == data) return binBases[i] + " ";
    }

    return ""; // colocar mensagem de erro e encerrar sistema
}

string getNodeEncodedString(MinHeapNode* root) {
    string nodeEncodedString = "";
    
    for (int i = 0; i < root->getFrequency(); i++)
        nodeEncodedString += getEncodedValue(root->getData());
    
    return nodeEncodedString;
}

string getEncodedString(MinHeapNode* root) {
    string encodedString = "";

    if (root->getRightSon() != nullptr)
        encodedString += getEncodedString(root->getRightSon());
    if (root->getLeftSon() != nullptr)
        encodedString += getEncodedString(root->getLeftSon());

    return encodedString + getNodeEncodedString(root);
}

//Huffman Code
string findValueInHeap(MinHeapNode* root, const char value) {
    string aux = "";
    if (root == nullptr)
        return "*";

    if (root->getData() == value)
        return "";

    aux = findValueInHeap(root->getRightSon(), value);
    if (aux.compare("*") != 0)
        return "1" + aux;

    aux = findValueInHeap(root->getLeftSon(), value);
    if (aux.compare("*") != 0)
        return "0" + aux;

    return "*";
}

void HuffmanCodes(fstream& DNAFile, char* data, int* frequency, int size, string DNAFilename){
    MinHeapNode* root;

    string dnaCompTxtPath = "";
    dnaCompTxtPath.append(DNAFilename).append("-comp.txt");

    fstream outFile;
    outFile.open(dnaCompTxtPath, ios::out);

    root = buildHuffmanTree(data, frequency, size);

    int arr[MAX_TREE_HIGHT], top = 0;

    DNAFile.open(DNAFilename, ios::in);

    writeCodes(outFile, root, arr, top);
    outFile << endl;
    char com = 0;
    
    while(DNAFile.get(com)){
        outFile<<findValueInHeap(root, com);
    }

    outFile.close();
    DNAFile.close();
}



void huffmanCompression(char* path, const char* filename) {
    /* NO MÉTODO HUFFMAN */
    char com = 0;

    string dnaTxtPath = "";
    dnaTxtPath.append(path).append("/").append(filename);

    fstream DNAFile;
    DNAFile.open(dnaTxtPath, ios::in);

    if (!DNAFile.is_open()) {
        cout<<"Path to the file: "<<dnaTxtPath<<endl;
        cout<<"Error: File " << filename << " not found!"<<endl;
        exit(23);
    }
    int contThymine; 
    int contGuanine;
    int contAdenine;
    int contCytosine;

    contCytosine = contThymine = contGuanine = contAdenine = contCytosine = 0;

    int freq[] = {contAdenine, contCytosine, contGuanine, contThymine};
    getFrequencies(DNAFile, freq);
    DNAFile.close();

    char Bases[] = {'a','c','g','t'};

    int size = sizeof(Bases) / sizeof(Bases[0]);
    HuffmanCodes(DNAFile, Bases, freq, size, dnaTxtPath);
}

void decode(fstream& compressedDnaSequence, fstream& altFile) {
    char com = 0, value;
    string header = "";

    int contPossibleValues = 0;
    MinHeapNode *root = new MinHeapNode();
    MinHeapNode *currNode = root;

    while (compressedDnaSequence.get(com) && com != '\n') {
        switch(com) {
            case '0':
                if (currNode->getLeftSon() == nullptr) {
                    currNode->setLeftSon(new MinHeapNode());
                }
                currNode = currNode->getLeftSon();
                break;
            case '1':
                if (currNode->getRightSon() == nullptr) {
                    currNode->setRightSon(new MinHeapNode());
                }
                currNode = currNode->getRightSon();
                break;
            default:
                currNode->setData(com);
                currNode = root;
        }
    }
    currNode = root;
    
    while (compressedDnaSequence.get(com)) {
        switch (com) {
            case '0':
                currNode = currNode->getLeftSon();
                break;
            case '1':
                currNode = currNode->getRightSon();
                break;
        }

        value = currNode->getData();
        if (value != '$') {
            altFile << value;
            currNode = root;
        }
    }
}

void huffmanDecompression(char* path, const char* filename) {
    string dnaCompressedTxtPath = "";
    dnaCompressedTxtPath.append(path).append("/").append(filename);

    fstream dnaCompressedTxt;
    dnaCompressedTxt.open(dnaCompressedTxtPath, ios::in);

    string dnaDecompressedTxtPath = "";
    dnaDecompressedTxtPath.append("/").append(dnaCompressedTxtPath).append("-decomp.txt");

    fstream dnaDecompressedTxt;
    dnaDecompressedTxt.open(dnaDecompressedTxtPath, ios::out);
    decode(dnaCompressedTxt, dnaDecompressedTxt);

    dnaCompressedTxt.close();
    dnaDecompressedTxt.close();
}



void huffmanCompressionStart(char *path) {
    for (int i = 1; i <= N; i++) {
        string filename = "dna" + to_string(i) + ".txt";
        huffmanCompression(path, filename.c_str());
    }
}

void huffmanDecompressionStart(char *path) {
    for (int i = 1; i <= N; i++) {
        string filename = "dna" + to_string(i) + ".txt-comp.txt";
        huffmanDecompression(path, filename.c_str());
    }
}





#endif /* B1DF5179_BD33_42F2_A3F3_AC016307A5A0 */

/*
The Deoxyribonucleic Acid bases:
    t --> Thymine
    g --> Guanine
    a --> Adenine
    c --> Cytosine
*/
