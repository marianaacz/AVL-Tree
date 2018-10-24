// Author:       Mariana Acosta
// Assignment:       project 4
// File:       Tree
// Instructor:       Reza Sanati
// Class:       CSIS 2420  Section: 001
// Date Written:   June 2, 2018
// Description: get data from file, then construct an avl tree, in order recursevely and pre order non recursevely

#include <iostream>
#include "Tree.h"
#include <stack>
using namespace std;

//TreeNode constructor
TreeNode::TreeNode(int v) {
  value = v;
  left = nullptr;
  right = nullptr;
  height = 0;
}
//tree constructor 
Tree::Tree()
{
  root = nullptr;
}
// Function Name:    RotateLeft
// Purpose:       rotate the data to balance it out 
// Parameters:       TreeNode*& n
// Returns:       child
// Pre-conditions:   none
// Post-conditions:none

TreeNode* Tree::RotateLeft(TreeNode*& n){
  TreeNode* child = n->right;
  n->right = child->left;
  child->left = n;
  n->height = updateHeight(n);
  child->height = updateHeight(child);
  child->left->height = updateHeight(child->left);
  return child;
}

// Function Name:    RotateRight
// Purpose:       rotate the data to balance it out 
// Parameters:       TreeNode*& n
// Returns:       child
// Pre-conditions:   none
// Post-conditions:none
TreeNode* Tree::RotateRight(TreeNode*& n){
  TreeNode* child = n->left;
  n->left = child->right;
  child->right = n;
  n->height = updateHeight(n);
  child->height = updateHeight(child);
  child->right->height = updateHeight(child->right);
  return child;
}

// Function Name:    RotateLeftRight
// Purpose:       rotate the date to balance it out 
// Parameters:       TreeNode*& n
// Returns:       child
// Pre-conditions:   none
// Post-conditions:none
TreeNode* Tree::RotateLeftRight(TreeNode*& n){
  TreeNode* child = n->left;
  n->left = RotateLeft(child);
  n->height = updateHeight(n);
  n->left->height = updateHeight(n->left);
  child->height = updateHeight(child);
  return RotateRight(n);
}

// Function Name:    RotateRightLeft
// Purpose:       rotate the date to balance it out 
// Parameters:       TreeNode*& n
// Returns:       child
// Pre-conditions:   none
// Post-conditions:none
TreeNode* Tree::RotateRightLeft(TreeNode*& n){
  TreeNode* child = n->right;
  n->right = RotateRight(child);
   n->height = updateHeight(n);
   n->right->height = updateHeight(n->right);
  child->height = updateHeight(child);
  return RotateLeft(n);
}

// Function Name:    DataIn
// Purpose:       insert the data and accomodate it  
// Parameters:       TreeNode*& head, and int data 
// Returns:      none
// Pre-conditions:   if there are two equal numbers ignore one, 
// if the head is null new node is the head, if there is a head and it is bigger put it to the right if it is less put it to the right
// Post-conditions:none
void Tree::DataIn(TreeNode*& head, int data) {
  //if there are two equal numbers ignore one
        if (head != nullptr && data == head->value){
          return;
        }
        //if the head is null new node is the head
        if(head == nullptr) {
          head = new TreeNode(data);
    
        }
        //if there is a head and it is smaller put it to the left
        else if(head->value > data){
          DataIn(head->left, data);
          
        }
        //if there is a head and it is bigger put it to the right
        else if(head->value < data){
          DataIn(head->right, data);
          
        }
        //update the height and equal it to checkDifference,
        //if height is more than one and less than -1 then balance it out 
        head->height = updateHeight(head);
        int heightDifference = checkDifference(head);
        if (heightDifference > 1 || heightDifference < -1){
          Balance(head);
        }

}

// Function Name:    Balance
// Purpose:       see the height check the difference and balance it out if needed 
// Parameters:       TreeNode*& n
// Returns:      none
// Pre-conditions:   if the height is more than one there are two options, if heightDifference is more than 0 rotate it right, else then RotateLeftRight, if heightDifference is less than -1 two options again, if it is less than 0 RotateLeft if not RotateRightLeft
// Post-conditions:none
void Tree::Balance(TreeNode*& n){
  int heightDifference = checkDifference(n);
  //if it is more than one then put it to the left 
  if (heightDifference > 1){
    heightDifference = checkDifference(n->left);
    //if it is more than 0  then RotateRight
    if (heightDifference > 0){
      n = RotateRight(n);
    }
    //if not RotateLeftRight
    else {
      n = RotateLeftRight(n);
    }
  }
  // if it is less than -1 then move it to the right
  else if(heightDifference < -1){
    heightDifference = checkDifference(n->right);
    //if more less than 0 RotateLeft
    if (heightDifference < 0){
      n = RotateLeft(n);
    }
    //else RotateRightLeft
    else {
      n = RotateRightLeft(n);
    }
  }
}
// Function Name:    updateHeight
// Purpose:       updates the height of the tree 
// Parameters:       TreeNode*& n
// Returns:       0 or the max 
// Pre-conditions:   if n is null then return 0, else max takes the updateHeight of left and right plus one 
// Post-conditions:none
int Tree::updateHeight(TreeNode* n){
  if (n==nullptr){ //base case 
    return 0;
  }
  else { //recursive case
    return max(updateHeight(n->left), updateHeight(n->right))+1;
  }
}

// Function Name:    max
// Purpose:       see the max height 
// Parameters:      int left_height, int right_height
// Returns:      left_height or  right_height
// Pre-conditions:   if the left heightis bigger than the right one return the left one, else return the right one 
// Post-conditions:none
int Tree::max(int left_height, int right_height){
  if(left_height > right_height){
    return left_height;
  }
  else {
    return right_height;
  }
}

// Function Name:    InOrder
// Purpose:      if left is null then go left, and output the value, if right is null, go right 
// Parameters:      TreeNode* head
// Returns:      none
// Pre-conditions:  if left or right are null 
// Post-conditions:none
void Tree::InOrder(TreeNode* head){ //recursevely
  if(head->left != nullptr){
    InOrder(head->left);
  }
    cout << head->value << endl;
  if (head->right != nullptr){
    InOrder(head->right);
  }
}

// Function Name:    checkDifference
// Purpose:     see the difference between heights to see if it is balanced or not 
// Parameters:      TreeNode* n
// Returns:      the heights or 0 
// Pre-conditions:  if both are null then return the difference, if one is bigger return the heights 
// Post-conditions:none
int Tree::checkDifference(TreeNode* n){
  if(n->left != nullptr && n->right != nullptr){
    return (n->left->height) - (n->right->height);
  }
  else if(n->left != nullptr){
    return n->left->height;
  }
  else if(n->right != nullptr){
    return -(n->right->height);
  }
  else {
    return 0;
  }
}

// Function Name:    PreOrder
// Purpose:    order it in pre order form 
// Parameters:      TreeNode* head
// Returns:      the heights or 0 
// Pre-conditions:  if the head is null then do everything 
// Post-conditions:none
void Tree::PreOrder(TreeNode* head){
  if (head == nullptr)
    return;
    // Create an empty stack and push head to it
    stack<TreeNode*> TreeNodes;
    TreeNodes.push(head);
    /* Pop all items one by one. Do following for every popped item, print it, push its right child, push its left child
    Note that right child is pushed first so that left is processed first */
    while (TreeNodes.empty() == false)
    {
        // Pop the top item from stack and print it
        TreeNode *node = TreeNodes.top();
        cout << node->value << endl;
        TreeNodes.pop();
 
        // Push right and left children of the popped node to stack
        if (node->right)
            TreeNodes.push(node->right);
        if (node->left)
            TreeNodes.push(node->left);
    }
}

