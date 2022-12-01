#pragma once
#include <iostream>
#include "Person.h"
#include "List.h"

#define DICT_ERR_EMPTY 1
#define DICT_ERR_INVALID_ENTRY 2
#define DICT_ERR_INVALID_KEY 3

class Dictionary {
  private:
  List * * d;
  int size = 7;

  public:
  Dictionary();
  ~Dictionary();

  void insert(Person * p);
  int hash(std::string key);
  Person * get_person(std::string name);
  std::string get_keys();
};


