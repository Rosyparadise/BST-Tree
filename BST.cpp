#include "BST.h"
#include <iostream>

using namespace std;

BST::BST() //constructor sets the root of the tree to null
{
    root = NULL;
}


BST::Node* BST::NewNode(string x){ //creation of new node

    struct Node *newleaf = new Node;
    newleaf->content = x; //content is set as the parameter given
    newleaf->ladd = newleaf->radd = NULL; //since the node is new, it has no children
    newleaf->counter = 1;//it also can not have a counter other than 1
    return newleaf;//returns the pointer that points to the node created
}


void BST::insertNewNode(string x, Node *p)
{


    if(root == NULL) //if the root is null the tree is empty
    {
        root = NewNode(x);//so the first insertion will correspond to the root of the tree
    }
    else
    {
        if(p->content == x) //if the parameter is the same as the content of the node
        {
            p->counter++;//the counter is increased
        }


        else if(p->content < x)//if the parameter is larger than the content of the node
        {
            if(p->radd != NULL)//if the node has a left child
                insertNewNode(x, p->radd); //recursively execute insertnewnode for the right child
            else
                p->radd = NewNode(x);//if it doesnt, create a new node with x as the content
        }

        else if(p->ladd != NULL)//if the parameter is smaller than the content of the node and it has a left child
        {
            insertNewNode(x, p->ladd);//recursively execute insertnewnode for the left child
        }


        else
        {
            p->ladd = NewNode(x);//if it doesnt, create a new node with x as the content
        }

    }
}

BST::Node* BST::searchNode(string x, Node* p)
{
    if(root == NULL)//if the root is null the tree is null
    {
        return NULL;
    }
    else if(p->content == x)//the node is found
    {
        return p;
    }
    else
    {
        if(p->content > x)//if the parameter is smaller than the content of the node
        {
            if(p->ladd != NULL)//and it has a left child
                return searchNode(x, p->ladd);//recursively execute the function for the left child
        }

        else if(p->content < x)//if the parameter is larger than the content of the node
        {
            if(p->radd != NULL)//and it has a right child
                return searchNode(x, p->radd);//recursively execute the function for the right child
        }
    }

    return NULL;
}

BST::Node* BST::minofmax(string x)
{
    Node* temp=searchNode(x, root)->radd;//treats temp as the root of the right subtree
    while (temp->ladd!=NULL)//while there are left nodes
    {
        temp=temp->ladd;//keep changing temp to said node
    }
    return temp;








}

BST::Node* BST::deleteNode(string x, Node*& p){

    if(!p)//word is not found
    {
        return 0;
    }
    if(root == NULL)//if the tree is empty
    {   cout<<"No nodes in the tree"<<endl;
        return p;
    }

    else
    {
        if(x > p->content)//if the parameter is larger than the content of node
        {
            p->radd = deleteNode(x, p->radd);//execute the function recursively for the right child
            return p;
        }

        else if(x < p->content)//if the parameter is smaller than the content of node
        {
            p->ladd = deleteNode(x, p->ladd);//execute the function recursively for the left child
            return p;
        }

        //No children
        else if(p->ladd == NULL && p->radd == NULL && p->content == x)
        {
            if (p->counter>1)//if the word is saved more than once
            {
                p->counter--;//delete one of them
                return p;
            }

            else
            {
                delete p;//if its saved only once
                p = NULL;//delete the whole node
                return p;
            }
        }

        //One child
        else if(p->ladd != NULL&&p->radd==NULL && p->content == x)//the node has a left child
        {
            Node* temp=p->ladd;//saves the pointer pointing to the left child
            if (p->counter>1)//if the word is saved more than once
            {
                p->counter--;//delete one of them
                return p;
            }

            else if (root==p)//if root is the node that we want to delete
            {
                root=temp;//then the root will be equal to its left child
                return root;
            }

            else//if none of the above
            {
                delete p;//delete node
                p=NULL;
                return temp;
            }
        }

        else if(p->radd != NULL&&p->ladd==NULL && p->content == x)//the node has a right child
        {
            Node* temp=p->radd;//saves the pointer pointing to the right child
            if (p->counter>1)//if the word is saved more than once
            {
                p->counter--;//delete one of them
                return p;
            }
            else if (root==p)//if root is the node that we want to delete
            {
                root=temp;//then the root will be equal to its right child
                return root;
            }

            else//if none of the above
            {
                delete p;//delete node
                p=NULL;
                return temp;
            }

        }


        //Two children
        else if (p->radd!=NULL && p->ladd!=NULL && p->content==x)
        {
            if (p->counter>1)//if the word is saved more than once
            {
                p->counter--;//delete one of them
                return p;
            }

            else
            {
                Node* tempadd=minofmax(p->content);//find the minimum of the right subtree
                if (p->radd==tempadd)//if that minimum is the root of the right subtree
                {
                    p->radd=tempadd->radd;//make the node's right child the minimum's right child
                    p->content=tempadd->content;//and then change the content
                    p->counter=tempadd->counter;//and the counter to that of minimum, basically swapping places
                    delete tempadd;//delete node
                    tempadd=NULL;//check out!!!
                    return p;
                }
                else//otherwise
                {
                    p->content=tempadd->content;//change the content of the node
                    p->counter=tempadd->counter;//and the counter of the node to that of tempadd's
                    tempadd->counter=1;//set the counter of tempadd to 1
                    deleteNode(tempadd->content,p->radd);//so it can be deleted immediately by calling deleteNode
                    return p;
                }
            }
        }
    }
        return p;
}





//tree traversals

void BST::inOrder(Node* p)
{
    if(p == NULL)
        return;
    inOrder(p->ladd);
    cout<<p->content<<endl;
    inOrder(p->radd);
}

void BST::postOrder(Node* p)
{
    if(p == NULL)
        return;
    postOrder(p->ladd);
    postOrder(p->radd);
    cout<<p->content<<endl;

}

void BST::preOrder(Node* p)
{
    if(p == NULL)
        return;
    cout<<p->content<<endl;
    postOrder(p->ladd);
    postOrder(p->radd);

}
