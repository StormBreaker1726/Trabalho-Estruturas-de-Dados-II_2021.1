#ifndef FAB06DAB_7375_4DF4_A95B_E4FB7218D45A
#define FAB06DAB_7375_4DF4_A95B_E4FB7218D45A

#include "Node.h"

class RBTree{
    public:
        RBTree(string path); //imp
        ~RBTree();
        
        void printNode(Node* x);

        Node* getRoot(); //imp
        Node* searchByName(char* name); //Função de busca para ser usada pelo usuário //imp
        Node* search(char* name); //Função de busca para ser usada durante a inserção //imp

        void insert(char* id, int positionInBinaryFile, char* name); //imp
        void printInOrder(); //imp
        void fillTree();
        void getPath();

        void inserir(char* id, int position);

        bool isOnTree(char* name); //imp

    private:
        string path;
        Node* root;
        Node* nill;
        Node *inserirAux(Node *root, char* chave, int loc);
        void leftRotate(Node* x); //imp
        void rightRotate(Node* x); //imp
        void swapColors(Node* x1, Node* x2); //imp
        void fixRedRed(Node* x); //imp
        void fixDoubleBlack(Node* x); //imp
        void inOrder(Node* x); //imp
        void nameRecover(int position, char* name); //imp

        int namesCompare(int position1, int position2); //imp
        int namesCompareNew(int position, char* name); //imp

        void RBInsertFixUp(Node* z);
        

        Node* successor(Node* x); //imp
};

#endif /* FAB06DAB_7375_4DF4_A95B_E4FB7218D45A */
