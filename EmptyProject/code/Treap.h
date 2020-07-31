#ifndef Treap_H__
#define Treap_H__

#include<iostream>
#include <string>
#include <memory>
#include <vector>


using namespace std;

struct Node{
char c;
int priority;
shared_ptr<Node> left;
shared_ptr<Node> right;
};

class Treap{
public:
  //The constructor, left empty.
  Treap();
  ~Treap();

  //build a random Treap of 15 random uppercase chars. 
  //Max size would be 26 (n of uppercase chars)
  Treap buildTreap();
  //Builds a Treap from vector of chars.
  Treap buildTreap(vector<char> v);

  
  //These public functions all call overloaded private functions
  //which operate on private member variable Root.
  //In this way, user does not have to manage shared_ptrs which got messy.

  void insert(char c)
  {
    insert(Root, c);    
  }
  void remove(char c)
  {
    remove(Root, c);
  }
  
  void print()
  {
    print(Root);
    cout<<endl;
  }
  shared_ptr<Node> search(char c)
  {
    return search(Root, c);
  }
  vector<char> findUnion(Treap A, Treap B)
  {
    return findUnion(A.Root, B.Root);
  }
  
  vector<char> findIntersection(Treap A, Treap B)
  {
    return findIntersection(A.Root, B.Root);
  }
  
  vector<char> findDifference(Treap A, Treap B)
  {
    return findDifference(A.Root, B.Root);
  }
  
private:
  //This returns a random priority between 0-99 inclusive.
  int randPriority();
  //This creates a new Treap node with c as main key,
  //and random priority.
  shared_ptr<Node> initNode(char c);
  //Inserts Node with char c into leaf of treap pointed to by root.
  //rotate this Node to maintain treap properties.
  void insert(shared_ptr<Node>& root,  char c);
  //Removes Node with character c, by rotating that node to be a leaf.
  void remove(shared_ptr<Node>& root,  char c);
  //searches for and returns Node with char c.
  shared_ptr<Node> search(shared_ptr<Node>& root,  char c);
  //rotateLeft or Right at root to maintain treap invariant.
  shared_ptr<Node> rotateLeft(shared_ptr<Node> root);
  shared_ptr<Node> rotateRight(shared_ptr<Node> root);
  //prints treap characters inOrder.
  void print(shared_ptr<Node> root);
  //converts treap to a vector inOrder, to later run set operations.
  void toVector(shared_ptr<Node> root, vector<char>&res);

  //returns a vector of chars of the union of two Treaps.
  vector<char> findUnion(shared_ptr<Node> A, shared_ptr<Node> B);
  //returns a vector of chars of the intersection of two Treaps.
  vector<char> findIntersection(shared_ptr<Node> A, shared_ptr<Node> B);
  //returns a vector of chars of the difference A-B
  vector<char> findDifference(shared_ptr<Node> A, shared_ptr<Node> B);
  //Capital R root is initialized as NULL private variable.
  //This is first set in insert(char c)
  shared_ptr<Node> Root=NULL;
};

#endif // Treap_H__