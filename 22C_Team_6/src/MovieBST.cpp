// Implementation file for the BinaryTree class
#include <iostream>  // For cout and NULL


#include "movieBST.h"
#include <cstdlib>   // For rand()
#include <ctime>     // For time()
using namespace std;

/**~*~*
   Constructor
*~**/
BinaryTree::BinaryTree()
{
    root = NULL;
    count = 0;
}
/**~*~*
   This function calls a recursive function to traverse the
   tree in postorder (the wrapper function)
*~**/


/**~*~*
   This function calls a recursive function to traverse the
   tree in inorder (the wrapper function)
*~**/
void BinaryTree::inOrder() const
{
    _inOrder(root);
}

/**~*~*
   Inorder Traversal of the Binary Tree:
   Left-Root-Right (recursive)
*~**/
void BinaryTree::_inOrder(Node* root) const
{
    if (root)
    {
        _inOrder(root->left);
        cout << root->data.num << " ";
        _inOrder(root->right);
    }
}

/**~*~*
   Insert data into a random Binary Tree
*~**/
void BinaryTree::insert(Data dataIn)
{
    Node* newNode;
    Node* pWalk;
    Node* parent;
    int  rand_num;

    // allocate the new node
    newNode = new Node;
    newNode->data = dataIn;
    newNode->left = NULL;
    newNode->right = NULL;

    // find a "random" parent
    if (!root) // tree is empty
        root = newNode;
    else
    {
        parent = NULL; // root does not have a parent
        pWalk = root;
        while (pWalk) {
            parent = pWalk;
            rand_num = rand() % 100;
            if (rand_num % 2) // if odd - take left
                pWalk = pWalk->left;
            else
                pWalk = pWalk->right;
        }

        // insert the new node
        if (!parent->left) // no left child
            parent->left = newNode;
        else
            parent->right = newNode;
    }

    count++;
}

/**~*~*
   Destructor
   This function calls a recursive function to delete all nodes in the binary tree
*~**/
BinaryTree::~BinaryTree()
{
    if (root)
        _destroy(root);
}

/**~*~*
   This function traverses the binary tree in postorder and deletes every node
*~**/
void BinaryTree::_destroy(Node* root)
{
    if (root)
    {
        _destroy(root->left);
        _destroy(root->right);
        delete root;
    }
}




