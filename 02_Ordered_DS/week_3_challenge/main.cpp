/*

Coursera - Ordered Data Structures
Week 3 Challenge.

The height of a node is the number of edges in
its longest chain of descendants.

Implement computeHeight to compute the height
of the subtree rooted at the node n. Note that
this function does not return a value. You should
store the calculated height in that node's own
height member variable. Your function should also
do the same for EVERY node in the subtree rooted
at the current node. (This naturally lends itself
to a recursive solution!)

*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

class Node {
public:
  int height; // to be set by computeHeight()
  Node *left, *right;
  Node() { height = -1; left = right = nullptr; }
  ~Node() {
    delete left;
    left = nullptr;
    delete right;
    right = nullptr;
  }
};

void computeHeight(Node *n) {

  // If leaf
  if (n->left == nullptr && n->right == nullptr) {
    n->height = 0;
  } else { // Not leaf

    int h_left_child = -1; // no left child
    int h_right_child = -1; // no right child
    if (n->left) {// left exists
      // Recursively go to the deepest nodes = leaves
      computeHeight(n->left);
      // After deepest nodes (= leaves) found
      // we can get the height of the child
      h_left_child = n->left->height;
    }
    if (n->right) {// right exists
      computeHeight(n->right);
      // After deepest nodes (= leaves) found
      // we can get the height of the child
      h_right_child = n->right->height;
    }

    // Here, we are not leaf and the height of all
    // sub-nodes has been computed
    if (h_left_child >= h_right_child)
      n->height = h_left_child + 1;
    else
      n->height = h_right_child + 1;

  }

}

// This function prints the tree in a nested linear format.
void printTree(const Node *n) {
  if (!n) return;
  std::cout << n->height << "(";
  printTree(n->left);
  std::cout << ")(";
  printTree(n->right);
  std::cout << ")";
}

// The printTreeVertical function gives you a verbose,
// vertical printout of the tree, where the leftmost nodes
// are displayed highest. This function has already been
// defined in some hidden code.
// It has this function prototype: void printTreeVertical(const Node* n);

// This main() function is for your personal testing with
// the Run button. When you're ready, click Submit to have
// your work tested and graded.
int main() {
  Node *n = new Node();
  n->left = new Node();
  n->right = new Node();
  n->right->left = new Node();
  n->right->right = new Node();
  n->right->right->right = new Node();

  computeHeight(n);

  printTree(n);
  std::cout << std::endl << std::endl;
  //printTreeVertical(n);
  
  // The Node destructor will recursively
  // delete its children nodes.
  delete n;
  n = nullptr;

  return 0;
}
