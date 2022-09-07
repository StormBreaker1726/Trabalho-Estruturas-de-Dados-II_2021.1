#ifndef ED5A3107_91B2_48AF_BE3A_032351138954
#define ED5A3107_91B2_48AF_BE3A_032351138954

#include <iostream>
#include <fstream>
#include "MinHeapNode.h"
using namespace std;
using std::cout;

void printArray(int* arr, int n){
    int i;
    for(i = 0; i < n; ++i){
        cout<<arr[i];
    }
    cout<<endl;
}

void getFrequencies(fstream& file, int* frequencies){

    char com;
    while(file.get(com)){

        if(com == 'a'){
            frequencies[0] = frequencies[0] + 1;
        }
        else if(com == 'c'){
            frequencies[1] = frequencies[1] + 1;
        }
        else if(com == 'g'){
            frequencies[2] = frequencies[2] + 1;
        }
        else if(com == 't'){
            frequencies[3] = frequencies[3] + 1;
        }
    }
    cout<<"Finished"<<endl;
}

void auxWriteCodes(fstream& file, int* arr, int n, MinHeapNode* root){
    int i;
    for(i = 0; i < n; ++i){
        file<<arr[i];
    }
    file<<root->getData();
}

void writeCodes(fstream& file, MinHeapNode* root, int* arr, int top)
{
    if(root->getLeftSon()){
        arr[top] = 0;
        writeCodes(file, root->getLeftSon(), arr, top + 1);
    }

    if(root->getRightSon()){
        arr[top] = 1;
        writeCodes(file, root->getRightSon(), arr, top + 1);
    }

    if(root->isLeaf()){
        //cout<<root->getData()<<":  ";
        auxWriteCodes(file, arr, top, root);
    }
}



#endif /* ED5A3107_91B2_48AF_BE3A_032351138954 */

/*
The Deoxyribonucleic Acid bases:
    t --> Thymine
    g --> Guanine
    a --> Adenine
    c --> Cytosine
*/