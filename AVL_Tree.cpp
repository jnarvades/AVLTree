//avltree.cpp
#include "AVL_Tree.h"

int AVL_Tree::getHeight(Node* node)
{
  if (node == nullptr) {
        return 0;
    } else {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        // Return the maximum of left and right subtree heights plus one (for the current node)
        return std::max(leftHeight, rightHeight) + 1;
  }
}

Node* AVL_Tree::leftRotate(Node* root, Node* parent)
{
  bool rootRotated = false;
  if (root->getGatorID() == getRoot()->getGatorID()) {rootRotated = true;}
  Node* newRoot = root->right;
  root->right = newRoot->left;
  root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
  newRoot->left = root;
  newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight
  (newRoot->right));

  // Calculate balance factors
  root->balanceFactor = getHeight(root->left) - getHeight(root->right);
  newRoot->balanceFactor = getHeight(newRoot->left) - getHeight(newRoot->right);

  //reattach new root to tree
  if (rootRotated) {setRoot(newRoot);} 
  else 
  {
    if (parent->left == root) {
      parent->left = newRoot;
    } else {
      parent->right = newRoot;
    }
  }
  return newRoot;
}

// Perform right rotation.
Node* AVL_Tree::rightRotate(Node* root, Node* parent)
{
  bool rootRotated = false;
  if (root->getGatorID() == getRoot()->getGatorID()) {rootRotated = true;}
  Node* newRoot = root->left;
  root->left = newRoot->right;
  root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
  newRoot->right = root;
  newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

  // Calculate balance factors
  root->balanceFactor = getHeight(root->left) - getHeight(root->right);
  newRoot->balanceFactor = getHeight(newRoot->left) - getHeight(newRoot->right);

  //reattach new root to tree
  if (rootRotated) {setRoot(newRoot);} 
  else //newroot != getroot
  {
    if (parent->left == root) {
      parent->left = newRoot;
    } else {
      parent->right = newRoot;
    }
  }

  return newRoot;
}

// Left-Right Rotation
Node* AVL_Tree::leftRightRotate(Node* root, Node* parent) {
    // Perform a left rotation on the left child (node->left)
    root->left = leftRotate(root->left, root);
    // Perform a right rotation on the root (node)
    return rightRotate(root, parent);
}

// Right-Left Rotation
Node* AVL_Tree::rightLeftRotate(Node* root, Node* parent) {
    // Perform a right rotation on the right child (node->right)
    root->right = rightRotate(root->right, root);
    // Perform a left rotation on the root (node)
    return leftRotate(root, parent);
}

void AVL_Tree::insert(Node*& root, Node* node, Node* parent)
{
  if (root == nullptr) {
    root = node;
    if (!rooted) {setRoot(node); rooted = true;}
  }

  else if (node->getGatorID() < root->getGatorID()) {
    if (root->left == nullptr) {root->left = node;}
    else {insert(root->left, node, root);}
  }

  else if (node->getGatorID() > root->getGatorID()) {
    if (root->right == nullptr) {root->right = node;}
    else {insert(root->right, node, root);}

  } else {
    //gatorID already exists
  }
  // Update the height of the current node
  root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
  balance(root, parent);
}

void AVL_Tree::searchID(Node* root, int& gatorID)
{
  if (root == nullptr) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }

  if (gatorID < root->getGatorID()) {
    searchID(root->left, gatorID);
  } 
  
  else if (gatorID > root->getGatorID()) {
    searchID(root->right, gatorID);

  } else {
    std::cout << root->getName() << std::endl;
    return;
  }

}

void AVL_Tree::searchName(Node* root, std::string& name, bool& found)
{
  if (root == nullptr) {
    return;
  }

  searchName(root->left, name, found);

  if (root->getName() == name) {
    std::cout << root->getGatorID() << std::endl;
    found = true;
  }

  searchName(root->right, name, found);
}

void AVL_Tree::printInorder(Node* root, bool& first)
{
  if (root == nullptr) {
    return;
  }
  
  printInorder(root->left, first);

  //excludes comma from the last name
  if (!first) {std::cout << ", ";} else {first = false;}
  std::cout << root->getName();

  printInorder(root->right, first);
}

void AVL_Tree::printPreorder(Node* root, bool& first)
{
  if (root == nullptr) {
    return;
  }

  //excludes comma from the last name
  if (!first) {std::cout << ", ";} else {first = false;}
  std::cout << root->getName();

  printPreorder(root->left, first);
  printPreorder(root->right, first);
}

void AVL_Tree::printPostorder(Node* root, bool& first)
{
  if (root == nullptr) {
    return;
  }
  
  printPostorder(root->left, first);
  printPostorder(root->right, first);

  //excludes comma from the last name
  if (!first) {std::cout << ", ";} else {first = false;}
  std::cout << root->getName();
}

void AVL_Tree::remove(Node* root, int gatorID, Node* parent)
{
  if (root == nullptr) {
    std::cout << "unsuccessful" << std::endl;
    return;
  }

  if (gatorID < root->getGatorID()) {
    remove(root->left, gatorID, root);
  } 

  else if (gatorID > root->getGatorID()) {
    remove(root->right, gatorID, root);

  } else {   
    if (root->left != nullptr && root->right != nullptr)
    { 
      Node* successor = root->right;
      Node* successorParent = root;
      while (successor->left != nullptr) {
          successorParent = successor;
          successor = successor->left;
      }

      if (root->getGatorID() != getRoot()->getGatorID())
      {  // Connect the successor to the parent
        if (parent->left == root) {
          parent->left = successor;
        } else {
          parent->right = successor;
        }
      } else {
        setRoot(successor);
      }

      // Update the successor's children
      successor->left = root->left;
      // If the successor is not the immediate right child of the root,
      // update its parent's left link and the successor's right link
      if (successor != successorParent->right) {
        successorParent->left = successor->right;
        successor->right = root->right;
      }
      // Delete the root node
      root->setGatorID(0);
      root->setName("");
      root->left = nullptr;
      root->right = nullptr;
      delete root;
      balance(root, parent);
    }

    else if (root->left != nullptr)
    {
      //replace with child, P-C = C-L
      if (parent->left == root) {parent->left = root->left; delete root;}
      else {parent->right = root->left; delete root;}
    }

    else if (root->right != nullptr)
    {
      //replace with child, P-C = C-R
      if (parent->left == root) {parent->left = root->right; delete root;}
      else {parent->right = root->right; delete root;}
    }

    else
    {
      if (parent->left == root) {parent->left = nullptr; delete root;}
      else {parent->right = nullptr; delete root;}
    }
    std::cout << "successful" << std::endl;
    return;
  }
}

void AVL_Tree::removeInorderN(Node* root, int n) 
{
  //using a stack to count up inOrder
  std::stack<Node*> s;
  Node* current = root;
  Node* parent = nullptr;
  Node* temp = nullptr;
  bool found = false;
  int count = 0;
  ++n;
  while (!s.empty() || current) {
      if (current) {
          s.push(current);
          current = current->left;
      } else {
          Node* node = s.top();
          s.pop();
          count++;
          if (count == n) {
            root = node;
              // seek parent node from top through bst search
            temp = getRoot();
            while (!found) {
              if (root->getGatorID() < temp->getGatorID()) {
                parent = temp;
                temp = temp->left;
              } 
              
              else if (root->getGatorID() > temp->getGatorID()) {
                parent = temp;
                temp = temp->right;

              } else {
                remove(root, root->getGatorID(), parent);
                return;
              }
            }
          }
        current = node->right;
      }
  }
  std::cout << "unsuccessful" << std::endl;
}

void AVL_Tree::balance(Node*& root, Node* parent) {
    // Update balance factor
    root->balanceFactor = getHeight(root->right) - getHeight(root->left);

    if (root->balanceFactor > 1) {
        // Right heavy
        if (root->right->balanceFactor < 0) {
            // Right-Left Rotation
            root = rightLeftRotate(root, parent);
        } else {
            // Left Rotation
            root = leftRotate(root, parent);
        }
    } else if (root->balanceFactor < -1) {
        // Left heavy
        if (root->left->balanceFactor > 0) {
            // Left-Right Rotation
            root = leftRightRotate(root, parent);
        } else {
            // Right Rotation
            root = rightRotate(root, parent);
        }
    }
}


void AVL_Tree::printLevelOrder(Node* root) {
    // Base Case
    if (root == NULL)
        return;

    // Create an empty queue for level order traversal
    std::queue<Node*> q;

    // Enqueue Root and initialize height
    q.push(root);

    while (q.empty() == false) {
        int size = q.size(); // Store the number of nodes at this level

        // Print nodes at the current level
        for (int i = 0; i < size; i++) {
            // Print front of queue and remove it from queue
            Node* node = q.front();
            std::cout << node->getName() << "(" << getHeight(node) << ")" << "(" << node->balanceFactor << ") ";
            q.pop();

            // Enqueue left child
            if (node->left != NULL)
                q.push(node->left);

            // Enqueue right child
            if (node->right != NULL)
                q.push(node->right);
        }

        std::cout << std::endl << std::endl; // Move to the next level
    }
}

