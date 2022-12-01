#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <stdexcept>
#include "OList.h"

TEST_CASE("Insert/ToString Test: ") {

  OList * l = new OList();

  // null test
  CHECK(l->toString() == "head --> nullptr");

  // random sequence with negative test
  l->insert(2);
  l->insert(1);
  l->insert(13);
  l->insert(-1);
  l->insert(5);
  CHECK(l->toString() == "head --> -1 --> 1 --> 2 --> 5 --> 13 --> nullptr");

  // re-insert test
  l->insert(8);
  l->insert(3);
  CHECK(l->toString() == "head --> -1 --> 1 --> 2 --> 3 --> 5 --> 8 --> 13 --> nullptr");

  delete l;
}

TEST_CASE("Contains Test: ") {
  OList * l = new OList();

  // null test
  CHECK(!l->contains(-1));

  // negative test
  l->insert(-1);
  CHECK(l->contains(-1));


  l->insert(2);
  l->insert(3);
  l->insert(5);
  CHECK(l->contains(2));
  CHECK(l->contains(3));
  CHECK(l->contains(5));

  delete l;
}

TEST_CASE("Get Test: ") {
  OList * l = new OList();

  // order: -3, -2, 0, 2, 3
  l->insert(-2);
  l->insert(0);
  l->insert(2);
  l->insert(-3);
  l->insert(3);

  CHECK(l->get(0) == -3);
  CHECK(l->get(1) == -2);
  CHECK(l->get(2) == 0);
  CHECK(l->get(3) == 2);
  CHECK(l->get(4) == 3);

  //Check for getting something out of bounds
  CHECK(l->get(99) == -1);

  delete l;
}

TEST_CASE("Remove/ToString Tests: ") {
  OList * l = new OList();

  // Order: -1, 1, 2, 3, 5, 8, 13
  l->insert(3);
  l->insert(2);
  l->insert(1);
  l->insert(13);
  l->insert(-1);
  l->insert(5);
  l->insert(8);
  CHECK(l->toString() == "head --> -1 --> 1 --> 2 --> 3 --> 5 --> 8 --> 13 --> nullptr");

  // testing singular removal
  l->remove(3);
  CHECK(l->toString() == "head --> -1 --> 1 --> 2 --> 5 --> 8 --> 13 --> nullptr");


  l->remove(1);
  l->remove(1);
  CHECK(l->toString() == "head --> -1 --> 5 --> 8 --> 13 --> nullptr");

  //Check for removing something out of bounds
  CHECK_THROWS_AS(l->remove(50), std::out_of_range);

  delete l;
}

TEST_CASE("Reverse Test: ") {
  OList * l = new OList();

  // null test
  l->reverse();
  CHECK(l->toString() == "head --> nullptr");

  // single test
  l->insert(-1);
  l->reverse();
  CHECK(l->toString() == "head --> -1 --> nullptr");

  l->insert(0);
  l->insert(1);
  l->insert(2);
  l->insert(3);
  l->insert(4);

  l->reverse();
  CHECK(l->toString() == "head --> 4 --> 3 --> 2 --> 1 --> 0 --> -1 --> nullptr");

  // reversing reverse
  l->reverse();
  CHECK(l->toString() == "head --> -1 --> 0 --> 1 --> 2 --> 3 --> 4 --> nullptr");

  delete l;
}
