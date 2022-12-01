#pragma once
#include <iostream>
#include "Node.h"

class BSTree{
 private:
  Node *root;

public:
  BSTree();
 
  std::string traverse(Node * st);
  std::string get_debug_string();

  void delete_node(int x);
  void remove(int x);
  void insert(int val);
  
  Node * search_node(Node * n, int x, bool parent);
  Node * searchR(int x);
  Node * get_root();

  void setup();
};
