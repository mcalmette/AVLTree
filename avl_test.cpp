//----------------------------------------------------------------------
// Author: Michael Calmette
// Course: CPSC 223, Spring 2020
// Assign: 10
// File:   hw10_test.cpp
//
// TODO: Description here
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "avl_collection.h"

using namespace std;


// Test 1
TEST(BasicListTest, CorrectSize) {
  AVLCollection<string,double> c;
  ASSERT_EQ(0, c.size());
  c.add("b", 10.0);
  ASSERT_EQ(1, c.size());
  c.add("a", 20.0);
  ASSERT_EQ(2, c.size());
  c.add("c", 20.0);
  ASSERT_EQ(3, c.size());
}

// Test 2
TEST(BasicListTest, SimpleFind) {
  AVLCollection<string,double> c;
  double v;
  ASSERT_EQ(false, c.find("b", v));
  c.add("b", 10.0);
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(10.0, v);
  ASSERT_EQ(false, c.find("a", v));
  c.add("a", 20.0);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(20.0, v);
}

// Test 3
TEST(BasicListTest, SimpleRemoveElems) {
  AVLCollection<string,int> c;
  c.add("b", 10);
  c.add("a", 20);
  c.add("d", 30);
  c.add("c", 30);
  ASSERT_EQ(4, c.size());
  int v;
  c.remove("a");
  ASSERT_EQ(3, c.size());
  ASSERT_EQ(false, c.find("a", v));
  c.remove("b");
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(false, c.find("b", v));  
  c.remove("c");
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(false, c.find("c", v));  
  c.remove("d");
  ASSERT_EQ(0, c.size());
  ASSERT_EQ(false, c.find("c", v));  
}

// Test 4
TEST(BasicListTest, SimpleRange) {
  AVLCollection<int,string> c;
  c.add(50, "e");
  c.add(10, "a");
  c.add(30, "c");
  c.add(40, "d");
  c.add(60, "f");
  c.add(20, "b");
  vector<string> vs;
  c.find(20, 40, vs);
  ASSERT_EQ(3, vs.size());
  // note that the following "find" is a C++ built-in function
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "a"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "b"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "c"));
  ASSERT_NE(vs.end(), find(vs.begin(), vs.end(), "d"));
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "e"));  
  ASSERT_EQ(vs.end(), find(vs.begin(), vs.end(), "f"));  
}

// Test 5
TEST(BasicListTest, SimpleSort) {
  AVLCollection<string,int> c;
  c.add("a", 10);
  c.add("e", 50);
  c.add("c", 30);
  c.add("b", 20);
  c.add("d", 40);
  vector<string> sorted_ks;
  c.sort(sorted_ks);
  ASSERT_EQ(5, sorted_ks.size());
  // check if in sorted order
  for (int i = 0; i < int(sorted_ks.size()) -1; ++i)
    ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
}
/*
// Test 6
TEST(BasicListTest, SimpleCopy) {
  AVLCollection<string,int> c1;
  c1.add("b", 20);
  c1.add("a", 10);
  c1.add("c", 30);
  ASSERT_EQ(3, c1.size());
  ASSERT_EQ(2, c1.height());
  // copy constructor
  AVLCollection<string,int> c2(c1);
  ASSERT_EQ(3, c2.size());
  ASSERT_EQ(2, c2.height());
  c2.add("d", 40);
  ASSERT_EQ(4, c2.size());
  ASSERT_EQ(3, c2.height());
  // assignment operator
  c1 = c2;
  ASSERT_EQ(4, c1.size());
  ASSERT_EQ(3, c1.height());  
}*/

// Test 7

TEST(BasicListTest, RemoveRebalanceCheck) {
  // no children, rebalance
  AVLCollection<string,int> c1;
  c1.add("c", 30);
  c1.add("b", 20);
  c1.add("d", 40);
  c1.add("a", 10);
  ASSERT_EQ(3, c1.height());
  c1.remove("c");
  ASSERT_EQ(2, c1.height());
  // one child, rebalance
  AVLCollection<string,int> c2;
  c2.add("e", 50);
  c2.add("c", 30);
  c2.add("f", 60);
  c2.add("a", 10);
  c2.add("d", 40);
  c2.add("b", 20);
  c2.add("g", 70);
  ASSERT_EQ(4, c2.height());
  c2.remove("f");
  //ASSERT_EQ(3, c2.height());
  // two children, rebalance
  AVLCollection<string,int> c3;
  c3.add("e", 50);
  c3.add("b", 20);
  c3.add("g", 70);
  c3.add("a", 10);
  c3.add("d", 40);
  c3.add("f", 60);
  c3.add("c", 30);
  ASSERT_EQ(4, c3.height());
  c3.remove("e");
  ASSERT_EQ(3, c3.height());
  
}



// Changing the word in the first argument 
// creates a separate test case
// AddRebalanceTest 1
TEST(AddRebalanceTest, LeftRebalanceCheck2) { 
  // left rotation
  AVLCollection<string,int> c1;
  c1.add("a", 10);
  c1.add("b", 20);
  c1.add("c", 30);
  ASSERT_EQ(2, c1.height());
}

// AddRebalanceTest 2
TEST(AddRebalanceTest, RightRebalanceCheck2) {
  // right rotation
  AVLCollection<string,int> c2;
  c2.add("c", 30);
  c2.add("b", 20);
  c2.add("a", 10);
  ASSERT_EQ(2, c2.height());
}

// AddRebalanceTest 3
TEST(AddRebalanceTest, LeftRightRebalanceCheck2) {
  // left-right rotation
  AVLCollection<string,int> c3;
  c3.add("c", 30);
  c3.add("a", 10);
  c3.add("b", 20);
  ASSERT_EQ(2, c3.height());
}

// AddRebalanceTest 4
TEST(AddRebalanceTest, RightLeftRebalanceCheck2) {
  // right-left rotation
  AVLCollection<string,int> c4;
  c4.add("a", 10);
  c4.add("c", 30);
  c4.add("b", 20);
  ASSERT_EQ(2, c4.height());
}

// AddRebalanceTest 5
TEST(AddRebalanceTest, LeftRebalanceCheck3) {
  // left rotation
  AVLCollection<string,int> c5;
  c5.add("e", 50);
  c5.add("f", 60);
  c5.add("c", 30);
  c5.add("d", 40);
  c5.add("b", 20);
  c5.add("a", 10);
  ASSERT_EQ(3, c5.height());
}

// AddRebalanceTest 6
TEST(AddRebalanceTest, RightLeftRebalanceCheck3) {
  // right-left rotation
  AVLCollection<string,int> c6;
  c6.add("e", 50);
  c6.add("f", 60);
  c6.add("b", 20);
  c6.add("d", 40);
  c6.add("a", 10);
  c6.add("c", 30);
  ASSERT_EQ(3, c6.height());
}

// AddRebalanceTest 7
TEST(AddRebalanceTest, RightRebalanceCheck3) {
  // right rotation
  AVLCollection<string,int> c7;
  c7.add("b", 20);
  c7.add("a", 10);
  c7.add("d", 40);
  c7.add("c", 30);
  c7.add("e", 50);
  c7.add("f", 60);
  ASSERT_EQ(3, c7.height());
}

// AddRebalanceTest 8
TEST(AddRebalanceTest, LeftRightRebalanceCheck3) {
  // left-right rotation
  AVLCollection<string,int> c8;
  c8.add("b", 20);
  c8.add("a", 10);
  c8.add("e", 50);
  c8.add("d", 40);
  c8.add("f", 60);
  c8.add("c", 30);
  ASSERT_EQ(3, c8.height());
}



// TODO: ... additional tests ...

TEST(BasicListTest, LargerAddAndFind) {
  AVLCollection<string,double> c;
  double v;
  ASSERT_EQ(0, c.size());
  c.add("d", 10.0);
  ASSERT_EQ(1, c.size());
  c.add("a", 9.0);
  c.add("g", 15.0);
  c.add("c", 12.0);
  c.add("e", 13.0);
  c.add("b", 1.0);
  c.add("f", 2.0);
  ASSERT_EQ(7, c.size());
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(true, c.find("g", v));
  ASSERT_EQ(true, c.find("e", v));
  ASSERT_EQ(true, c.find("f", v));
}





int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

