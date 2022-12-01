#include <iostream>
#include "Node.h"
#include "BSTree.h"


BSTree::BSTree() {
  root = nullptr;
}


std::string BSTree::traverse(Node * st) {
  // traverse left subtree then right subtree, build recurisvely.
  if (st == nullptr) {
    return "";
  }
  // parentheses to show subtree.
  else {
    return std::to_string(st->getData()) + " -> (" + traverse(st->getLeft()) + ") " +
           "(" + traverse(st->getRight()) + ")";
  }
}

Node * BSTree::get_root() {
  return root;
}

std::string BSTree::get_debug_string() {
  if (root != nullptr) {
    return traverse(root) + "nullptr";
  }
  return nullptr;
}

void BSTree::insert(int value) {
  Node * newnode = new Node(value);

  Node * p = root;
  Node * trailer;

  while (p != nullptr) {
    trailer = p;
    if (p->getData() == value) {
      return;
    } else if (p->getData() < value) {
      p = p->getRight();
    } else {
      p = p->getLeft();
    }
  }

  if (root == nullptr) {
    root = newnode;
  } else {
    if (trailer->getData() < value) {
      trailer->setRight(newnode);
    } else {
      trailer->setLeft(newnode);
    }
  }
}


Node * BSTree::search_node(Node * n, int x, bool p) {
  if (n->getData() != x && n != nullptr) {

    if (p) {
      if (n->getLeft()->getData() == x ||
          n->getRight()->getData() == x) return n;
    }

    n = n->getData() > x ? search_node(n->getLeft(), x, p) :
        search_node(n->getRight(), x, p);
  }
  return n;
}


// toggles for parent and child node.
Node * BSTree::searchR(int x) {
  return search_node(root, x, false);
}

// p = parent node
// c = child node to delete





void BSTree::remove(int x) {
  // p = parent node, c = child node.
  Node * c = search_node(root, x, false);
  Node * p = search_node(root, x, true);

  // case #1: no child node
  if (c->getLeft() == c->getRight()) {
    if (p->getData() < c->getData()) {
      p->setRight(nullptr);
    } else {
      p->setLeft(nullptr);
    }

    p = nullptr, c = nullptr;
    delete c;
    delete p;

    return;
  }
  // case #3 (needs to be cleaned a bit)
  else if (c->getLeft() != nullptr && c->getRight() != nullptr) {
    Node * tmp = p;
    while (p->getRight()->getRight() != nullptr) {
      c = p->getRight();
      p = p->getRight();
    }

    c = p->getLeft();
    Node * p1 = p;
    p = tmp;

    p->getRight()->setData(c->getData());
    p1->setLeft(nullptr);
    return;
  }
  // case 2:
  c = c->getLeft() != nullptr ? c->getLeft() : c->getRight();
  if (p->getLeft()->getData() == x) {
    p->setLeft(nullptr);
    p->setLeft(c);
  } else {
    p->setRight(nullptr);
    p->setRight(c);
  }
  p = nullptr, c = nullptr;
  delete c;
  delete p;
}



void BSTree::delete_node(int x) {
  remove(x);
}


void BSTree::setup() {
  Node * n = new Node(20);
  root = n;

  n = new Node(18);
  root->setLeft(n);

  Node * n2 = new Node(15);
  n->setLeft(n2);


  n2 = new Node(12);
  n->getLeft()->setLeft(n2);

  n2 = new Node(40);
  n->setRight(n2);

  n2 = new Node(25);
  n->getRight()->setLeft(n2);

  n2 = new Node(55);
  n->getRight()->setRight(n2);

  n2 = new Node(50);
  root->setRight(n2);

  n = new Node(35);
  n2->setLeft(n);

  n = new Node(70);
  n2->setRight(n);
}
