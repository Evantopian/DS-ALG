#include <iostream>
#include <string>
#include <algorithm>
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
    return std::to_string(st->getData()) + " ->(" + traverse(st->getLeft()) + ")" +
           "->(" + traverse(st->getRight()) + ")";
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


int BSTree::search(int value) {
  Node * t = root;

  while (t != nullptr) {
    int tval = t->getData();
    if (tval == value) {
      // here we'd really return a full object
      // with all the stuff associated with value
      // not just an int
      return value;
    }

    if (tval < value) {
      t = t->getRight();
    } else {
      t = t->getLeft();
    }

  }

  // if we get here then the value isn't
  // in the tree

  // normally, if we had a tree of objects
  // we could return null but since we only have
  // an int, we can't return an int to represent
  // not found so we'll throw an exception

  throw 1; // we should define our exceptions.
}

int BSTree::rsearch(int value, Node * n) {
  if (n == nullptr) {
    throw 3;
  } // If n becomes nullptr, throw exception.

  int data = n->getData();
  if (value == data) {
    return data;
  } // Just return data if the value is equal to the node's current data.

  else if (value < data) {
    return rsearch(value, n->getLeft());
  } // Search left subtree to check if value is less than that node's value.

  else {
    return rsearch(value, n->getRight());
  } // Search right subtree to check if value is greater than that node's value.

}

int BSTree::rsearch(int value) {
  return rsearch(value, root);
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
  } else {
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
}


void BSTree::delete_node(int x) {
  remove(x);
}

int BSTree::leaves(Node * n, int cnt) {
  if (n == nullptr) return 0;

  if (n->getLeft() == nullptr && n->getRight() == nullptr) {
    return 1;
  }
  return leaves(n->getLeft(), cnt) + leaves(n->getRight(), cnt);
}


int BSTree::count_leaves() {
  return leaves(root, 0);
}

int BSTree::height(Node *n){
  if (n == nullptr) return 0;
  
  int l = height(n->getLeft());
  int r = height(n->getRight());
  
  return l > r ? l + 1 : r + 1;

}

int BSTree::height() {
  return height(root);  
}

int BSTree::sum_lvl(Node * n, int curr, int x) {
  if (n == nullptr) return 0;
  if (curr == x) return n->getData();

  return sum_lvl(n->getLeft(), curr + 1, x) + sum_lvl(n->getRight(), curr + 1, x);
}

int BSTree::sum_level(int x) {
  if (root == nullptr) throw 1;
  if (x < 0 || height() < x) throw 2;

  return sum_lvl(root, 1, x);
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
