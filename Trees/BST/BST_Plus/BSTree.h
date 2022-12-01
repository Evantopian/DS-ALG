#pragma once
#include <iostream>
#include <vector>
#include "Node.h"


#define BST_EMPTY 1
#define BST_BOUNDS 2
#define BST_NO_VAL 3


class BSTree {
  private:
  Node * root;

  public:
  BSTree();

  std::string traverse(Node * st);
  std::string get_debug_string();

  int count_leaves();
  int leaves(Node * n, int x);

  int height(Node *n);
  int height();

  int search(int x);
  int rsearch(int x);
  int rsearch(int x, Node * n);

  int sum_lvl(Node * n, int curr, int x);
  int sum_level(int x);


  void delete_node(int x);
  void remove(int x);
  void insert(int x);


  Node * search_node(Node * n, int x, bool parent);
  Node * searchR(int x);
  Node * get_root();

  void setup();
};
