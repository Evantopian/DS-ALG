#include <iostream>
#include <stdexcept>
#include "List.h"


List::List() {
  head = nullptr;
}

List::~List() {
  Node *trailer = nullptr;

  while (head != nullptr) {
    trailer = head;
    head = head->getNext();
    delete trailer;
  }
}

void List::insert(int data) {
  Node *walker = head;
  Node *trailer = nullptr;
  Node *tmp = new Node(data);

  while (walker != nullptr && data > walker->getData()) {
    trailer = walker;
    walker = walker->getNext();
  }

  if (trailer == nullptr) {
    tmp->setNext(head);
    head = tmp;
  } else {
    trailer->setNext(tmp);
    tmp->setNext(walker);
  }

  return;
}


std::string List::toString() {
  std::string result = "head --> ";
  Node * walker = this->head;

  while (walker != nullptr) {
    result += std::to_string(walker->getData());
    result += " --> ";
    walker = walker->getNext();
  }

  result = result + "nullptr";
  return result;
}

int List::get(int index) {
  Node *walker = head;

  while (walker && index > 0) {
    walker = walker -> getNext();
    index--;
  }

  if (walker != nullptr) {
    return walker->getData();
  }

  return -1;
}

void List::remove(int index) {
  Node *walker = head;
  Node *trailer = nullptr;

  while (index > 0 && walker != nullptr) {
    trailer = walker;
    walker = walker->getNext();
    index = index - 1;
  }

  if (walker == nullptr) {
    throw std::out_of_range("out of range");
  }

  if (trailer == nullptr) {
    head = walker->getNext();
    delete walker;
  } else {
    trailer->setNext(walker->getNext());
    delete walker;
  }
}

