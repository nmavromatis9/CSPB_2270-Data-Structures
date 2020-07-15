#include "Treap.h"
using namespace std;


Treap::Treap()
{
    //left blank on purpose.
    //do not call srand() here. Not as random as in main().
}

Treap::~Treap()
{

}

//This returns a random priority between 0-99 inclusive.
int Treap::randPriority()
{
  //generates random int from 0-99
  int r=rand()%100;
  //cout<<r<<endl;
  return r;
}

//This creates a new Treap node with c as main key,
//and random priority.
shared_ptr<Node> Treap::initNode(char c)
{
    shared_ptr<Node> ret(new Node);
    ret->c=c;
    ret->left=NULL;
    ret->right=NULL;
    ret->priority=randPriority();
    //cout<<"priority= "<<ret->priority<<endl;
    
    return ret;
}

 //build a random Treap of 15 random uppercase chars. 
 Treap Treap::buildTreap()
 {
     Treap T;
     for(int i=0; i<15; i++)
     {
         //randomly generate an uppercase Char.
         //90 is ascii value of 'Z',
         //65 is ascii value of 'A' 
         //so subtracting 0-25 from 90 makes sure all chars in range A-Z
        char c = (90 - (rand() % 26));
            //cout<<c<<endl;
        //insert this rand char with rand priority into Treap.
        T.insert(c);
     }

     return T;
 }

//Builds a Treap from vector of chars.
 Treap Treap::buildTreap(vector<char> v)
 {
     Treap T;
     int s=v.size();
     for (int i=0; i<s; i++)
     {
         T.insert(v[i]);
     }
     return T;
 }

//Inserts Node with char c into leaf of treap pointed to by root.
//rotate this Node to maintain treap properties.
void Treap::insert(shared_ptr<Node>& root, char c)
{
    //This is a recursive stopping case, 
    //that inserts newNode into correct NULL spot.

    //The private insert() function also calls this on private Root variable.
    //so it sets Root if Root was previously NULL.
    if (!root) 
    {
      root = initNode(c);
      return;
    }
    
    //Do not allow duplicate main keys.
    if(root && c==root->c)
    {
        //cout<<"No insert done, duplicate key: "<<c<<endl;
        return;
    }
    //If main key (c) of new node is less than the root's:
    if (c<root->c)
    {
        //insert in left subtree by calling insert root->left recursively.
        //This could update root->left, then call next line to correct heap.
        insert(root->left, c);
        //if the root's left child now has a greater priority, rotate right at the root.
        if (root->left != NULL && root->left->priority > root->priority)
        {
            root=rotateRight(root);
            //cout<<"Right Rotation."<<endl;
        }
    }
    //else if main key is greater than root's main key:
    else if (c>root->c)
    {
        //insert in right subtree by calling insert root->right recursively.
        //This could update root->right, then call next line to correct heap.
        insert(root->right, c);
        //if the root's right child now has a greater priority, rotate left at the root.
        if (root->right!= NULL && root->right->priority > root->priority)
        {
            root=rotateLeft(root);
            //cout<<"Left Rotation. "<<endl;
        }
    }
    //must include final return.
    return;

}

//rotateLeft at root to maintain treap invariant.
shared_ptr<Node> Treap::rotateLeft(shared_ptr<Node> root)
{
    //Rotate left:
    //Old right child becomes new root, 
    //Old root becomes left child of new root,
    //Old root->right->left becomes new root->left->right.
    shared_ptr<Node> R=root->right;
    shared_ptr<Node> RL=root->right->left;
    R->left=root;
    root->right=RL;
    //This line is important to update subtree, so that root is updated.
    root=R;
    return root;
}

//rotateRight at root to maintain treap invariant.
shared_ptr<Node> Treap::rotateRight(shared_ptr<Node> root)
{
     //Rotate right:
    //Old left child becomes new root, 
    //Old root becomes right child of new root,
    //Old root->left->right becomes new root->right->left.
    shared_ptr<Node> L=root->left;
    shared_ptr<Node> LR=root->left->right;
    L->right=root;
    root->left=LR;
    root=L;
    return root;
}

//To remove a node, it is rotated until it becomes a leaf, then removed.
void Treap::remove(shared_ptr<Node>& root,  char c)
{
    //NULL case must be included.
    if(!root)
    {
        return;
    }

    //first, find the node with the char to be deleted.
    //if the char to be deleted is less than that of current node, recur left.
    if(c<root->c)
    {
        remove(root->left, c);
    }
    //else if the char to be deleted is greater than that of current node, recur right.
    else if (c>root->c)
    {
        remove(root->right, c);
    }
    //else if the current node contains the char to be deleted:
    else if(root->c==c)
    {
        //if node has no children, or is a leaf, simply delete it.
        if(!root->left && !root->right)
        {
            //set root to NULL
            root=nullptr;
            return;
        }

        //else, rotate until current node becomes a leaf.

        //if there is no right child, or if there are two children
        //with the left's priority greater than the right's, rotate right.
        //This is so higher priority left child becomes parent.
        if (!root->right || (root->left && root->right && root->left->priority > root->right->priority))
                {
                    root=rotateRight(root);
                    //recursively call remove on right child, 
                    //b/c node to be deleted will now be right child of root.
                    remove(root->right, c);
                }
        // if opposite conditions are true, rotate left.
        else if(!root->left || (root->left && root->right && root->left->priority<root->right->priority))
        {
            root=rotateLeft(root);
            //recursively call remove on left child, 
            //b/c node to be deleted will now be left child of root.
            remove(root->left, c);
        }
    }
   return; 
}

//searches for and returns Node with char c.
shared_ptr<Node> Treap::search(shared_ptr<Node>& root,  char c)
{
    //stopping case, executed if empty tree, or char not found.
    if (!root)
    {
        cout<<c<<" NOT found."<<endl;
        return NULL;
    }
    //if char found in current node, return it.
    if(root->c==c)
    {
        cout<<root->c<<" found"<<endl;
        return root;
    }
    //if search char < current node, search in left subtree recursively.
    else if(c<root->c)
    {
        search(root->left, c);
    }
    //if search char > current node, search in right subtree recursively.
    else if(c>root->c)
    {
        search(root->right, c);
    }
    //This is crucial, or else seg faults occur. 
    return NULL;
}

//inorder traversal and printing of tree.
void Treap::print(shared_ptr<Node> root)
{
    //recursive stopping case.
    if (!root) 
    {
       return; 
    }
  
    //recur on left child.
   print(root->left); 
  
    //output char in current node.
    cout << root->c << " "; 
  
   //recur on left child.
    print(root->right); 
} 

//converts treap to a vector inOrder, to later run set operations.
 void Treap::toVector(shared_ptr<Node> root, vector<char>&res)
{

    //recursive stopping case or empty tree.
  if(!root)
  {
    return;
  }
  
  //Use recursion on left child.
  toVector(root->left, res);

  //store value of current node in vector.
  res.push_back(root->c);

  //Use recursion on right child.
  toVector(root->right, res);
}

//returns a vector of chars of the intersection of two Treaps.
vector<char> Treap::findIntersection(shared_ptr<Node> A, shared_ptr<Node> B)
{
    //stores inOrder vector of treap pointed to by A
    vector<char>a;
    toVector(A, a);
    int sizeA=a.size();
    //stores inOrder vector of treap pointed to by B
    vector<char>b;
    toVector(B, b);
    int sizeB=b.size();
    //stores intersection of both trees.
    vector<char>r;
    //iterate over each element in larger vector, check if element exists in smaller vector.
    if(sizeB>sizeA)
    {
        //iterate over each element in larger vector.
        for (int i=0; i<sizeB; i++)
        {
            //store char of larger vector
            char c=b[i];
            //iterate over each element in smaller vector, and check for char
            for(int i=0; i<sizeA; i++)
            {
                //if it exists, save it in r vector.
                if (c==a[i])
                    r.push_back(c);
            }
        }
    }
   
    //This else executes if a.size()>=b.size()
    else
    {
        //iterate over each element in larger vector.
        for (int i=0; i<sizeA; i++)
        {
            //store each char.
            char c=a[i];
            //iterate over each element in smaller vector, and check for char
            for (int i=0; i<sizeB; i++)
            {
                //if it exists, save it in r vector.
                 if (c==b[i])
                    r.push_back(c);
            }
        }
    }
    cout<<"Intersection of two sets: "<<endl;
    int rSize=r.size();
    if(rSize==0)
    {
        cout<<"Empty Set"<<endl;
    }
    else
    {
        for (int i=0; i<rSize; i++)
        {
            cout<<r[i]<<" ";
        }
        cout<<endl;
    }
    
    return r;
}

//returns a vector of chars of the union of two Treaps.
vector<char> Treap::findUnion(shared_ptr<Node> A, shared_ptr<Node> B)
{
    //stores inOrder vector of treap pointed to by A
    vector<char>a;
    toVector(A, a);
    int sizeA=a.size();
    //stores inOrder vector of treap pointed to by B
    vector<char>b;
    toVector(B, b);
    int sizeB=b.size();
    //stores union
    vector<char>r;
    //iterate over each element in larger vector, check if element exists in smaller vector.
    if(sizeB>sizeA)
    {
        //iterate over each element in larger vector.
        for (int i=0; i<sizeB; i++)
        {
            //push back each element to union vector.
            r.push_back(b[i]);
        }
        //iterate over each element in smaller vector, 
        //check if each char in smaller vector is in r already.
        
        for(int i=0; i<sizeA; i++)
        {
            int sizeR=r.size();
            char c=a[i];
            bool add=true;
            //iterate over each element in r.
            for (int i=0; i<sizeR; i++)
            {
                //if char already exists in r, do not push it back.
                if (c==r[i])
                    add=false;
            }
            //if char does not exist in r, push it back.
            if (add)
            {
                r.push_back(c);
            }
            
        }
        
    }
   
    //This else executes if a.size()>=b.size()
    else
    {
       //iterate over each element in larger vector.
        for (int i=0; i<sizeA; i++)
        {
            //push back each element to union vector.
            r.push_back(a[i]);
        }
        //iterate over each element in smaller vector, 
        //check if each char in smaller vector is in r already.
        
        for(int i=0; i<sizeB; i++)
        {
            int sizeR=r.size();
            char c=b[i];
            bool add=true;
            //iterate over each item in r
            for (int i=0; i<sizeR; i++)
            {
                //if char already exists in r, do not push back.
                if (c==r[i])
                    add=false;
            }
            //if that char does not exist already in r, store it in r.
            if (add)
            {
                r.push_back(c);
            }
            
        }
    }
    cout<<"Union of two sets: "<<endl;
    int rSize=r.size();
    if(rSize==0)
    {
        cout<<"Empty Set"<<endl;
    }
    else
    {
        for (int i=0; i<rSize; i++)
        {
            cout<<r[i]<<" ";
        }
        cout<<endl;
    }
    
    return r;
}

//returns a vector of chars of the difference A-B
vector<char> Treap::findDifference(shared_ptr<Node> A, shared_ptr<Node> B)
{
    //stores inOrder vector of treap pointed to by A
    vector<char>a;
    toVector(A, a);
    int sizeA=a.size();
    //stores inOrder vector of treap pointed to by B
    vector<char>b;
    toVector(B, b);
    int sizeB=b.size();
    //stores difference of A-B
    vector<char>r;
    
    //iterate over each element in first vector.
    for(int i=0; i<sizeA; i++)
    {
        char c=a[i];
        bool add=true;
        //iterate over each element in second vector
        //check if second vector contains that char.
        for(int i=0; i<sizeB; i++)
        {
            //if char is found in both, do not add it to r.
            if(c==b[i])
                add=false;
        }
        //if char only found in first vector, store it.
        if(add)
        {
            r.push_back(c);
        }
    }
    
    cout<<"Difference of two sets, A\\B: "<<endl;
    int rSize=r.size();
    if(rSize==0)
    {
        cout<<"Empty Set"<<endl;
    }
    else
    {
        for (int i=0; i<rSize; i++)
        {
            cout<<r[i]<<" ";
        }
        cout<<endl;
    }
    return r;
}

