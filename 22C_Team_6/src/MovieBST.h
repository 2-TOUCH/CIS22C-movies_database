// Specification file for the BinaryTree class
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "Movie.h"
#include "Node.h"


class BinaryTree
{
private:


    Node* root;       // root of the tree
    int count;        // number of nodes in the tree

public:
    // Constructor
    BinaryTree();

    // Destructor
    ~BinaryTree();

    // Binary Tree operations
    bool insert(Movie dataIn);
    void inOrder() const;
    void preOrder() const;
    void postOrder() const;
    int getCount() const { return count; }
    bool isEmpty() const { return count == 0; }


private:
    Node* _insert(Node* nodePtr, Node* newNode);
    void _inOrder(Node* root) const;
    void _destroy(Node* root);
};
#endif
