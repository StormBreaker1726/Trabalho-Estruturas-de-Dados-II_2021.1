#ifndef EED3B5EE_C2DC_431A_8D4C_BCFED44CB5C3
#define EED3B5EE_C2DC_431A_8D4C_BCFED44CB5C3

//Including the "main headers"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include <string.h>

using namespace std;

class MinHeapNode{
    public:
        //Setters:
        void setData(char data);
        void setFrequency(unsigned frequency);
        void setLeftSon(MinHeapNode* leftSon);
        void setRightSon(MinHeapNode* rightSon);
        
        //Getters:
        unsigned getFrequency();
        char getData();
        MinHeapNode* getLeftSon();
        MinHeapNode* getRightSon();

        //Constructor and Destructor:
        MinHeapNode(char data, unsigned frequency);
        MinHeapNode();
        ~MinHeapNode();

        //Helper function:
        bool isLeaf();

    private:
        MinHeapNode* leftSon;
        MinHeapNode* rightSon;
        char data;
        unsigned frequency;
};

void MinHeapNode::setData(char data) 
{
    this->data = data; // Função ta com problema de assignment
}

void MinHeapNode::setFrequency(unsigned frequency) 
{
    this->frequency = frequency;
}

void MinHeapNode::setLeftSon(MinHeapNode* leftSon) 
{
    this->leftSon = leftSon;
}

void MinHeapNode::setRightSon(MinHeapNode* rightSon) 
{
    this->rightSon = rightSon;
}

unsigned MinHeapNode::getFrequency() 
{
    return this->frequency;
}

char MinHeapNode::getData() 
{
    return this->data;
}

MinHeapNode* MinHeapNode::getLeftSon() 
{
    return this->leftSon;
}

MinHeapNode* MinHeapNode::getRightSon() 
{
    return this->rightSon;
}

MinHeapNode::MinHeapNode(char data, unsigned frequency) 
{
    this->data = data;
    this->frequency = frequency;
    this->leftSon = nullptr;
    this->rightSon = nullptr;
}

MinHeapNode::MinHeapNode(){
    this->data = '$';
    this->frequency = 1;
    this->leftSon = nullptr;
    this->rightSon = nullptr;
}

MinHeapNode::~MinHeapNode() 
{
    //Do nothing
}

bool MinHeapNode::isLeaf() 
{
    return !(this->leftSon) && !(this->rightSon);
}


#endif /* EED3B5EE_C2DC_431A_8D4C_BCFED44CB5C3 */
