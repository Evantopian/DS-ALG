#include <iostream>
#include "stack.h"
#include "queue.h"

int main(){
  /*
  Stack *s = new Stack();
  
  s->push(5);
  s->push(10);
  s->push(20);
  s->push(30);
  s->push(999);
  

  std::cout << "Size: " << s->getSize() << "Top: " << s->top() << std::endl;
  int y = s->pop();
  y = s->pop();

  std::cout << y << " | Size: " << s->getSize() << std::endl;
 */
  Queue * q = new Queue();

  std::cout << q->is_empty() << "\n";

  q->enqueue(1);
  q->enqueue(2);
  q->enqueue(3);
  q->enqueue(4);
  std::cout << q->front() << " = 1 \n";

  std::cout << q->is_full() << "\n";
  q->enqueue(3);
}
