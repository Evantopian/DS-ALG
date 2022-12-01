#include <iostream>
#include "Node.h"
#include "BSTree.h"

int main(){

  BSTree *bst = new BSTree();
  
  bst->insert(5);
  bst->insert(2);
  bst->insert(12);
  bst->insert(-4);
  bst->insert(4);
  bst->insert(3);
  bst->insert(9);
  bst->insert(21);
  bst->insert(19);
  bst->insert(25);


  std::cout << bst->get_debug_string() << std::endl;
  //std::cout << bst->searchR(-4)->getData() << "\n";
  bst->delete_node(4);
  std::cout << bst->get_debug_string() << std::endl;

  /*
  Node *root = new Node(0);
 
  Node *n = new Node(10);
  root->setLeft(n);

  n = new Node(50);
  root->setRight(n);
  
  std::cout << root->getData() << "\n";
  std::cout << root->getLeft()->getData() << " | " << 
               root->getRight()->getData() << std::endl;

  n = new Node(20);
  root->getLeft()->setLeft(n);
  
  n = new Node(60);
  root->getRight()->setRight(n);
*/
}
