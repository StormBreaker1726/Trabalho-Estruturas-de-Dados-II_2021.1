#include <iostream> //biblioteca padrão
#include <vector> //std::vector
#include <string>
#include <algorithm> //std::find
#include <stdlib.h> //rand, srand
#include <iomanip>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>

using namespace std;

#include "Node.h"

Node::Node(int positionInBinaryFile, char* id) 
{
    setPositionInBinaryFile(positionInBinaryFile);
    setId(id);

    setColor(false);

    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
}

Node::~Node() 
{
    
}

void Node::setId(char* newId) 
{
    strcpy(this->id, newId);
}

void Node::setPositionInBinaryFile(int newPositionInBinaryFile) 
{
    this->positionInBinaryFile = newPositionInBinaryFile;
}

void Node::setRight(Node* newRight, Node* nill) 
{
    this->right = newRight;

    if (newRight != nill) {
        newRight->setParent(this);
    }
}

void Node::setLeft(Node* newLeft, Node* nill) 
{
    this->left = newLeft;
    
    if (newLeft != nill) {
        newLeft->setParent(this);
    }
}

void Node::setRightOnly(Node* newRight) 
{
    this->right = newRight;
}

void Node::setLeftOnly(Node* newLeft) 
{
    this->left = newLeft;
}

void Node::setParent(Node* newParent) 
{
    this->parent = newParent;
}

void Node::setColor(bool newColor) 
{
    this->color = newColor;
}

Node* Node::getLeft() 
{
    return this->left;
}

Node* Node::getRight() 
{
    return this->right;
}

Node* Node::getParent() 
{
    return this->parent;
}

/* Node* Node::uncle() 
{
    if(this->parent == NULL || this->parent->getParent() == NULL){
        return NULL;
    }
    if(this->parent->isOnLeft()){
        return this->parent->getParent()->getRight();
    }
    else{
        return this->parent->getParent()->getLeft();
    }
} */

/* Node* Node::siblings() 
{
    if(this->parent == NULL){
        return NULL;
    }
    if(isOnLeft()){
        return this->parent->getRight();
    }
    return parent->getLeft();
} */

char* Node::getId() 
{
    return this->id;
}

int Node::getPositionInBinaryFile() 
{
    return positionInBinaryFile;
}

bool Node::getColor() 
{
    return this->color;
}

/* void Node::moveDown(Node* nodeParent) 
{
    if(this->parent != NULL){
        if(isOnLeft()){
            this->parent->setLeft(nodeParent);
        }
        else{
            this->parent->setRight(nodeParent);
        }
    }
    nodeParent->setParent(this->parent);
    setParent(nodeParent);
}

bool Node::hasRedChild() 
{
    return ((this->left != NULL && this->left->getColor() == false) || (this->right != NULL && this->right->getColor() == false));
}

bool Node::isOnLeft() 
{
    if(parent == NULL){
        return false;
    }
    return (this == this->parent->getLeft());
} */


