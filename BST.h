#ifndef BST_H
#define BST_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class BST
{
    private:
        struct Node// a struct node that saves a word along its necessary info
        {
            string content; //the word itself
            Node *ladd, *radd;//children
            int counter;
        };

        Node* root;//root of the tree
        Node* NewNode(string); //creates new node
        Node* minofmax(string x); //minimum value of a right subtree; It's used in deleteNode
        Node* deleteNode(string, Node*&);//deletes a node if counter==1, otherwise the counter is subtracted by one
        Node* searchNode(string, Node*);//searches a node based on its content

        //tree traversals
        void inOrder(Node*);
        void postOrder(Node*);
        void preOrder(Node*);

        //inserts a new node in the right place
        void insertNewNode(string, Node*);


    public:
        //public versions of functions above
        BST();
        void GetIns(string x){insertNewNode(x, root);}
        void inOrderPub(){inOrder(root);}
        void preOrderPub(){preOrder(root);}
        void postOrderPub(){postOrder(root);}
        void GetDel(string x){deleteNode(x, root);}
        void printsearch(string x, ofstream &y){Node* temp=searchNode(x,root); y<<temp->content<<":"<<temp->counter<<"   ";}
        void GetSer(string x){searchNode(x, root);}
};

#endif // BST_H
