#include <iostream>
#include "queue.h"

Queue::Queue(){
  max_size = 5;
  q = new int[max_size];
  head = 0;
  tail = 0;
}

Queue::~Queue(){
  delete q;
}


void Queue::enqueue(int data){
  if (!is_full()){
    q[tail%max_size] = data;
    tail++;
  }
  else{
    throw 2; 
  }
}


int Queue::dequeue(){
  if (is_empty()) throw 1;
  int x = q[head%max_size];
  head++; 

  return x;
}


int Queue::front(){
  if (!is_empty()) return q[head];
  throw 1;
}


bool Queue::is_empty(){
  return head == tail;
}


bool Queue::is_full(){
  if (tail - head == max_size) return true;
  return false;
}
