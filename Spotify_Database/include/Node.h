#ifndef A94BC00F_EE06_489A_9513_B3ACFF438968
#define A94BC00F_EE06_489A_9513_B3ACFF438968

#include "const.h"

class Node{
    public:
        Node(int positionInBinaryFile, char* id); //ok //blz
        ~Node();//ok //blz
        Node(){
            this->parent = NULL;
            this->left = NULL;
            this->right = NULL;
        };

        /*Setters functions*/
        void setId(char* newId); //ok //blz
        void setPositionInBinaryFile(int newPositionInBinaryFile); //ok //blz
        void setRight(Node* newRight, Node* nill); //ok //blz
        void setLeft(Node* newLeft, Node* nill); //ok //blz
        void setRightOnly(Node* newRight); //ok //blz
        void setLeftOnly(Node* newLeft); //ok //blz
        void setParent(Node* newParent); //ok //blz
        void setColor(bool newColor); //ok //blz

        /*Getters functions*/
        Node* getLeft(); //ok //blz
        Node* getRight(); //ok //blz
        Node* getParent(); //ok //blz
        Node* uncle(); //ok //blz
        Node* siblings(); //ok

        char* getId(); //ok //blz
        int getPositionInBinaryFile(); //ok //blz
        bool getColor(); //ok //blz
        void moveDown(Node* nodeParent); //ok
        bool hasRedChild(); //ok //blz
        bool isOnLeft(); //ok //blz

    private:
        /*Data to be stored in the node*/
        int positionInBinaryFile; //ok //blz 
        char id[ARTIST_ID_SIZE]; //ok //blz

        /*Node proprieties*/
        Node* left; //ok //blz
        Node* right; //ok //blz
        Node* parent; //ok //blz

        bool color; //ok //blz 
};

#endif /* A94BC00F_EE06_489A_9513_B3ACFF438968 */
