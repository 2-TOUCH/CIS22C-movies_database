#pragma once
#include <vector>
#include "Movie.h"
#include "BSTNode.h"

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
    bool remove(Movie);
    Node* getMax(Node*);
    Node* getMin(Node*);
    std::vector<Movie> inOrder()const;
    void preOrder() const;
    void postOrder() const;
    int getCount() const { return count; }
    bool isEmpty() const { return count == 0; }

private:
    Node* _insert(Node* nodePtr, Node* newNode);
    Node* _finder(Movie dataIn, Node* nodePtr);
    void _remove(Movie dataIn, Node* nodePtr); 
    void _inOrder(Node* root, std::vector<Movie>&) const;
    void _destroy(Node* root);
   
};
