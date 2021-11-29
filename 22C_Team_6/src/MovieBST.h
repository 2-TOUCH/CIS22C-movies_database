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
//    bool delete(Movie dataIn);
    std::vector<Movie> inOrder()const;
    void preOrder() const;
    void postOrder() const;
    int getCount() const { return count; }
    bool isEmpty() const { return count == 0; }

private:
    Node* _insert(Node* nodePtr, Node* newNode);
    void _inOrder(Node* root, std::vector<Movie>&) const;
    void _destroy(Node* root);
};
