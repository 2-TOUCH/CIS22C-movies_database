#pragma once
#include <vector>
#include <stack>
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
    std::vector<Movie> DFS(std::string);
    void preOrder() const;
    void postOrder() const;
    void printTree(void visit(Movie&, int)) const {_printTree(visit, root,1);}
    int getCount() const { return count; }
    bool isEmpty() const { return count == 0; }
    bool isLeafNode(Node* node) { return !node->getLeftPtr() && !node->getRightPtr();}
    Node* getParent(Node*, Node*);
    
private:
    Node* _insert(Node* nodePtr, Node* newNode);
    Node* _finder(Movie dataIn, Node* nodePtr);
    void _remove(Movie dataIn, Node* nodePtr); 
    void _inOrder(Node* root, std::vector<Movie>&) const;
    void _destroy(Node* root);
    void _dfs(std::stack<Node*>&, std::string, std::vector<Movie>&); 
    void _printTree(void visit(Movie&, int), Node* nodePtr, int level) const;
};
	
         
