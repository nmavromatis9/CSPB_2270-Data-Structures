#include "LinkedList.h"

// constructor, initialize class variables and pointers here if need.
LinkedList::LinkedList()
{
  
  // Initially set top pointer to a null shared_ptr of node
  shared_ptr<node> ptr(new node);
  ptr=NULL;
  //ptr->next=NULL; //This makes a segmentation fault. 
  top_ptr_=ptr;

  //also valid:
  //top_ptr_ = shared_ptr<node>(NULL);
}

//deconstructor,
LinkedList::~LinkedList(){
}


shared_ptr<node> LinkedList::InitNode(int data)
{
  //creates a new node structure from heap memory.
  shared_ptr<node> ret(new node);
  ret->data=data;
  ret->next=NULL;
  return ret;
}

string LinkedList::Report()
{
  string ret="";
  shared_ptr<node> ptr(new node);
  ptr=top_ptr_;
    while(ptr)//!=NULL
    {
      //convert int to string, concatenate to string.
      ret+=to_string(ptr->data);
      ret+=" ";
      ptr=ptr->next;
    }
    return ret;
}


void LinkedList::AppendData(int data)
{
  //This call InitNode, which allocates new memory for shared_ptr<node>
  //and stores this returned shared_ptr in ptr.
  shared_ptr<node> ptr=InitNode(data);
  Append(ptr);
}

void LinkedList::Append(shared_ptr<node> new_node)
{
  //initiaize pointer to help access nodes of linked list.
  shared_ptr<node> crsr(new node);
  crsr=top_ptr_;
  //if top_ptr_!=NULL
  if(crsr)
  {
    //scroll crsr to stop at final node
    while(crsr->next) //!=NULL
    {
      crsr=crsr->next;
    }
    //insert new_node at end.
    crsr->next=new_node;
  }
  else
  {
    //assign top_ptr_ to this new_node so that top_ptr is no longer NULL
    //NOTE: crsr=new_node fails. Must assign top_ptr_ directly!
    top_ptr_= new_node;
  }
    
}

void LinkedList::InsertData(int offset, int data)
{ 
  //initialize pointer to new node containing data
  shared_ptr<node> new_node=InitNode(data);
  //pass to Insert helper function.
  Insert(offset, new_node);
}

void LinkedList::Insert(int offset, shared_ptr<node> new_node)
{
  //ptr acts as cursor.
  shared_ptr<node> ptr(new node);
  //tmp will store "old->next"
  shared_ptr<node> tmp(new node);
  ptr=top_ptr_;
  
  if(!ptr)//if top_ptr_==NULL, return
  {
    return;
  }
  if(offset<0)//invalid offset passed.
  {
    return;
  }
  //special case, when no scrolling needs to be done.
  if (offset==0)
  {
    //store node to come after new_node in tmp
    tmp=ptr;
    //set top_ptr_(head) to this new_node
    top_ptr_=new_node;
    top_ptr_->next=tmp;
  }
  //else: stop pointer one before offset position.
  else
  {
    for (int i=0; i<offset-1; i++)
    {
      if(ptr->next)//!=NULL
      {
        ptr=ptr->next;
      }
    }
    //store node to come after new_node in tmp
    tmp=ptr->next;
    ptr->next=new_node;
    new_node->next=tmp;
  }
}

void LinkedList::Remove(int offset)
{
  // Your code here
}

int LinkedList::Size()
{
  int ret;
  // Your code here
  return ret;
}

bool LinkedList::Contains(int data)
{
  bool ret;
  // Your code here
  return ret;
}

// This function is implemented for you
// It returns the top pointer
shared_ptr<node> LinkedList::GetTop(){
  return top_ptr_;
}

// This function is implemented for you
// It sets a given pointer as the top pointer
void LinkedList::SetTop(shared_ptr<node> top_ptr){
  top_ptr_ = top_ptr;
}
