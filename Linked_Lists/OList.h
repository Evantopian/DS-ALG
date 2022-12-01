#pragma once
#include "Node.h"

class OList {
  private:
  Node * head;

  public:
  OList();
  ~OList();

  void insert(int data);
  void remove (int index);
  bool contains(int data);

  int get(int index);

  std::string toString();

  void reverse();
};
