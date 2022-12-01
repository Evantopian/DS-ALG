#pragma once
#include <iostream>

// Changed to integers since it's easier to work with.

class Node {
  private:
  int data;
  Node * next;

  public:
  Node();
  Node(int data);
  Node(int data, Node * next);

  void setData(int data);
  void setNext(Node * next);

  int getData();
  Node * getNext();
};
