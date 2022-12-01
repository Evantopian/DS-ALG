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
  //bst->delete_node(4);
  bst->delete_node(3);
  bst->delete_node(19);
  bst->delete_node(-4);
  bst->insert(17);
  bst->insert(1);
  bst->insert(-2);


  std::cout << bst->get_debug_string() << std::endl;
  std::cout << "Leaves: " << bst->count_leaves() << std::endl;
  std::cout << "Height: " << bst->height() << std::endl;
  std::cout << "SumLvl: " << bst->sum_level(3) << std::endl; 

}
