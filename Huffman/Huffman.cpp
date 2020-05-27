#include "Huffman.h"

// constructor, initialize class variables and pointers here if need.
Huffman::Huffman()
{
  //blank on purpose.
}

//deconstructor,
Huffman::~Huffman(){
}

//Inits node.
shared_ptr<freq_info> Huffman::CreateLeaf(char symbol, int count) 
{
  shared_ptr<freq_info> ptr(new freq_info);
  ptr->symbol=symbol;
  ptr->count=count;
  ptr->left=NULL;
  ptr->right=NULL;
  ptr->is_leaf=true;
  
  return ptr;
}

  //Creates an internal node from left and right.
shared_ptr<freq_info> Huffman::CombineNodes(shared_ptr<freq_info> left, shared_ptr<freq_info> right) 
{
  shared_ptr<freq_info> ptr(new freq_info);
  ptr->left=left;
  ptr->right=right;
  ptr->is_leaf=false;
  ptr->count=left->count+right->count;
  return ptr;
}

// IncrementLookup will add one to the value associated with the
  // symbol, or if the symbol is not yet a key in the map, it will
  // create a mapping lookup[symbol] = 1.
void Huffman::IncrementLookup(map<char, int>& lookup, char symbol) 
{
  //if map[symbol] does not exist, create a pair and insert it.
  if(lookup.find(symbol)==lookup.end())
  {
    lookup.insert(make_pair(symbol, 1));
  }
//else, increment map[symbol]
  else
  {
    lookup[symbol]++;
  }
}

 // LoadQueue turns each key/value pair in the lookup table into a
// freq_info pointer, and pushes it into the provided priority queue
void Huffman::LoadQueue(const map<char, int>& lookup, tree_queue& q) 
{
  shared_ptr<freq_info> ptr(new freq_info);
  //iterate through map, initialize leaf with(c, n),
  //store in ptr, push ptr onto q.
  for (auto it = lookup.cbegin(); it != lookup.cend(); it++) 
  {
  char c = (*it).first;
  int n =  (*it).second;
  ptr=CreateLeaf(c, n);
  //note that ptr-> left==NULL and ->right==NULL
  q.push(ptr);
  }
}

  // BuildTree creates a Huffman codec tree (tree_queue) using the values contained
  // in the provided priority queue. it returns a pointer to the root
  // node.
shared_ptr<freq_info> Huffman::BuildTree(tree_queue& q) 
{
  //The strategy here is to create a new internal node 
  //out of two highest priority nodes on q (OR two nodes w/ lowest counts/freqs)
  //after accessing and popping these two nodes, and push internal node onto q.
  //Do this until q has only one (root) node.
   shared_ptr<freq_info> root(new freq_info);
   shared_ptr<freq_info> L(new freq_info);
   shared_ptr<freq_info> R(new freq_info);
   root=NULL;
   L=NULL;
   R=NULL;

   while(q.size()>1)
   {
     //store lowest count node
     L=q.top();
     q.pop();
     //store second lowest count node
     R=q.top();
     q.pop();
     //create internal node, push onto q.
     //Internal-> left=L, ->right=R.
     root=CombineNodes(L, R);
     q.push(root);
   }

  return root;
}
//This is a recursive helper function that builds encoding map, called by BuildEncodingTable.

void Huffman::BuildMap(shared_ptr<freq_info>& root, map<char, string>& m, string str) 
{
  if(root->is_leaf)//if leaf node, that contains char(symbol)
  {
    //Stopping case.
    //Insert map[symbol]=str into m
    m.insert(make_pair(root->symbol, str));
  }
  else
  {
    if(root->left)
    {
    //recur left, adding LEFT_CHAR onto string until leaf node reached.
    BuildMap(root->left, m, str+LEFT_CHAR);
    }
    if(root->right)
    {
    //recur right, adding RIGHT_CHAR onto string until leaf node reached
    BuildMap(root->right, m, str+RIGHT_CHAR);
    }
  }
}
//returns encoding table of map<char, string> where string is huffman code. 
map<char, string> Huffman::BuildEncodingTable(shared_ptr<freq_info> root) 
{
  map<char, string> m;
  string str="";

  if (root) 
    { 
      BuildMap(root, m, ""); 
    }
    
  return m;
 
}
  // Encode returns an encoded string using the provided encoding lookup
  // table on the input string.
string Huffman::Encode(map<char, string> enc_table, string input) 
{
  string ans="";
  
  for (unsigned i=0; i<input.size(); i++)
  {
    char c=input[i];
    //lookup huffman code for each char in encoding table, concatenate onto string.
    ans+=enc_table[c];
  }
  return ans;
}

//Decode converts string of huffman codes back into original chars.
//It does this by moving left down tree if LEFT_CHAR encountered,
//Moving right down tree if RIGHT_CHAR encountered,
//and if a root is found, appending the char found in root to decoded string.
string Huffman::Decode(shared_ptr<freq_info> root, string input) 
{
  shared_ptr<freq_info> ptr(new freq_info);
  ptr=root;
  string ans="";
  for(unsigned i=0; i<input.size(); i++)
  {
    char c=input[i];
    //if c is left char, move left down tree.
    if (c=='.') //LEFT_CHAR is a string, this is easier to use char to compare.
    {
      ptr=ptr->left;
    }
    //if c is right char, move right down tree.
    else if (c=='^')
    {
      ptr=ptr->right;
    }
    //if leaf is reached, then concatenate leaf->symbol onto string to decode, 
    //and reset pointer to point to root
    if(ptr->is_leaf)
    {
      ans+=ptr->symbol;
      ptr=root;
    }
  }
  return ans;
}