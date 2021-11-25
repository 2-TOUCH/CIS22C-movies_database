#pragma once
#ifndef _BINARY_NODE
#define _BINARY_NODE
#include "Movie.h"

class Node
{
private:
	Movie    item;         // Data portion
	Node* leftPtr;		// Pointer to left child
	Node* rightPtr;		// Pointer to right child

public:
	// constructors
	Node(const Movie& anItem) { item = anItem; leftPtr = 0; rightPtr = 0; }
	Node(const Movie& anItem,
		Node* left,
		Node* right) {
		item = anItem; leftPtr = left; rightPtr = right;
	}
	// setters
	void setItem(const Movie& anItem) { item = anItem; }
	void setLeftPtr(Node* left) { leftPtr = left; }
	void setRightPtr(Node* right) { rightPtr = right; }

	// getters
	Movie getItem() const { return item; }
	Node* getLeftPtr() const { return leftPtr; }
	Node* getRightPtr() const { return rightPtr; }


};

#endif 
