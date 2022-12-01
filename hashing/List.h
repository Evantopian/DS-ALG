#pragma once
#include "Node.h"

class List{
 private:
  Node *head;
  int size = 0;

 public:
  List();
  ~List();
  
  void insert(Person *p);
  std::string toString();
  Node * locate(int index);
  void remove(int index);
  Node * get_head();
  
  int get_size();


};
