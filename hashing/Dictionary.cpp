#include <iostream>
#include "Dictionary.h"

// Check list:
// Constructor and destructor done.
// insert working on rn.



Dictionary::Dictionary(){
  d = new List*[size];

  for (int i = 0; i < size; i++)
    d[i] = new List();
}


Dictionary::~Dictionary(){
  for (int i = 0; i < size; i++){
    delete d[i];
  }
  delete d;
}



Person * Dictionary::get_person(std::string name){ 
  for (int i = 0; i < d[hash(name)]->get_size(); i++){
    std::string p = d[hash(name)]->locate(i)->getPerson()->get_name();  
    if (p == name){
      return d[hash(name)]->locate(i)->getPerson(); 
    }
  }
  throw 2;
}


std::string Dictionary::get_keys(){
  std::string str_keys = "";
  for (int i = 0; i < size; i++)
    if (d[i]) str_keys += d[i]->toString(); 
  
  if (str_keys.length() == 0) throw 1;
  return str_keys;
}


int Dictionary::hash(std::string v){
  return v.length() % size;
}

void Dictionary::insert(Person *p){
  d[hash(p->get_name())]->insert(p);
}

// get person return person given the name as the key.
// resolv




