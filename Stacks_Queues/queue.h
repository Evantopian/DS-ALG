#pragma once
#include "Node.h"

#define QUEUE_ERR_EMPTY 1
#define QUEUE_ERR_FULL 2

class Queue{
 private:
  int max_size;
  int head;
  int tail;
  int *q;

 public:
  Queue();
  ~Queue();

  void enqueue(int val); // add a value to the back of the queue
  int dequeue(); // remove and return the item from the front of the queue
  int front(); // return but do not remove the item from the front of the queue
  bool is_empty(); // checks and returns if the queue is empty
  bool is_full(); // checks and returns if the queue is full
};
