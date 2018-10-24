

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

TreeNode* Tree::RotateRight(TreeNode*& n){
  TreeNode* child = n->left;
  n->left = child->right;
  child->right = n;
  n->height = updateHeight(n);
  child->height = updateHeight(child);
  child->right->height = updateHeight(child->right);
  return child;
}


TreeNode* Tree::RotateLeftRight(TreeNode*& n){
  TreeNode* child = n->left;
  n->left = RotateLeft(child);
  n->height = updateHeight(n);
  n->left->height = updateHeight(n->left);
  child->height = updateHeight(child);
  return RotateRight(n);
}

TreeNode* Tree::RotateRightLeft(TreeNode*& n){
  TreeNode* child = n->right;
  n->right = RotateRight(child);
   n->height = updateHeight(n);
   n->right->height = updateHeight(n->right);
  child->height = updateHeight(child);
  return RotateLeft(n);
}

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
    else {
      n = RotateRightLeft(n);
    }
  }
}

int Tree::updateHeight(TreeNode* n){
  if (n==nullptr){ //base case 
    return 0;
  }
  else { //recursive case
    return max(updateHeight(n->left), updateHeight(n->right))+1;
  }
}
int Tree::max(int left_height, int right_height){
  if(left_height > right_height){
    return left_height;
  }
  else {
    return right_height;
  }
}

void Tree::InOrder(TreeNode* head){ //recursevely
  if(head->left != nullptr){
    InOrder(head->left);
  }
    cout << head->value << endl;
  if (head->right != nullptr){
    InOrder(head->right);
  }
}

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

