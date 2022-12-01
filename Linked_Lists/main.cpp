#include <iostream>
#include "Node.h"
//#include "List.h"
#include "OList.h"

int main() {
  OList * l1 = new OList();


  l1->insert(1);
  l1->insert(1);
  l1->insert(2);
  l1->insert(3);
  l1->insert(5);
  l1->insert(8);
  l1->insert(13);

  std::cout << "List: " << l1->toString() << "\n";
  l1->reverse();
  std::cout << "List: " << l1->toString() << "\n\n";
  delete l1;


  OList * l2 = new OList();
  std::cout << "List2: " << l1->toString() << "\n";
  l2->reverse();
  std::cout << "List2: " << l1->toString() << "\n\n";
  delete l2;

  OList * l3 = new OList();
  l3->insert(1);
  l3->insert(2);
  std::cout << "List3: " << l1->toString() << "\n";
  l2->reverse();
  std::cout << "List3: " << l1->toString() << "\n\n";
  delete l3;
}


