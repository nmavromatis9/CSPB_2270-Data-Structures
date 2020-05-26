#include "BST.h"
//delete
#include<iostream>
using namespace std;
//delete
// constructor, initialize class variables and pointers here if need.
BST::BST()
{
  //no need to allocate new memory for root_ptr_. Done when class called?  
 // root_ptr_ = shared_ptr<bst_node>(new bst_node);
 //shared_ptr<bst_node>root_ptr_(NULL);
  root_ptr_ = shared_ptr<bst_node>(NULL);
}

//deconstructor,
BST::~BST(){
}

shared_ptr<bst_node> BST::InitNode(int data)
{
  shared_ptr<bst_node> ptr(new bst_node);
  ptr->data=data;
  ptr->left=NULL;
  ptr->right=NULL;
  
  return ptr;
}

//iterative solution is easiest to implement here.
void BST::Insert(shared_ptr<bst_node> new_node)
{
  shared_ptr<bst_node> ptr(new bst_node);
  shared_ptr<bst_node> parent(new bst_node);
  ptr=root_ptr_;

  if(!root_ptr_) //root==NULL
  {
    //make root point to new_node.
    root_ptr_=new_node;
  }
  else
  {
    //scroll ptr to appropriate empty(NULL) left or right child.
    while(ptr)//!=NULL
    {
      //store parent node of eventual spot to insert.
      parent=ptr;
      if(new_node->data<ptr->data)//if data less than ptr->data
      {
        //scroll ptr to equal left child, try again
        ptr=ptr->left;
      }
      else if(new_node->data>=ptr->data)
      {
        //scroll ptr to equal right child, try again
        ptr=ptr->right;
      }
    }
    //if new_node->data>=parent->data, insert as right child.
    if (new_node->data>=parent->data)
    {
      parent->right=new_node;
    }
    //else if new_node->data<parent->data, insert as left child.
    else if(new_node->data<parent->data)
    {
      parent->left=new_node;
    }
  }
  

}

//this calls helper functions
//InitNode(data)
//then Insert(shared_ptr<bst_node> new_node)
void BST::InsertData(int data)
{
  shared_ptr<bst_node> new_node=InitNode(data);
  Insert(new_node);
}

//This finds and returns the parent of node (which contains data)
shared_ptr<bst_node> BST:: GetParent(shared_ptr<bst_node> node, int data)
{
  shared_ptr<bst_node> ptr(new bst_node);
  ptr=node;
  //always include NULL case
  if(!ptr)
  {
    return NULL;
  }
  //if node is root, it has no parent. Return NULL
  if(data==root_ptr_->data)
  {
    //cout<<"ROOT"<<endl;
    return NULL;
  }
  //if parent found, return it.
  if(ptr->left->data==data || ptr->right->data==data)
  {
    return ptr;
  }
  //if data<ptr->data, recur left, moving down left subtree.
  else if(data<ptr->data)
  {
    //must return GetParent(); just GetParent() doesn't work.
    return GetParent(ptr->left, data);
  }
  //if data>ptr->data, recur right, moving down right subtree.
  else if(data>ptr->data)
  {
    return GetParent(ptr->right, data);
  }
  
  return NULL;
}

//Find and return InOrder successor of Node
//Which is leftmost node of right subtree of Node
shared_ptr<bst_node> BST::InOrder(shared_ptr<bst_node> node)
{
  shared_ptr<bst_node> ptr(new bst_node);
  //scroll to right subtree
  ptr=node->right;
  //set ptr to leftmost node.
  while(ptr->left)//!=NULL
  {
    ptr=ptr->left;
  }

  return ptr;
}
//This function calls helper function RemoveHelp()
void BST::Remove(int data)
{
  shared_ptr<bst_node> ptr(new bst_node);
  //search for and store node to be deleted in ptr
  ptr=GetNode(root_ptr_, data);

  if(!ptr)//if node to be deleted not found, exit.
  {
    return;
  }
//call helper function
  RemoveHelp(ptr, data);
}

//3 cases:
//Node is leaf: Just delete.
//Node has one child: Copy child to node, delete child. 
//Node has 2 children:
//find successor node: node in the right subtree with min value.
//  copy successor to node, and delete successor. 
//  Successor always has zero children.
void BST::RemoveHelp(shared_ptr<bst_node> &node, int data)
{

  shared_ptr<bst_node> p (new bst_node);
  //find parent, so that ->left or ->right child can be altered.
  p=GetParent(root_ptr_, data);
  
  //cout<<node->data<<" FOUND"<<endl;
  
  if((!node->left) && (!node->right)) //if node is a leaf
  {
    //cout<<"LEAF"<<endl;
    //if node is right child, set this child to nullptr.
    if(p->right->data==data)
    {
      p->right=nullptr;
    }
  //if node is left child, set this child to nullptr.
    else if(p->left->data==data)
    {
      p->left=nullptr;
    }
  }
  //else if node has one left child
  else if(!node->right)
  {
    //copy data of left child, then set left child to null
    node->data=node->left->data;
    node->left=nullptr;
  }
  //if node has one right child
  else if(!node->left)
  {
    //copy data of right child, set right child to null
    node->data=node->right->data;
    node->right=nullptr;
  }
  //if node has 2 children, find and replace
  //with inorder successor, then delete that successor.
  else
  {
    //store inorder successor in min
    shared_ptr<bst_node> min=InOrder(node);
    //cout<<min->data<<" IN ORDER"<<endl;

    //find min's parent, store it
    p=GetParent(root_ptr_, min->data);
    //cout<<"PARENT 2= "<<p->data<<endl;

    //copy min to node
    node->data=min->data;
    //cout<<"NEW NODE DATA"<<node->data<<endl;
    //delete min:
    //if min was right child, set right child to null
    if(p->right && p->right->data==min->data)
    {
      p->right=nullptr;
    }
  //if min was left child, set left child to null
    else if (p->left && p->left->data==min->data)
    {
      p->left=nullptr;
    }
  }
      
}

bool BST::Contains(shared_ptr<bst_node> subt, int data)
{
  shared_ptr<bst_node> ptr(new bst_node);
  ptr=subt;

  if(!subt)//if subt==NULL(empty)
  {
    return false;
  }

  while (ptr)//!=NULL
  {
    if(ptr->data == data)//if val found in current pointer
    {
      return true;
    }
    //if data<ptr->data, search left subtree.
    else if(data<ptr->data)//scroll to left child, iterate again(reenter while loop)
    {
      ptr=ptr->left;
    }
    //if data>=ptr->data, search right subtree
    else if(data>=ptr->data)//scroll to right child, iterate again.
    {
      ptr=ptr->right;
    }
  }
  return false;
}
//Just like Contains, but returns pointer or NULL
shared_ptr<bst_node> BST::GetNode(shared_ptr<bst_node> subt, int data)
{
  shared_ptr<bst_node> ptr(new bst_node);
  ptr=subt;

  if(!subt)//if subt==NULL(empty)
  {
    return NULL;
  }

  while (ptr)//!=NULL
  {
    if(ptr->data == data)//if val found in current pointer
    {
      return ptr;
    }
    //if data<ptr->data, search left subtree.
    else if(data<ptr->data)//scroll to left child, iterate again(reenter while loop)
    {
      ptr=ptr->left;
    }
    //if data>=ptr->data, search right subtree
    else if(data>=ptr->data)//scroll to right child, iterate again.
    {
      ptr=ptr->right;
    }
  }
  return NULL;
}

//This function is recursive.
int BST::Size(shared_ptr<bst_node> subt)
{
  shared_ptr<bst_node> ptr(new bst_node);
  ptr=subt;

  if (!ptr)//empty, and stopping case.
  {
    return 0;
  }
  else 
  {
    //recursively add 1 + (root)
    //+ size of right subtree,
    //+ size of left subtree.
    //SO the recursion continuously adds 1 at each call, moving down subtrees.
    return (1 + Size(ptr->left) + Size(ptr->right));
  }

  return 0;
}

void BST::ToVector(shared_ptr<bst_node> subt, vector<int>& vec)
{
  // inorder: Left, Root, Right
  // eventually fill in vec ex. vec[0] = 1;
  shared_ptr<bst_node> ptr(new bst_node);
  ptr=subt;

  if(!ptr)//empty tree
  {
    return;
  }
  //Recursion works well here because it operates on an implicit stack.
  //Use recursion on left child.
  ToVector(ptr->left, vec);

  //store value of current node in vector.
  vec.push_back(ptr->data);

  //Use recursion on right child.
  ToVector(ptr->right, vec);

  
}

// This function is implemented for you
// Returns the root pointer
shared_ptr<bst_node> BST::GetRoot(){
  return root_ptr_;
}

// This function is implemented for you
// sets a given pointer as the top pointer
void BST::SetRoot(shared_ptr<bst_node> root_ptr){
  root_ptr_ = root_ptr;
}