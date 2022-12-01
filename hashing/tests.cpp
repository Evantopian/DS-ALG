#include "Person.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Dictionary.h"


Dictionary *d = new Dictionary();

Person *p1 = new Person("Evan", "Huang", 1);
Person *p2 = new Person("Nave", "Gnuah", 2);
Person *p3 = new Person("Md", "Ratul", 3);
Person *p4 = new Person("arats", "m", 4);


TEST_CASE("insert & get_keys"){
  try{
    std::string exception_test = d->get_keys();
  }
  catch (int e){
    CHECK(e == 1);
  }

  d->insert(p1);
  CHECK(d->get_keys() == " Huang, Evan (ID: 1) -> ");

  d->insert(p2);
  d->insert(p3);
  CHECK(d->get_keys() == " Ratul, Md (ID: 3) ->  Gnuah, Nave (ID: 2) ->  Huang, Evan (ID: 1) -> ");
  
  d->insert(p4);
  CHECK(d->get_keys() == " m, arats (ID: 4) ->  Ratul, Md (ID: 3) ->  Gnuah, Nave (ID: 2) ->  Huang, Evan (ID: 1) -> ");
}


TEST_CASE("Hash"){
  CHECK(d->hash(p1->get_name()) == 4);
  CHECK(d->hash(p2->get_name()) == 4);
  CHECK(d->hash(p3->get_name()) == 2);
  CHECK(d->hash(p4->get_name()) == 1);
}

TEST_CASE("get_person"){
  CHECK(d->get_person(p1->get_name()) == p1);
  CHECK(d->get_person(p2->get_name()) == p2);
  CHECK(d->get_person(p3->get_name()) == p3);
  CHECK(d->get_person(p4->get_name()) == p4);
    
  Person *notp = new Person("Not in", "Hash", 123);
  try{
    if (d->get_person("Exception test") == notp) std::string s = "test";
  }
  catch (int e){
    CHECK(e == 2);
  }

}



