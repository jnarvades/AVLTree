#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <sstream>
#include <regex>
#include <string>
#include <vector>
#include <queue>

class Node {

  private:
  std::string _name;
  int _gatorID;
  
  public:
  Node* left;
  Node* right;
  int balanceFactor;
  int height;

  Node(std::string _name = "", int _gatorID = 0, Node* left = nullptr, Node* right = nullptr, int balanceFactor = 0, int height = 0) : _name(_name), _gatorID(_gatorID), left(left), right(right), balanceFactor(balanceFactor), height(height) {}

  std::string getName() const {return _name;}
  int getGatorID() const {return _gatorID;}

  void setName(std::string name){_name = name;}
  void setGatorID(int gatorID){_gatorID = gatorID;}

};

class AVL_Tree : public Node {

  private:
  Node* root = nullptr;
  bool rooted = false;
  int levelCount;
  
  public:
  AVL_Tree(){}

  void insert(Node*& root, Node* node, Node* parent);
  void searchID(Node* root, int& gatorID);
  void searchName(Node* root, std::string& name, bool& found);
  void printInorder(Node* root, bool& first);
  void printPreorder(Node* root, bool& first);
  void printPostorder(Node* root, bool& first);
  void remove(Node* root, int gatorID, Node* parent);
  void removeInorderN(Node* root, int n);
  void balance(Node*& root, Node* parent);
  int getHeight(Node* node);
  int getLevelCount(){return levelCount;}
  Node* getRoot() {return root;}
  Node* leftRotate(Node* root, Node* parent);
  Node* rightRotate(Node* root, Node* parent);
  Node* leftRightRotate(Node* root, Node* parent);
  Node* rightLeftRotate(Node* root, Node* parent);

  void setLevelCount(int _levelCount){levelCount = _levelCount;}
  void setRoot(Node* _root){root = _root;}

  void printLevelOrder(Node* root);

  ~AVL_Tree(){}

};

#endif