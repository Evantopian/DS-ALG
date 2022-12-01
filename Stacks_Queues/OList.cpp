#include <iostream>
#include "OList.h"


OList::OList() {
  head = nullptr;
}


OList::~OList() {
  Node * trailer = nullptr;

  while (head != nullptr) {
    trailer = head;
    head = head->getNext();
    delete trailer;
  }
}


void OList::insert(int data) {
  Node * walker = head;
  Node * trailer = nullptr;
  Node * tmp = new Node(data);

  // increasing order.
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
}


std::string OList::toString() {
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


bool OList::contains(int data) {
  Node * walker = head;

  while (walker != nullptr) {
    if (walker->getData() == data) return true;
    walker = walker->getNext();
  }
  return false;
}


int OList::get(int index) {
  Node * walker = head;

  while (walker && index > 0) {
    walker = walker -> getNext();
    index--;
  }

  if (walker != nullptr) {
    return walker->getData();
  }

  return -1;
}

void OList::remove(int index) {
  Node * walker = head;
  Node * trailer = nullptr;

  while (index > 0 && walker != nullptr) {
    trailer = walker;
    walker = walker->getNext();
    index--;
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

void OList::reverse() {
  if (head == nullptr) return;

  Node * walker = head;
  Node * trailer = nullptr;
  Node * tmp = nullptr;

  // tmp is the nodes after walker's current head
  // walker's sets its next trailer (e.g 01 becomes 10)
  // trailer holds nodes of walker allowing walker to become tmp
  // process goes on (e.g 123 -> null(1)(2)(3) -> (2)(3)(1)(null)
  // -> (3)(2)(1)(null) since walker becomes null, the process ends.
  // Reversed.
  while (walker) {
    tmp = walker->getNext();
    walker->setNext(trailer);
    trailer = walker;
    walker = tmp;
  }
  head = trailer;
}
