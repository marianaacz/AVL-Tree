#ifndef TREE_H
#define TREE_H


class  TreeNode {
  public:
  TreeNode *left;
  TreeNode *right;
  int value;
  TreeNode(int);
  int height;
};

class Tree {
  public:
  Tree();
  TreeNode *root;
  void DataIn(TreeNode*& head, int data);
  void InOrder(TreeNode* head);
  void PreOrder(TreeNode* head);

  void Balance(TreeNode*& n);
  int updateHeight(TreeNode *n);
  TreeNode* RotateLeft(TreeNode*& n);
  TreeNode* RotateRight(TreeNode*& n);
  TreeNode* RotateLeftRight(TreeNode*& n);
  TreeNode* RotateRightLeft(TreeNode*& n);
  int max(int left_height, int right_height);
  int checkDifference(TreeNode* n);


};

#endif
