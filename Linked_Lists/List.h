#pragma once
#include <iostream>
#include "Node.h"

class List{
 private: Node *head;

 public:
  List();
  ~List();

  void insert(int  data);
  void insert(int loc, int  data);

  void remove(int loc);
  
  int  get(int loc);

  int length();

  std::string toString();  
};
