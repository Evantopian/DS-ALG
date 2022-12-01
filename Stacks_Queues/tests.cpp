#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include "stack.h"
#include "queue.h"


TEST_CASE("Testing push, top, pop, & is_empty") {
  Stack * s = new Stack();

  // push & top
  try {
    s->top();
  } catch (int e) {
    CHECK(e == 1);
  }

  s->push(1);
  CHECK(s->top() == 1);

  s->push(2);
  s->push(3);
  CHECK(s->top() == 3);

  // pop
  s->push(4);
  s->push(5);
  s->push(6);
  s->push(7);

  CHECK(s->top() == 7);
  CHECK(s->pop() == 7);

  CHECK(s->top() == 6);
  CHECK(s->pop() == 6);

  CHECK(s->top() == 5);
  CHECK(s->pop() == 5);

  //is_empty

  int x = s->pop();
  x = s->pop();
  x = s->pop();
  CHECK(!s->is_empty());

  x = s->pop();
  CHECK(s->is_empty());

  try {
    s->pop();
  } catch (int e) {
    CHECK(e == 1);
  }
  delete s;
}


TEST_CASE("Testing enqueue, dequeue, front, is_empty, & is_full") {

  // front, enqueue, & is_empty
  Queue * q = new Queue();
  CHECK(q->is_empty());

  try {
    q->front();
  } catch (int e) {
    CHECK(e == 1);
  }

  q->enqueue(1);
  CHECK(q->front() == 1);
  q->enqueue(2);
  q->enqueue(3);
  CHECK(q->front() == 1);


  // is_full

  q->enqueue(4);
  q->enqueue(5);
  CHECK(q->is_full());

  try {
    q->enqueue(6);
  } catch (int e) {
    CHECK(e == 2);
  }

  // dequeue
  // since q is full:
  q->dequeue();
  CHECK(!q->is_full());

  // making it full again
  q->enqueue(5);
  CHECK(q->is_full());

  for (int i = 0; i < 5; i++) q->dequeue();
  CHECK(q->is_empty());

  try {
    q->dequeue();
  } catch (int e) {
    CHECK(e == 1); // Use QUEUE_ERR_EMPTY
  }

  delete q;
}
