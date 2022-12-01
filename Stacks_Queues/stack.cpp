#include <iostream>
#include "stack.h"

Stack::Stack(){
  ll = new OList();
  size = 0;
}


Stack::~Stack(){
  delete ll;
}


void Stack::push(int data){
  ll->insert(data);
  size++;
}


int Stack::pop(){
  if (size == 0) throw 1;

  int x = ll->get(size-1);
  ll->remove(size-1);
  size--;
  return x;
}


int Stack::top(){
  if (size < 0) throw 1; 
  return ll->get(size-1);
}


int Stack::getSize(){
  return size;
}


bool Stack::is_empty(){
  return size == 0;
}






