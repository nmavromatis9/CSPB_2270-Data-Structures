#include "PriorityQueue.h"
using namespace std;
PriorityQueue::PriorityQueue()
{
    //head initialized to NULL in .h file, so no need to initialize here.
  
}

PriorityQueue::~PriorityQueue(){
    // You don't need to add anything here
}

    //My functions START
//returns head, or NULL if head unitialized.
shared_ptr<pq> PriorityQueue::GetHead()
{
    if(!head)
    {
        return NULL;
    }
    return head;
}

//prints list text sequentially.
void PriorityQueue::print()
{
    shared_ptr<pq>ptr(head);
    while(ptr)//!=NULL
    {
        cout<<ptr->text<<" ";
        ptr=ptr->next;
    }
    cout<<endl;
}

//setter function for obj.
shared_ptr<pq> PriorityQueue::set(string s, float p)
{
    shared_ptr<pq>ptr=InitPriorityQueue();
    ptr->text=s;
    ptr->priority=p;
    //ptr->next=NULL; //done in InitPriorityQueue().
    return ptr;
}
    //my functions END

//This function creates a new pq ptr object,
//initializes it with placeholder values,
//and sets the head to this placeholder pq ptr if head==NULL
shared_ptr<pq> PriorityQueue::InitPriorityQueue()
{
    shared_ptr<pq>ptr(new pq);
    ptr->text="";
    ptr->priority=0.0;
    ptr->next=NULL;
    if(!head)
    {
        head=ptr;
    }
    return ptr;
}

// Inserts pq pointer with text and priority into queue (linked list)
void PriorityQueue::Insert(shared_ptr<pq> queue, string text, float priority)
{
    shared_ptr<pq>new_node(new pq);
    shared_ptr<pq>ptr(head);
    //set also calls InitPriorityQueue(), which assigns placeholder head if necesarry.
    new_node=set(text, priority);
   //if InitPriorityQueue() called first, so head is placeholder
    if (head->priority==0.0) 
    {
        //replace placeholder head.
        head=new_node;
        return;
    }

    //if priority is greater than head, new_node will be new head.
    else if (new_node->priority>head->priority)
    {
        new_node->next=head;
        head=new_node;
    }
    //else, stop ptr one before spot to insert.
    else
    {
        //first check that ptr->next exists, so you don't go beyond end of list.
        //next, stop ptr before insertion, where ptr->priority>=new_node->priority>ptr->next->priority
            while(ptr->next && (new_node->priority<=ptr->next->priority) )
            {
                ptr=ptr->next;
            }
    
        new_node->next=ptr->next; //NULL if inserted as final node.
        ptr->next=new_node;
    }
}

// returns highest priority string, removes with pq node.
string PriorityQueue::Remove(shared_ptr<pq> queue)
{
    string s="";
   if (!head)
   {
       return "";
   }

   else
   {
       s=head->text;
       //effectively deletes old head
       head=head->next;
   }
   return s;
}

// Return highest priority text without removal.
string PriorityQueue::Peek(shared_ptr<pq> queue)
{
    if(!head)
    {
        return "";
    }
    return head->text;
}