#pragma once
#include "Person.h"

class Node{
 private:
  Person *person;
  Node *next;

 public:
  Node();
  Node(Person *p);
  ~Node();
  Node(Person *p, Node *next);

  void setPerson(Person *data);
  void setNext(Node *next);

  Person *getPerson();
  Node *getNext();
};
