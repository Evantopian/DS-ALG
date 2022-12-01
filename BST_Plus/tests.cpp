#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Node.h"
#include "BSTree.h"

BSTree *bst = new BSTree();

TEST_CASE("Searching & Inserting"){
  bst->insert(5);
  bst->insert(2);
  bst->insert(12);
  bst->insert(-4);
  bst->insert(4);
  bst->insert(3);
  bst->insert(9);
  bst->insert(21);
  bst->insert(19);
  bst->insert(25);

  int x = bst->rsearch(2);
  CHECK(x == 2);
  x = bst->rsearch(-4);
  CHECK(x == -4);
  x = bst->rsearch(19);
  CHECK(x == 19);
}

TEST_CASE("Printing & Deletion"){
  // default case
  CHECK(bst->get_debug_string() == "5 ->(2 ->(-4 ->()->())->(4 ->(3 ->()->())->()))->(12 ->(9 ->()->())->(21 ->(19 ->()->())->(25 ->()->())))nullptr");

  bst->delete_node(3);
  CHECK(bst->get_debug_string() == "5 ->(2 ->(-4 ->()->())->(4 ->()->()))->(12 ->(9 ->()->())->(21 ->(19 ->()->())->(25 ->()->())))nullptr");
    
  bst->delete_node(19);
  bst->delete_node(-4);
  CHECK(bst->get_debug_string() == "5 ->(2 ->()->(4 ->()->()))->(12 ->(9 ->()->())->(21 ->()->(25 ->()->())))nullptr");
  
  bst->insert(17);
  bst->insert(1);
  bst->insert(-2);
  CHECK(bst->get_debug_string() == "5 ->(2 ->(1 ->(-2 ->()->())->())->(4 ->()->()))->(12 ->(9 ->()->())->(21 ->(17 ->()->())->(25 ->()->())))nullptr");
}

TEST_CASE("Counting Leaves"){
  // default case based on previous insertions
  CHECK(bst->count_leaves() == 5);
  
  // one none leaf, one leaf removal.
  bst->delete_node(-2);
  bst->delete_node(4);
  CHECK(bst->count_leaves() == 4);

  // removing singular leaf
  bst->delete_node(17);
  CHECK(bst->count_leaves() == 3);
  

  // double insert, one non-leaf, one leaf.
  bst->insert(-1);  CHECK(bst->count_leaves() == 3);
  bst->insert(4);
  CHECK(bst->count_leaves() == 4);
}


TEST_CASE("Height and Summing"){
  // default
  BSTree *bst2 = new BSTree();
  CHECK(bst2->height() == 0);

  // general adding
  bst2->insert(20);
  bst2->insert(10);
  CHECK(bst2->height() == 2);

  bst2->insert(5);
  bst2->insert(40);
  CHECK(bst2->height() == 3);
  
  // deleting
  bst2->insert(2);
  bst2->delete_node(5); 
  CHECK(bst2->height() == 3);

  bst2->delete_node(10);
  CHECK(bst2->height() == 2);


  // default
  CHECK(bst2->sum_level(0) == 0);

  // different lvls
  CHECK(bst2->sum_level(2) == 42);
  
  bst2->insert(50);
  CHECK(bst2->sum_level(3) == 50);
 
  try {
    bst2->sum_level(4);
  } 
  catch (int e){
    CHECK(e == 2);
  }
}
