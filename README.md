# AVLTree

## Class Setup
```
cmake CMakeLists.txt
make
```
To use the test file:
```
./avlTest
```

To use the performance test:
```
./avlPerf rand-50k.txt
```

## About this project
AVL tree with key-value nodes - special tree that makes sure that the tree remains balanced (balance factor) with single and double rotations. Inserting nodes is less efficient than a normal BST, but the AVL tree is great for finding objects since the tree height is much smaller than a normal BST.  The file also implements these functions:
- add
- remove
- find
- range find
- keys (returns all keys by reference)
- sort (ascending order)
- size


The test file is used as a way to ensure that each function works with different test cases.  The performance file is used to find the speed and number of calls for each function. This can be used with a randomly generated key-value pairs that ranges from 10k pairs to 50k pairs.

Note: Need to have Cmake installed

# 50k items Performance - Test Results
=============

  Add Calls...: 50000
  
  Add Time....: 15338 microseconds
  
  Add Average.: 0.30676 microseconds


  Remove Calls...: 2000
  
  Remove Time....: 11221 microseconds
  
  Remove Average.: 5.6105 microseconds


  Find Calls...: 2000
  
  Find Time....: 110 microseconds
  
  Find Average.: 0.055 microseconds


  Range Calls...: 1
  
  Range Time....: 2989 microseconds
  
  Range Average.: 2989 microseconds

  Sort Calls...: 1
  
  Sort Time....: 6589 microseconds
  
  Sort Average.: 6589 microseconds
  
  Tree Height: 19
