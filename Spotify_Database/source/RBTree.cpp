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

#include "Artist.h"
#include "const.h"
#include "RBTree.h"
#include "helper.h"

RBTree::RBTree(string path) 
{
    this->path = path;
    
    nill = new Node();
    nill->setColor(true);
    this->root = nill;
}

RBTree::~RBTree() 
{

}

void RBTree::printNode(Node* x) 
{
    cout<<"Id   "<<x->getId()<<endl;
    cout<<"Color    "<<x->getColor()<<endl;
}


Node* RBTree::getRoot() 
{
    return this->root;
}

Node* RBTree::searchByName(char* name) 
{
    /*
        <0	the first character that does not match has a lower value in ptr1 than in ptr2
        0	the contents of both strings are equal
        >0	the first character that does not match has a greater value in ptr1 than in ptr2
    */

    if(root == NULL){
        return NULL;
    }
    Node* temp = root;

    while(temp != NULL){
        int n = namesCompareNew(temp->getPositionInBinaryFile(), name);
        
        if(n == 0){
            return temp;
        }
        else if(n > 0){
            if(temp->getLeft() == NULL){
                break;
            }
            else{
                temp = temp->getLeft();
            }
        }
        else if(n < 0){
            if(temp->getRight() == NULL){
                break;
            }
            else{
                temp = temp->getRight();
            }
        }
    }

    return NULL;
}

/* Node* RBTree::search(char* name) 
{
    // cout<<"*****search begins"<<endl;
    if(root == NULL){
        return NULL;
    }
    Node* temp = root;
    Node* parent = NULL;

    while(temp != NULL){
        int n = namesCompareNew(temp->getPositionInBinaryFile(), name);
        // cout<<"n:"<<n<<endl;
        if(n == 0){
            return temp;
        }
        else if(n > 0){
            if(temp->getLeft() == NULL){
                break;
            }
            else{
                parent = temp;
                temp = temp->getLeft();
            }
        }
        else if(n < 0){
            if(temp->getRight() == NULL){
                break;
            }
            else{
                parent = temp;
                temp = temp->getRight();
            }
        }
    }
    if(temp != NULL)
        return temp;
    else
        return parent;
}
 */
void RBTree::insert(char* id, int positionInBinaryFile, char* name) 
{

    Node* z = new Node(positionInBinaryFile, id);

    Node* y = nill;
    Node* x = root;

    while(x != nill){
        y = x;
        char nameTemp[375];
        nameRecover(x->getPositionInBinaryFile(), nameTemp);
        toLowerAll(name);
        toLowerAll(nameTemp);
        //cout<<"nameTemp:"<<nameTemp<<endl;
        int n = strncmp(nameTemp, name, ARTIST_NAME);
        //cout<<"n:"<<n<<endl;
        if(n < 0){
            x = x->getRight();
        }
        else if(n > 0){
            x = x->getLeft();
        }
    }

    z->setParent(y);

    if(y == nill){
        root = z;
    }
    else{
        char nameTe[375];
        //cout<<"oo"<<endl;
        nameRecover(y->getPositionInBinaryFile(), nameTe);
        toLowerAll(name);
        toLowerAll(nameTe);
        //cout<<"nameTe:"<<nameTe<<endl;
        int qw = strncmp(nameTe, name, ARTIST_NAME);
        //cout<<"qw:"<<qw<<endl;
        if(qw < 0){
            y->setRightOnly(z);
        }
        else if(qw > 0){
            y->setLeftOnly(z);
        }
    }

    z->setLeftOnly(nill);
    z->setRightOnly(nill);
    z->setColor(false);

    RBInsertFixUp(z);
}

void RBTree::RBInsertFixUp(Node* z)
{
    Node *y = nill;

    //cout<<"z->getParent():"<<z->getParent()<<endl;

    while(z->getParent()->getColor() == false){
        if(z->getParent() == z->getParent()->getParent()->getLeft()){
            y = z->getParent()->getParent()->getRight();
            if(y->getColor() == false){
                z->getParent()->setColor(true);
                y->setColor(true);
                z->getParent()->getParent()->setColor(false);
                z = z->getParent()->getParent();
            }
            else{ 
                if(z == z->getParent()->getRight()){
                    z = z->getParent();
                    leftRotate(z);
                }
                z->getParent()->setColor(true);
                z->getParent()->getParent()->setColor(false);
                rightRotate(z->getParent()->getParent());
            }
        }
        else{
            y = z->getParent()->getParent()->getLeft();
            if(y->getColor() == false){
                z->getParent()->setColor(true);
                y->setColor(true);
                z->getParent()->getParent()->setColor(false);
                z = z->getParent()->getParent();
            }
            else{ 
                if(z == z->getParent()->getLeft()){
                    z = z->getParent();
                    rightRotate(z);
                }
                z->getParent()->setColor(true);
                z->getParent()->getParent()->setColor(false);
                leftRotate(z->getParent()->getParent());
            }
        }
    }
    root->setColor(true);
}

void RBTree::printInOrder() 
{
    //cout<<"inOrder: "<<endl;
    if(root == nill){
        //cout<<"There's nothing to print here!!!"<<endl;
    }
    else{
        inOrder(root);
    }
    //cout<<endl;
}

void RBTree::fillTree() 
{
    string artistBinPath;
    artistBinPath.append(path).append("/artists.bin");

    fstream binaryFile;
    binaryFile.open(artistBinPath, ios::in|ios::binary);

    char id[23];
    float followers;
    char genre[318];
    char name[375];
    int popularity;

    int s_file = Artist::size(); 

    for (int i = 1; i <= ARTIST_TOTAL_ROWS; i++)
    {
        binaryFile.seekg((i-1)*s_file, ios::beg);
        binaryFile.read((char*)id, sizeof(id));
        binaryFile.read((char*)&followers, sizeof(followers));
        binaryFile.read((char*)genre, sizeof(genre));
        binaryFile.read((char*)name, sizeof(name));
        binaryFile.read((char*)&popularity, sizeof(popularity));
        //cout<<"Row-->  "<<i<<endl;
        //cout << "Name:"<<name<<endl;
        //cout<<"Id: "<<id<<endl;
        
        insert(id, i, name);
        //cout<<"   Inserted with success!"<<endl;
        //cout<<"####################"<<endl;

    }
    cout<<"All insertions were made"<<endl;
    
    cout<<"####################"<<endl;

    binaryFile.close();
}

void RBTree::getPath() 
{
    cout<<path<<endl;
}

void RBTree::leftRotate(Node* x) 
{
    //cout<<"leftRotate start"<<endl;
    Node* y = x->getRight();

    x->setRightOnly(y->getLeft());
    y->getLeft()->setParent(x);

    y->setParent(x->getParent());

    if(x->getParent() == nill){
        root = y;
    }
    else if(x == x->getParent()->getLeft()){
        x->getParent()->setLeftOnly(y);
    }
    else{
        x->getParent()->setRightOnly(y);
    }
    
    y->setLeftOnly(x);
    x->setParent(y);

    //cout<<"leftRotate finish"<<endl;
}

void RBTree::rightRotate(Node* x) 
{
    //cout<<"rightRotate start"<<endl;
    Node* y = x->getLeft();

    x->setLeftOnly(y->getRight());
    y->getRight()->setParent(x);

    y->setParent(x->getParent());

    if(x->getParent() == nill){
        root = y;
    }
    else if(x == x->getParent()->getRight()){
        x->getParent()->setRightOnly(y);
    }
    else{
        x->getParent()->setLeftOnly(y);
    }
    
    y->setRightOnly(x);
    x->setParent(y);
}

void RBTree::swapColors(Node* x1, Node* x2) 
{
    bool temp;

    temp = x1->getColor();
    x1->setColor(x2->getColor());
    x2->setColor(temp);
}
/* 
void RBTree::fixRedRed(Node* x) 
{
    if(x == root){
        
        x->setColor(true);
        return;
    }
    
    Node* parent = x->getParent();
    if(parent == NULL){
        return;
    }
    Node* grandparent = parent->getParent();
    
    Node* uncle = x->uncle();
    

    if(parent->getColor() != true){
        if(uncle != NULL){ 
            if(uncle->getColor() == false){
                parent->setColor(true);
                uncle->setColor(true);
                grandparent->setColor(false);
                fixRedRed(grandparent);
            }
            else{
                if(parent->isOnLeft()){
                    if(x->isOnLeft()){
                        swapColors(parent, grandparent);
                    }
                    else{
                        leftRotate(parent);
                        swapColors(x, grandparent);
                    }
                    rightRotate(grandparent);
                }
                else{
                    if(x->isOnLeft()){
                        rightRotate(parent);
                        swapColors(x, grandparent);
                    }
                    else{
                        swapColors(parent, grandparent);
                    }
                    leftRotate(grandparent);
                }
        }
        }
        else{
            if(parent->isOnLeft()){
                if(x->isOnLeft()){
                    swapColors(parent, grandparent);
                }
                else{
                    leftRotate(parent);
                    swapColors(x, grandparent);
                }
                rightRotate(grandparent);
            }
            else{
                if(x->isOnLeft()){
                    rightRotate(parent);
                    swapColors(x, grandparent);
                }
                else{
                    swapColors(parent, grandparent);
                }
                leftRotate(grandparent);
            }
        }
    }
} */
/* 
void RBTree::fixDoubleBlack(Node* x) 
{
    if(x == root){
        return;
    }
    Node* sibling = x->siblings();
    Node* parent = x->getParent();

    if(sibling == NULL){
        fixDoubleBlack(parent);
    }
    else{
        if(sibling->getColor() == false){
            parent->setColor(false);
            sibling->setColor(true);
            if(sibling->isOnLeft()){
                rightRotate(parent);
            }
            else{
                leftRotate(parent);
            }
            fixDoubleBlack(parent);
            
        }
        else{
            if(sibling->hasRedChild()){
                if(sibling->getLeft() != NULL) 
                    if(sibling->getLeft()->getColor() == false){
                        if(sibling->isOnLeft()){
                            sibling->getLeft()->setColor(sibling->getColor());
                            sibling->setColor(parent->getColor());
                            rightRotate(parent);
                        }
                        else{
                            sibling->getLeft()->setColor(parent->getColor());
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    }
                    else{
                        if(sibling->isOnLeft()){
                            sibling->getRight()->setColor(parent->getColor());
                            leftRotate(sibling);
                            rightRotate(sibling);
                        }
                        else{
                            sibling->getRight()->setColor(sibling->getColor());
                            sibling->setColor(parent->getColor());
                            leftRotate(parent);
                        }
                    }
                parent->setColor(true);
            }
            else{
                sibling->setColor(false);
                if(parent->getColor() == true){
                    fixDoubleBlack(parent);
                }
                else{
                    parent->setColor(true);
                }
            }
        }
    }
} */

void RBTree::inOrder(Node* x) 
{
    if(x == nill){
        return;
    }
    inOrder(x->getLeft());
    cout<<"Id:  "<<x->getId()<<"\nPosition in Binary File:  "<<x->getPositionInBinaryFile()<<endl;
    inOrder(x->getRight());
}

void RBTree::nameRecover(int position, char* name) 
{
    string artistBinPath;
    artistBinPath.append(path).append("/artists.bin");

    fstream binaryFile;
    binaryFile.open(artistBinPath, ios::in|ios::binary);

    char id[23];
    float followers;
    char genre[318];
    int popularity;

    int s_file = Artist::size();

    binaryFile.seekg((position-1)*s_file, ios::beg);
    binaryFile.read((char*)id, sizeof(id));
    binaryFile.read((char*)&followers, sizeof(followers));
    binaryFile.read((char*)genre, sizeof(genre));
    binaryFile.read((char*)name, sizeof(ARTIST_NAME));
    binaryFile.read((char*)&popularity, sizeof(popularity));

    binaryFile.close();
    //cout<<"ter"<<endl;
}

int RBTree::namesCompare(int position1, int position2) 
{
    char nameOne[375];
    char nameTwo[375];
    int n;

    nameRecover(position1, nameOne);
    nameRecover(position2, nameTwo);

    toLowerAll(nameOne);
    toLowerAll(nameTwo);

    n = strncmp(nameOne, nameTwo, ARTIST_NAME);

    return n;
}

int RBTree::namesCompareNew(int position, char* name) 
{
    char nameTwo[375];
    char nameTemp[375];
    int n;

    strcpy(nameTemp, name);

    nameRecover(position, nameTwo);

    toLowerAll(nameTwo);
    toLowerAll(nameTemp);

    n = strncmp(nameTwo, nameTemp, ARTIST_NAME);

    return n;
}



bool RBTree::isOnTree(char* name) 
{
    return searchByName(name) != NULL;
}

Node* RBTree::successor(Node* x) 
{
    Node* temp = x;

    while(temp->getLeft() != NULL){
        temp = temp->getLeft();
    }
    return temp;
}

/* 
void RBTree::inserir(char* id, int position) 
{
    Node *novoNo = new Node();
    root = novoNo->inserirAux(root, id, position);

    if (root != NULL)
        root->setCor(BLACK);
}


Node *RBTree::inserirAux(Node *root, char* chave, int loc)
{
    if (root == NULL)
    {
        Node *aux = new Node(loc, chave);
        return aux;
    }

    int n = root->getId().length();
    char char_x[n + 1];
    strcpy(char_x, root->getId().c_str());

    n = chave.length();
    char char_y[n + 1];
    strcpy(char_y, chave);

    int comp = strcmp(char_y, char_x);

    if (comp > 0)
        root->setLeft(inserirAux(root->getLeft(), chave, loc));
    else
        root->setRight(inserirAux(root->getRight(), chave, loc));

    if (root->getRight() != NULL && root->getLeft() != NULL && root->getRight()->getColor() == false && root->getLeft()->getColor() == true)
        root = leftRotate(root);

    if (root->getLeft() != NULL && root->getLeft()->getLeft() != NULL && root->getLeft()->getColor() == false && root->getLeft()->getLeft()->getColor() == false)
        root = rightRotate(root);

    if (root->getRight() != NULL && root->getLeft() != NULL && root->getLeft()->getColor() == false && root->getRight()->getColor() == false)
        root->setColor(true);

    return root;
} */
/*
... gdb executavel
... run
... backtrace (pilha de execução)
*/