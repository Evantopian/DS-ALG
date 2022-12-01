#include <iostream>
#include "List.h"

List::List() {
  head = nullptr;
}

List::~List() {
  Node * walker = head;

  while (walker != nullptr) {
    Node * current = walker;
    walker = walker->getNext();
    delete current;
  }

  head = nullptr;
}

void List::insert(Person * p) {
  Node * new_node = new Node(p);
  new_node->setNext(head);
  head = new_node;
  size++;
}


Node * List::locate(int index) {
  int counter = 0;
  Node * walker = head;

  while (walker != nullptr && counter < index) {
    walker = walker->getNext();
    counter++;
  }
  return walker;
}

void List::remove(int index) {
  Node * walker = head;
  int counter = 0;
  while (counter < index - 1) {
    walker = walker->getNext();
    counter++;
  }
  Node * removing = walker->getNext();
  walker->setNext(removing->getNext());
  delete removing;
  size--;

  return;
}

std::string List::toString() {
  if (head == nullptr) {
    return "";
  }

  Node * walker = head;
  std::string s = "";
  while (walker != nullptr) {
    s = s + " " + walker->getPerson()->get_name() + " (ID: " +
    std::to_string(walker->getPerson()->get_id())+ ") -> ";
    walker = walker->getNext();
  }

  return s;
}


int List::get_size(){
  return size;
}

Node * List::get_head() {
  return head;
}
