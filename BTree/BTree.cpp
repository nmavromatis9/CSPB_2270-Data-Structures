#include "BTree.h"
#include <iostream>
using namespace std;

// constructor, initialize class variables and pointers here if need.
BTree::BTree(){
  // Your code here
}

//deconstructor,
BTree::~BTree(){
}

 // insert adds the given key into a b-tree rooted at 'root'.  If the
  // key is already contained in the btree this should do nothing.
  // 
  // On exit: 
  // -- the 'root' pointer should refer to the root of the
  //    tree. (the root may change when we insert or remove)
  // -- the btree pointed to by 'root' is valid.
void BTree::insert(shared_ptr<btree> root, int key)
{
  //use this pointer to store correct insertion spot.
  shared_ptr<btree> spot(new btree);
  //first, check for special case that root is full,

  if(isFull(root))
  {
    cout<<"Root needs to be split."<<endl;
    splitRoot(root);
    return;
  }

  //special case: root is a leaf, that is not full.
  //insert key into root, and then split if root becomes full, split root and exit.
  if(root->is_leaf)
  {
    fillKeys(root, key);
    if(isFull(root))
    {
      splitRoot(root);
      return;
    }
    return;
  }
  
  //For all other cases:
  //use find helper function to find correct insertion point. 
  spot=find(root, key);
  //if this spot is full, split the spot and reinsert.
  //fillKeys is passed correct insertion spot, so find MUST be used first.
  if(isFull(spot))
  {
    splitChild(root, spot);
    spot=find(root, key);
    fillKeys(spot, key);
  }
  //else, just insert key into spot.
  else
  {
    fillKeys(spot, key);
  }
  //now, if spot is full, split this spot. 
  if(isFull(spot))
  {
    splitChild(root, spot);
  }

  return;
}

 // remove deletes the given key from a b-tree rooted at 'root'. If the
  // key is not in the btree this should do nothing.
  //
  // On exit:
  // -- the 'root' pointer should refer to the root of the
  //    tree. (the root may change when we insert or delete)
  // -- the btree pointed to by 'root' is valid.
void BTree::remove(shared_ptr<btree> root, int key)
{
  /*
  //I will implement removal from a leaf here.
  shared_ptr<btree> spot=find(root, key);
  int i=0;
  for (i=0; i<spot->num_keys; i++)
  {
    if (key==spot->keys[i])
      break;
  }
  if(i==spot->num_keys)
  {
    return;
  }
  cout<<"Key to be deleted found at index "<<i<<endl;
  //move all keys after ith position one backwards
  for(int j=i; j<spot->num_keys; j++)
  {
    spot->keys[j]=spot->keys[j+1];
  }
  spot->num_keys--;
  return;
  */

}

//This returns child of parent, where child[i] contains key 
int BTree::findChild(shared_ptr<btree> parent, int key)
{
  shared_ptr<btree> ptr=parent;
   if(ptr->is_leaf) //means parent has no children
    {
      cout<<"node has no children"<<endl;
      return -10;
    }
  
  int i=0;
  for(i=0; i<ptr->num_keys; i++)
      {
        //This loop finds correct child node that has key.
        //Maybe a check for actual value is necessary.
        if(key<ptr->keys[i])
        {
          return i;
        }
      }
      //This executes if key belongs in right most child.
      if(ptr->children[ptr->num_keys])
      {
        return ptr->num_keys;
      }
    
    //error condition.
    cout<<"NO valid child i found."<<endl;
    return -100;
}

// find locates the node that either: (a) currently contains this key,
  // or (b) the node that would contain it if we were to try to insert
  // it.  Note that this always returns a non-null node.
shared_ptr<btree> BTree::find(shared_ptr<btree> root, int key)
{
  shared_ptr<btree> ptr=root;
    //if key is found in current btree node(ptr), return this node.
    for(int i=0; i<ptr->num_keys; i++)
    {
      if (key==ptr->keys[i])
      {
        return ptr;
      }
    }

      //if ptr is leaf, that means you hit a stopping case, and just return this node.
     //else, you will search recursively in children, which a leaf does not have.
    if(ptr->is_leaf)
    {
      return ptr;
    }
    //else, recursively search correct child node.
    else
    {
      int i=0;
      for(i=0; i<ptr->num_keys; i++)
      {
        //This loop finds correct child node that key belongs in.
        if(key<ptr->keys[i])
        {
          return find(ptr->children[i], key);
        }
        //NOTE: i exits as greater than loop condition.
        //This means just access i below (NOT i+1)
      }
      //This executes if key belongs in right most child.
      if(ptr->children[i])
      {
        return find(ptr->children[i], key);
      }
    }
    return ptr;
}

//this is a recursive function.
int BTree::count_nodes(shared_ptr<btree> root)
{ 
  int count=0;
  //if root==NULL, return 0
  if(!root)
  {
    return 0;
  }
  //if root is a leaf, add one more onto total.
  if(root->is_leaf)
  {
    return count+=1;
  }
  else 
  {
    //set count=1 for current node (not a leaf) 
    count=1;
    //add one more for each child by adding recursion (each child will be is_leaf)
    for (int i=0; i<=root->num_keys; i++)
    {
      count=count+count_nodes(root->children[i]);
    }
  }
  return count;
}

int BTree::count_keys(shared_ptr<btree> root)
{ 
  if(!root)
  {
    return 0;
  }

  //initializes count to root->num_keys. Also recursively allows count to be updated.
  int count=root->num_keys;
  //if root is not a leaf:
  if(root->is_leaf==false)
  {
    //recursively add onto count for each child node.
    for (int i=0; i<=root->num_keys; i++)
    {
      count=count+count_keys(root->children[i]);
    }
  }
  //this last return is key to the recursion working. 
  return count;
}


//my functions. Some are copied from tests to allow me to make my own tests.
shared_ptr<btree> BTree::init_node() 
{
  shared_ptr<btree> ret = shared_ptr<btree>(new btree);
  ret->num_keys = 0;
  ret->is_leaf = true;
  for (int i=0; i < BTREE_ORDER; i++)
  {
    ret->keys[i]=NULL;
  }
  for (int i=0; i <= BTREE_ORDER; i++) {
    ret->children[i] = NULL;
  }
  return ret;
}

shared_ptr<btree> BTree::build_node(int size, int* keys) 
{
  shared_ptr<btree> node = init_node();
  node->num_keys = size;
  for (int i=0; i < node->num_keys; i++) {
    node->keys[i] = keys[i];
  }
  return node;
}


bool BTree::almostFull(shared_ptr<btree> node)
{
  return(node->num_keys==4);
}
bool BTree::isFull(shared_ptr<btree> node)
{
  return (node->num_keys==5);
}

//Note: I initially tried to implement this using various strategies that did not 
//change the object stored at the memory pointed to by root. Thus test failed.
//Using shared_ptr<btree> parent(root)=init_node 
// or root=init_node() creates new memory. This is a huge mistake!
//because root=parent then sets root pointer to point to this new memory, and 
//original object at memory that is passed to test is unchanged.
//Using shared_ptr<btree> parent(root) points parent to root memory. Unnecessary. 
//You MUST alter root pointer directly, and reset values so root pointing to
//memory passes correct object to test.
//Also: function prototype that returns a shared_ptr<btree> is unnecessary.
void BTree::splitRoot(shared_ptr<btree> root)
{
  //create pointers to node to store left and right split around median.
  shared_ptr<btree> L=init_node();
  shared_ptr<btree> R=init_node();
  //assign leaf status of these two children nodes to be true.
  L->is_leaf=true;
  R->is_leaf=true;

  //if node doesn't have 5 keys, no need to split. 
  if(!isFull(root))
  {
    cout<<"Node is not full. Cannot be split"<<endl;
    return;
  }


  //First, split the values to the left of median into L node, 
  //and values to the right of median into right node.
     for(int i=0; i<2; i++)
    {
      L->keys[i]=root->keys[i];
      L->num_keys++;
    }
    R->keys[0]=root->keys[3]; 
    R->num_keys++;
    R->keys[1]=root->keys[4];
    R->num_keys++;

    //store median, to be new root value.
    int median=root->keys[2];
    
    //assign this to root,
    root->keys[0]=median;
    //then clear all "old" values in root that will later be in L and R.
    for(int i=1; i<5; i++)
    {
      root->keys[i]=0;
    }
    //fix root properties, and assign children.
    root->is_leaf=false;
    root->num_keys=1;
    root->children[0]=L;
    root->children[1]=R;
    

    return;
}

//after running find externally and making sure node is correct node to be split,
//split full node, move median of node into parent, and reassign children of parent.
void BTree::splitChild(shared_ptr<btree> root, shared_ptr<btree> node)
{
  //create pointers to node to store left and right split around median.
  shared_ptr<btree> L=init_node();
  shared_ptr<btree> R=init_node();
  shared_ptr<btree> parent=init_node();
  //assign leaf status of these two nodes based on if split node is a leaf
  L->is_leaf=node->is_leaf; 
  R->is_leaf=node->is_leaf;

  //if node doesn't have 5 keys, no need to split. 
  if(!isFull(node))
  {
    cout<<"Node is not full. Cannot be split"<<endl;
    return;
  }

  //else, if node is full, split it.
  else
  {
    //find the parent of the current node being split.
    //use node->keys[0] as a search value so correct parent is found.
    parent=findParent(root, node->keys[0]);
    
    //split current node into L and R.
    for(int i=0; i<2; i++)
    {
      L->keys[i]=node->keys[i];
      L->num_keys++;
    }
    R->keys[0]=node->keys[3]; 
    R->num_keys++;
    R->keys[1]=node->keys[4];
    R->num_keys++;

    //now, reassign children of parent...

    //First, find correct child index of the current node being split, by passing parent and a value.
    int n=findChild(parent, node->keys[0]);

    //insert median of node being split into parent.
    int median=node->keys[2];
    fillKeys(parent, median);

    //First, copy all children that are at least one spot greater than currently split child node
    //to one child spot higher.
      //1.find index of right most child node+1.
    int j=0;
    while(parent->children[j] && parent->children[j]->num_keys>0)
    {
      j++;
    }
      //2.start at this index(j), and copy values of previous child until j becomes one greater than split node index.
      //There is no need to copy children[n] and children[n+1] as these will be reassigned with L and R.
    for(j; j>n+1; j--)
    {
      parent->children[j]=parent->children[j-1];
    }
    //next, assign L and R split nodes in correct children spots.
    parent->children[n]=L;
    parent->children[n+1]=R;
    return;
  }
  return;
}

shared_ptr<btree> BTree::findParent(shared_ptr<btree> root, int key)
{
  shared_ptr<btree> parent=root;
  shared_ptr<btree> child;
  /*
  for (int k=0; k<parent->num_keys; k++)
  {
    cout<<parent->keys[k]<<" ";
  }
  */
  //if root has no children, return NULL
  if(root->is_leaf)
  {
    cout<<"No parent found for "<<key<<endl;
    return NULL;
  }

  else
  {
    int i=0;
    //if parent ptr reaches a leaf node, that means there is no valid parent.
    //exit loop then, and return NULL
    while(!parent->is_leaf)
    {
        for(i=0; i<parent->num_keys; i++)
        {
          //This loop finds correct child node to point child pointer to.
          if(key<parent->keys[i])
          {
            child=parent->children[i];
            //if correct child found, break out of current for loop
            break;
          }
          //NOTE: i exits as greater than loop condition.
          //This means just access i below (NOT i+1)
        }
        //This executes if child should point to right most child.
        //This occurs if key>final parent->keys[i] where i==parent->num_keys-1
        if(parent->children[parent->num_keys] && key>parent->keys[parent->num_keys-1])
        {
          child=parent->children[parent->num_keys];
        }
        //check children for child key. If found, return parent.
        for(int j=0; j<child->num_keys; j++)
        {
          if(key==child->keys[j])
          {
            cout<<"Parent FOUND of key: "<<key<<endl;
            for (int k=0; k<parent->num_keys; k++)
            {
              cout<<parent->keys[k]<<" ";
            }
            cout<<endl;
            return parent;
          }
        }
        //else, set parent==child pointer, reenter while loop to search further down tree.
        parent=child;
    }
  }

  cout<<"END: No parent found for "<<key<<endl;
  return NULL;
}

void BTree::fillKeys(shared_ptr<btree> node, int key)
{
  //first, use find() function to find correct node to insert key into. 
  shared_ptr<btree> ptr(node);
  
  if(isFull(ptr))
  {
    cout<<"Spot already has 5 keys."<<endl;
    return;
  }

  //find correct index, i, to insert key into.
  int i=0;
  while(i<ptr->num_keys && key>ptr->keys[i])
  {
    i++;
  }
  cout<<"i to insert "<<key<<" : "<<i<<endl;
  //move all indices starting at i one to the right, starting from rightmost value in keys[]
  for(int j=ptr->num_keys; j>i; j--)
  {
    ptr->keys[j]=ptr->keys[j-1];
  }
  //insert key into correct spot, num_keys++
  ptr->keys[i]=key;
  ptr->num_keys++;
  return;
}

shared_ptr<btree> BTree::build_two_tier_spaced()
{
   int valsRoot[] = { 10, 20, 30 };
  shared_ptr<btree> root = build_node(3, valsRoot);

  int vals_ch0[] = {5, 6, 7, 8};
  shared_ptr<btree> ch0 =  build_node(4, vals_ch0);

  int vals_ch1[] = {11, 12, 13, 14};
  shared_ptr<btree> ch1 =  build_node(4, vals_ch1);

  int vals_ch2[] = {21, 22, 23, 24};
  shared_ptr<btree> ch2 =  build_node(4, vals_ch2);

  int vals_ch3[] = {31, 32, 33, 34};
  shared_ptr<btree> ch3 =  build_node(4, vals_ch3);

  

  root->children[0] = ch0;
  root->children[1] = ch1;
  root->children[2] = ch2;
  root->children[3] = ch3;
  root->is_leaf = false;
  root->num_keys = 3;

  return root;
}

shared_ptr<btree> BTree::build_semi_full_two_tier() 
{
   //     [4,    7,     13,  ]
  //     /   |       |      \      
  //    /    |       |       \        
  // [1,3] [5,6] [8,11,12] [14,16,17,18] 

  int valsRoot[] = { 4, 7, 13 };
  shared_ptr<btree> root = build_node(3, valsRoot);

  int vals_ch0[] = { 1, 3 };
  shared_ptr<btree> ch0 =  build_node(2, vals_ch0);

  int vals_ch1[] = { 5, 6 };
  shared_ptr<btree> ch1 =  build_node(2, vals_ch1);

  int vals_ch2[] = { 8, 11, 12 };
  shared_ptr<btree> ch2 =  build_node(3, vals_ch2);

  int vals_ch3[] = { 14, 16, 17, 18 };
  shared_ptr<btree> ch3 =  build_node(4, vals_ch3);

  

  root->children[0] = ch0;
  root->children[1] = ch1;
  root->children[2] = ch2;
  root->children[3] = ch3;
  root->is_leaf = false;
  root->num_keys = 3;

  return root;
}

shared_ptr<btree> BTree::build_full_two_tier() {
  //     [4,    7,        13,        20]
  //     /   |       |           |      \
  //    /    |       |           |       \
  // [1,3] [5,6] [8,11,12] [14,16,17,18] [23,24,25,26]
  int valsRoot[] = { 4, 7, 13, 20 };
  shared_ptr<btree> root = build_node(4, valsRoot);

  int vals_ch0[] = { 1, 3 };
  shared_ptr<btree> ch0 =  build_node(2, vals_ch0);

  int vals_ch1[] = { 5, 6 };
  shared_ptr<btree> ch1 =  build_node(2, vals_ch1);

  int vals_ch2[] = { 8, 11, 12 };
  shared_ptr<btree> ch2 =  build_node(3, vals_ch2);

  int vals_ch3[] = { 14, 16, 17, 18 };
  shared_ptr<btree> ch3 =  build_node(4, vals_ch3);

  int vals_ch4[] = { 23, 24, 25, 26 };
  shared_ptr<btree> ch4 =  build_node(4, vals_ch4);

  root->children[0] = ch0;
  root->children[1] = ch1;
  root->children[2] = ch2;
  root->children[3] = ch3;
  root->children[4] = ch4;
  root->is_leaf = false;
  root->num_keys = 4;

  return root;
}

shared_ptr<btree> BTree::build_thin_three_tier() {
  int valsRoot[] = { 13 };
  shared_ptr<btree> root = build_node(1, valsRoot);

  int vals_ch0[] = { 4, 7 };
  shared_ptr<btree> ch0 =  build_node(2, vals_ch0);

  int vals_ch1[] = { 17, 24 };
  shared_ptr<btree> ch1 =  build_node(2, vals_ch1);

  root->is_leaf = false;
  root->children[0] = ch0;
  root->children[1] = ch1;
  ch0->is_leaf = false;
  ch1->is_leaf = false;

  int leaf_ch0[] = { 1, 3 };
  shared_ptr<btree> l0 =  build_node(2, leaf_ch0);
  
  int leaf_ch1[] = { 5, 6 };
  shared_ptr<btree> l1 =  build_node(2, leaf_ch1);
  
  int leaf_ch2[] = { 11, 12 };
  shared_ptr<btree> l2 =  build_node(2, leaf_ch2);

  ch0->children[0] = l0;
  ch0->children[1] = l1;
  ch0->children[2] = l2;
  
  int leaf_r0[] = { 14, 16 };
  shared_ptr<btree> r0 =  build_node(2, leaf_r0);
  
  int leaf_r1[] = { 19, 23 };
  shared_ptr<btree> r1 =  build_node(2, leaf_r1);
  
  int leaf_r2[] = { 25, 26 };
  shared_ptr<btree> r2 =  build_node(2, leaf_r2);
  
  ch1->children[0] = r0;
  ch1->children[1] = r1;
  ch1->children[2] = r2;

  return root;
}
