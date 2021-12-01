// Implementation file for the BinaryTree class
#include <iostream>  // For cout and NULL

#include "movieBST.h"
#include <cstdlib>   // For rand()
#include <ctime>     // For time()
using namespace std;

/**
 * Constructor
 */
BinaryTree::BinaryTree()
{
    root = NULL;
    count = 0;
}


/**
 * This function calls a recursive function to traverse the
 * tree in inorder (the wrapper function)
 */
std::vector<Movie> BinaryTree::inOrder() const
{
    std::vector<Movie> inOrdList;
    _inOrder(root,inOrdList);
    return inOrdList;
}

Node* BinaryTree::_insert(Node* nodePtr, Node* newNode)
{

    Node* pWalk = nodePtr;

    if (!nodePtr)
    {
        nodePtr = newNode;
        return nodePtr;
    }
    else
    {
        if (pWalk->getItem().getTitle() > newNode->getItem().getTitle())
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
            if(!pWalk->getRightPtr())
            {
                pWalk->setRightPtr(newNode);
            }
            else
                _insert(pWalk->getRightPtr(), newNode);
        }
        return nodePtr;
    }
}

/**
 * Inorder Traversal of the Binary Tree:
 * Left-Root-Right (recursive)
 */
void BinaryTree::_inOrder(Node* root, std::vector<Movie>& list) const
{
    if (root)
    {
        _inOrder(root->getLeftPtr(), list);
        list.push_back(root->getItem());
        _inOrder(root->getRightPtr(), list);
    }
}

/**
 * Insert data into a random Binary Tree
 */
bool BinaryTree::insert(Movie dataIn)
{
    Node* newNodePtr = new Node(dataIn);
    root = _insert(root, newNodePtr);
    count++;
    return true;
}

/*bool BinaryTree::delete(Movie dataIn)
{
   Node* pWalk = root;
   if(!pWalk)
    return false;
}
*/

/**
 * Destructor
 * This function calls a recursive function to delete all nodes in the binary tree
 */
BinaryTree::~BinaryTree()
{
    if (root)
        _destroy(root);
}

/**
 * This function traverses the binary tree in postorder and deletes every node
 */
void BinaryTree::_destroy(Node* root)
{
    if (!root)
     return;
    
    _destroy(root->getLeftPtr());
    _destroy(root->getRightPtr());
    delete root;
}



Node* BinaryTree::_finder(Movie dataIn, Node* nodePtr)
{
  if(!nodePtr)
    return nullptr;

  if(dataIn > nodePtr->getItem())
   return _finder(dataIn, nodePtr->getRightPtr());
  if(dataIn < nodePtr->getItem())
   return _finder(dataIn, nodePtr->getLeftPtr());
  return nodePtr;

}

void BinaryTree::_remove(Movie dataIn, Node* rt)
{
   Node* locatedNode = _finder(dataIn,rt); 
    if(locatedNode == nullptr)
      return; 
    if(isLeafNode(locatedNode))
    {
      Node* pNode = getParent(locatedNode,root);
      if(pNode->getRightPtr() == locatedNode)
       { 
         pNode->setRightPtr(nullptr);
         delete locatedNode;
       }
       else
        {
          pNode->setLeftPtr(nullptr);
          delete locatedNode;
        }

    }    

 
  if(locatedNode->getRightPtr())               //Internal Node 
     {
	Node* minOrMaxNode = getMin(locatedNode->getRightPtr());
        Movie temp = locatedNode->getItem();
        locatedNode->setItem(minOrMaxNode->getItem());
        minOrMaxNode->setItem(temp);        
        _remove(minOrMaxNode->getItem(), minOrMaxNode);
        return;
     }
   else if(locatedNode->getLeftPtr())
     {
        Node* minOrMaxNode = getMax(locatedNode->getLeftPtr());
        Movie temp = locatedNode->getItem();
        locatedNode->setItem(minOrMaxNode->getItem());
        minOrMaxNode->setItem(temp);        
	_remove(minOrMaxNode->getItem(), minOrMaxNode);
        return;
     }
    else
       {
        return;
       } 
    
}


Node* BinaryTree::getMax(Node* nodePtr)
{
    if(nodePtr->getRightPtr() == nullptr)
      return nodePtr;
    else
     return getMax(nodePtr->getRightPtr());
}

Node* BinaryTree::getMin(Node* nodePtr)
{
    
    if(nodePtr->getLeftPtr() == nullptr)
     return nodePtr;
    else
     return getMin(nodePtr->getLeftPtr());
}

bool BinaryTree::remove(Movie dataIn)
{
   count--;
   _remove(dataIn, root);
   return true;
}

Node* BinaryTree::getParent(Node* child, Node* rt)
{
   if(!rt)
     return nullptr;
   Node* parentNode = rt;
   if(rt->getRightPtr() && rt->getRightPtr()->getItem().getID() == child->getItem().getID())
     return parentNode;
   if(rt->getLeftPtr() && rt->getLeftPtr()->getItem().getID() == child->getItem().getID())
     return parentNode;
   if(getParent(child, parentNode->getRightPtr()))
     return getParent(child,parentNode->getRightPtr());
   return getParent(child, parentNode->getLeftPtr());
}

vector<Movie> BinaryTree::DFS(std::string title)
{
  std::stack<Node*> stck;
  std::vector<Movie> movieList;
  stck.push(root);
  _dfs(stck, title, movieList);
  return movieList;
}

void BinaryTree::_dfs(std::stack<Node*>& stk, string title, std::vector<Movie>& list)
{
   while(!stk.empty())
   {
     Node* nodeptr = stk.top();
     stk.pop();
     if(nodeptr->getItem().getTitle() == title)
        list.push_back(nodeptr->getItem());
     if(nodeptr->getRightPtr())
      {
       stk.push(nodeptr->getRightPtr()); 
       _dfs(stk, title, list);
      }
     if(nodeptr->getLeftPtr())
       stk.push(nodeptr->getLeftPtr());
       _dfs(stk, title, list);
   }

}
