
//----------------------------------------------------------------------
// Author: Michael Calmette
// File:   avl_collection.h
// 
//----------------------------------------------------------------------


#ifndef AVL_COLLECTION_H
#define AVL_COLLECTION_H

#include <vector>
#include <algorithm>
#include <string>               // for testing
#include "collection.h"


template<typename K, typename V>
class AVLCollection : public Collection<K,V>
{
public:

  // create an empty tree
  AVLCollection();
  
  // tree copy constructor
  AVLCollection(const AVLCollection<K,V>& rhs);

  // tree assignment operator
  AVLCollection<K,V>& operator=(const AVLCollection<K,V>& rhs);

  // delete a tree
  ~AVLCollection();
  
  // add a new key-value pair into the collection 
  void add(const K& a_key, const V& a_val);

  // remove a key-value pair from the collectiona
  void remove(const K& a_key);

  // find and return the value associated with the key
  bool find(const K& search_key, V& the_val) const;

  // find and return the values with keys >= to k1 and <= to k2 
  void find(const K& k1, const K& k2, std::vector<V>& vals) const;
  
  // return all of the keys in the collection 
  void keys(std::vector<K>& all_keys) const;

  // return all of the keys in ascending (sorted) order
  void sort(std::vector<K>& all_keys_sorted) const;

  // return the number of key-value pairs in the collection
  int size() const;

  // return the height of the tree
  int height() const;
  
private:
  
  // avl tree node structure
  struct Node {
    K key;
    V value;
    int height;
    Node* left;
    Node* right;
  };

  // helper to empty entire tree
  void make_empty(Node* subtree_root);
  
  // helper to build sorted list of keys (used by keys and sort)
  void inorder(const Node* subtree_root, std::vector<K>& keys) const;

  // helper to recursively find range of values
  void range_search(const Node* subtree_root, const K& k1, const K& k2,
                    std::vector<V>& vals) const;

  // recursively (deep) copy ancestors of src to dst
  void preorder_copy(const Node* subtree_root_src, Node* subtree_root_dst);

  // helper function to remove a node recursively
  Node* remove(const K& key, Node* subtree_root);

  // recursive add helper
  Node* add(Node* subtree_root, const K& a_key, const V& a_val);
  
  // rotate right helper
  Node* rotate_right(Node* k2);

  // rotate left helper
  Node* rotate_left(Node* k2);

  // rebalance the subtree rooted at subtree_root
  Node* rebalance(Node* subtree_root);
  
  // number of k-v pairs in the collection
  int tree_size; 

  // root node of tree
  Node* root;

  // for testing only: "pretty" prints a tree with node heights
  void print_tree(std::string indent, Node* subtree_root) const;
};


// TODO: implement the above functions here ...


// NOTE: some examples given below ...


template<typename K, typename V>
AVLCollection<K,V>::AVLCollection()
{
  tree_size = 0;
  root = nullptr;
}

template<typename K, typename V>
// tree copy constructor
AVLCollection<K,V>::AVLCollection(const AVLCollection<K,V>& rhs)
{
  tree_size = 0;
  root = nullptr;
  *this = rhs;
}

template<typename K, typename V>
AVLCollection<K,V>& AVLCollection<K,V>::operator=(const AVLCollection<K,V>& rhs)
{
  if(this != &rhs)
  {
    make_empty(root);
    preorder_copy(rhs.root,root);
  }
  return *this;  
}

template<typename K, typename V>
AVLCollection<K,V>::~AVLCollection()
{
  make_empty(root);
  //tree_size = 0;
}


// to see how height should work
template<typename K, typename V> 
int AVLCollection<K,V>::height() const
{
  if(!root)
    return 0;
  return root->height;
}


// from class
template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::rotate_right(Node* k2)
{
  // fill in here
  Node* k1 = k2->left;
  k2-> left = k1->right ;
  k1-> right = k2 ;
  return k1 ;
}

// from class
template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::rotate_left(Node* k2)
{
  // fill in here
  Node* k1 = k2->right;
  k2->right = k1->left;
  k1->left = k2;
  return k1;
}

template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::rebalance(Node* subtree_root)
{
  if(!subtree_root)
    return subtree_root;
  
  Node* leftPtr = subtree_root->left;
  Node* rightPtr = subtree_root->right;

  int heightL = 0;
  int heightR = 0;
  
  if(leftPtr!=nullptr)
    heightL = leftPtr->height;
  if(rightPtr!=nullptr)
    heightR = rightPtr->height;
  
 int heightAdjustor;  
 if(heightL - heightR > 1) //unbalanced left
  {
    int heightLR = 0;
    int heightLL = 0;
    if(leftPtr->left != nullptr)
      heightLL = leftPtr->left->height;
    if(leftPtr->right != nullptr)
      heightLR = leftPtr->right->height;
    
    if(heightLL > heightLR)
    {
      heightAdjustor = leftPtr->left->height;
      subtree_root = rotate_right(subtree_root);
    }
    else 
    {
      heightAdjustor = leftPtr -> right -> height;
      subtree_root->left = rotate_left(subtree_root -> left);
      subtree_root = rotate_right(subtree_root);
      subtree_root->height++;
      subtree_root->left -> height--;
    }
    subtree_root->right->height = heightAdjustor;

  }
  else if(heightL - heightR < -1) //unbalanced right
  {
    int heightRL = 0;
    int heightRR = 0;
    if(rightPtr -> left != nullptr)
      heightRL = rightPtr -> left -> height;
    if(rightPtr -> right != nullptr)
      heightRR = rightPtr -> right -> height;
    
    if(heightRL < heightRR)
    {
      heightAdjustor = rightPtr -> right -> height;
      subtree_root = rotate_left(subtree_root);
    }
    else
    {
      heightAdjustor = rightPtr -> left -> height;
      subtree_root -> right = rotate_right(subtree_root -> right);
      subtree_root = rotate_left(subtree_root);
      subtree_root -> height++;
      subtree_root -> right -> height--;
    }
    subtree_root -> left -> height = heightAdjustor;
  } 
  
  return subtree_root;
}

template<typename K, typename V>
void AVLCollection<K,V>::add(const K& a_key, const V& a_val)
{
  // to build in the height and rebalance, this must be a recursive
  // function!
  if(size() == 0)
  { 
    Node* tmp = new Node;
    tmp->key=a_key;
    tmp->value=a_val;
    tmp->left=nullptr;
    tmp->right=nullptr;
    root = tmp;
    tree_size++;
  }
  else
     root = add(root, a_key, a_val);

  //print_tree("", root); // for debugging
}


template<typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::add(Node* subtree_root, const K& a_key, const V& a_val)
{
  
  if(!subtree_root)
  {
    Node* tmp = new Node;
    tmp->key=a_key;
    tmp->value=a_val;
    tmp->left=nullptr;
    tmp->right=nullptr;
    subtree_root=tmp;
    subtree_root->height=1;
    tree_size++;
  }
  else 
  {
    if (a_key < subtree_root->key)
        subtree_root->left = add(subtree_root->left, a_key, a_val);
    else
        subtree_root->right = add(subtree_root->right, a_key, a_val);
      
    int treeHeight = subtree_root->height;
    int leftHeight = 0;
    int rightHeight = 0;
    if(subtree_root-> right!=nullptr)
      rightHeight = subtree_root -> right -> height;
    if(subtree_root->left != nullptr)
      leftHeight = subtree_root -> left -> height;
    
    if(treeHeight - std::max(leftHeight,rightHeight) <= 0)
      subtree_root->height++;
  }
  // backtracking: rebalance at the subtree_root (as needed)
  
  return rebalance(subtree_root);
}  

template <typename K, typename V>
void AVLCollection<K,V>::remove(const K& a_key)
{
  root = remove(a_key, root);

}

template <typename K, typename V>
typename AVLCollection<K,V>::Node*
AVLCollection<K,V>::remove(const K& key, Node* subtree_root)
{
  V valu;
  bool found = find(key,valu);
  if(found == false)
    return subtree_root;

  int tmpHeight = subtree_root -> height;
  if(subtree_root && key < subtree_root -> key)
  {
    subtree_root -> left = remove(key, subtree_root -> left);
    if(!subtree_root->right) 
     subtree_root -> height--; //update ancestor height
    else if(subtree_root -> left)
    {
      if(subtree_root -> right -> height < subtree_root -> left -> height)
      {
          if(subtree_root -> height - subtree_root -> left -> height > 1)//decrease height
              subtree_root -> height--;
      } else if(subtree_root -> left -> height == subtree_root -> right -> height) 
      {
        if(subtree_root -> height - subtree_root -> left -> height > 1)//decrease height
            subtree_root -> height--;
      }
     }
    // rebalances as it backtracks
    subtree_root = rebalance(subtree_root);
   }
   else if(subtree_root && key > subtree_root -> key)
   {
     subtree_root->right = remove(key, subtree_root -> right);
     if(!subtree_root->left)  
      subtree_root -> height--;//decrease height

     subtree_root = rebalance(subtree_root);
   }
   else if(subtree_root && key == subtree_root -> key) 
   {
     Node* cur = subtree_root;
     int prevHeight;

     tmpHeight = subtree_root -> height;
     if(subtree_root -> left == nullptr && subtree_root->right == nullptr)
     {
       delete cur;
       subtree_root = nullptr;
     }
     else if(subtree_root -> left != nullptr && subtree_root -> right != nullptr)
     {
       Node* prev = subtree_root;
       cur = subtree_root-> right;
       while(cur-> left != nullptr)
       {
         prev = cur;
         cur = cur -> left;
       }

       if(prev -> right == nullptr)
        prev -> height--;

       if(prev != subtree_root) 
         prev-> left = cur -> right;
      cur -> left = subtree_root-> left;
      if(subtree_root->right != cur)
        cur-> right = subtree_root->right;
      delete subtree_root;
      subtree_root = cur;

      subtree_root->height = tmpHeight;
     } 
     else 
     {
       if(subtree_root -> left != nullptr)
       {
         subtree_root-> height = subtree_root -> left -> height;
         subtree_root = subtree_root-> left;
         delete cur;
       } 
       else 
       {
         subtree_root -> height = subtree_root -> right -> height;
         subtree_root = subtree_root -> right;
         delete cur;
       }
     }
     tree_size--;
   }//rebalance

  return rebalance(subtree_root);
}


template <typename K, typename V>
bool AVLCollection<K,V>::find(const K& search_key, V& the_val) const
{
  if(tree_size == 0)
    return false;
  
  Node* tmp = new Node;
  tmp->key = search_key;
  tmp->value = the_val;
  tmp->left = nullptr;
  tmp->right = nullptr;
  tmp->height=0;

  Node* cur = root;
  while(cur != nullptr)
  {
    if(cur->key == tmp->key) //match
    {
      the_val = cur -> value;
      return true;
    }
    else 
    {
      if(cur -> left == nullptr && cur->right == nullptr)
        cur = nullptr;
      else
      {
        if(cur-> key > tmp->key)
          cur = cur -> left;
        else
          cur = cur -> right;
      }
    }
  }

  return false;
}

template <typename K, typename V>
void AVLCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
{
  range_search(root, k1, k2, vals);
}

template <typename K, typename V>
void AVLCollection<K,V>::keys(std::vector<K>& all_keys) const
{
  inorder(root, all_keys);
}

template <typename K, typename V>
void AVLCollection<K,V>::sort(std::vector<K>& all_keys_sorted) const
{
  inorder(root, all_keys_sorted);
}

template <typename K, typename V>
int AVLCollection<K,V>::size() const
{
  return tree_size;
}

template <typename K, typename V>
void AVLCollection<K,V>::make_empty(Node* subtree_root)
{
  if(subtree_root == nullptr)
          return;
        
  make_empty(subtree_root -> left);
  make_empty(subtree_root -> right);

  delete subtree_root;
  subtree_root = nullptr;
}

template <typename K, typename V>
void AVLCollection<K,V>::inorder(const Node* subtree_root, std::vector<K>& keys) const
{
  if(subtree_root == nullptr)
         return;
  inorder(subtree_root->left,keys);
  keys.push_back(subtree_root->key);
  inorder(subtree_root->right,keys);
}

template <typename K, typename V>
void AVLCollection<K,V>::range_search(const Node* subtree_root, const K& k1, const K& k2,std::vector<V>& vals) const
{
  if(subtree_root == nullptr)
          return;
        
  range_search(subtree_root->left,k1,k2,vals);
  range_search(subtree_root->right,k1,k2,vals);

  if(subtree_root-> key >= k1 && subtree_root->key <= k2)
    vals.push_back(subtree_root->value);
}

template <typename K, typename V>
void AVLCollection<K,V>::preorder_copy(const Node* subtree_root_src, Node* subtree_root_dst)
{
  if(subtree_root_src == nullptr)
        return;
  //visit node, then go left, and then go right
  preorder_copy(subtree_root_src->left,subtree_root_dst);
  add(subtree_root_src->key,subtree_root_src->value);
  preorder_copy(subtree_root_src->right,subtree_root_dst);
}

template<typename K, typename V>
void AVLCollection<K,V>::print_tree(std::string indent, Node* subtree_root) const
{
  if (!subtree_root)
    return;
  std::cout << indent << subtree_root->key << " (h="
            << subtree_root->height << ")" << std::endl;
  print_tree(indent + "  ", subtree_root->left);
  print_tree(indent + "  ", subtree_root->right);
}


#endif
