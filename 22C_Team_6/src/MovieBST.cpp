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
   tree in inorder (the wrapper function)
*~**/
void BinaryTree::inOrder() const
{
    _inOrder(root);
}

Node* BinaryTree::_insert(Node* nodePtr, Node* newNode)
{

    Node* pWalk = nodePtr;

    if (nodePtr)
    {
        nodePtr = newNode;
        return nodePtr;
    }
    else
    {
        if (pWalk->getItem() > newNode->getItem())
        {
            if (!pWalk->getLeftPtr())
            {
                pWalk->setLeftPtr(newNode);
            }
            else
                _insert(pWalk->getLeftPtr(), newNode);
        }
        else
        {
            if (pWalk->getRightPtr())
            {
                pWalk->setRightPtr(newNode);
            }
            else
                _insert(pWalk->getRightPtr(), newNode);
        }
        return nodePtr;
    }
}

/**~*~*
   Inorder Traversal of the Binary Tree:
   Left-Root-Right (recursive)
*~**/
void BinaryTree::_inOrder(Node* root) const
{
    if (root)
    {
        _inOrder(root->getLeftPtr());
        cout << root->getItem().getTitle()<< " ";
        _inOrder(root->getRightPtr());
    }
}

/**~*~*
   Insert data into a random Binary Tree
*~**/
bool BinaryTree::insert(Movie dataIn)
{
    Node* newNodePtr = new Node(dataIn);
    root = _insert(root, newNodePtr);
    return true;
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
        _destroy(root->getLeftPtr());
        _destroy(root->getRightPtr());
        delete root;
    }
}

