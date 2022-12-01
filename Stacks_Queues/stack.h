#pragma once
#include <iostream>
#include "OList.h"

#define STACK_ERR_EMPTY 1

class Stack{
  private:
    int data, size;
    OList *ll;

  public:
    Stack();
    ~Stack();

    void push(int data);
    int pop();
    int top();
    int getSize();
    
    bool is_empty();
};
