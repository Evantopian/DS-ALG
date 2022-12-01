#include <iostream>
#include "Node.h"

Node::Node() : next(nullptr){
}

Node::Node(Person *p){
  this->person = p;
  this->next = nullptr;
}

Node::~Node(){
  delete person;
}

Node::Node(Person *p, Node *next){
  this->person = p;
  this->next = next;
}

void Node::setPerson(Person *p){
  this->person = p;
}

void Node::setNext(Node *next){
  this->next = next;
}

Person *Node::getPerson(){
  return this->person;
}

Node *Node::getNext(){
  return this->next;
}
