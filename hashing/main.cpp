#include <iostream>
#include "Dictionary.h"
#include "Person.h"
#include "List.h"

int main(){
  List *l = new List();
  Person *p = new Person("William", "Zheng", 1);
  l->insert(p);
  
  p = new Person("Md", "Ratul", 420);
  l->insert(p);
  
  p = new Person("Wai", "Hlaing", 1378);
  l->insert(p);
  

  std::cout << l->toString() << "\n";
  delete p;


}
