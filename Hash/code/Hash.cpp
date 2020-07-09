#include "Hash.h"

// implemented for you - don't change this one
unsigned int DJB2(std::string key){
  unsigned int hash = 5381;
  // Leaving the debugging stuff commented out, in case you want to
  // play. It will output the hash at each incremental step so you can
  // see how it takes shape.
  //
  //  cout << "Hashing string \"" << key << "\"" << endl;
  //  cout << bitset<32>(hash) << " " << hash << endl;
  for (size_t i=0; i < key.length(); i++) {
    char c = key[i]; 
    hash = ((hash << 5) + hash) + c;
    // cout << bitset<32>(hash) << " " << hash << endl;
  }
  // cout << "Hashed string \"" << key << "\" to " << hash << endl;
  //
  // for light reading on why djb2 might not be the best
  // production-grade hash function, go to
  // http://dmytry.blogspot.com/2009/11/horrible-hashes.html
  return hash;
}

// implemented for you - don't change this one
unsigned int ModuloBucketFunc(unsigned int hashcode, unsigned int cap){
  unsigned int b = hashcode % cap;
  return b;
}

// constructor, initialize class variables and pointers here if need.
Hash::Hash(){
  // left blank on purpose
}

//deconstructor,
Hash::~Hash(){
}


  // table points to dynamic array of hash_node pointers. it should be
  // initialized to a dynamic array of pointers to hash_node
  // structs. those pointers shoudl all initially be NULL.
shared_ptr<hash_table> Hash::InitTable(unsigned int cap)
{
  //create a new ptr to hash_table, the overarching structure.
  shared_ptr<hash_table> ret(new hash_table);
  //create a new htable, which is defined as: vector<shared_ptr<hash_node>> htable;
  //size of vector is created as capacity.
  ret->table = shared_ptr<htable>(new htable(cap));
  //set all other default parameters.
  ret->capacity=cap;
  ret->size=0;
  ret->occupied=0;
  ret->hash_func = DJB2;
  ret->bucket_func = ModuloBucketFunc;
  return ret;
}

//initializes hash_node (ptr), which will be later stored in typedef vector<shared_ptr<hash_node>> htable;
//within struct hash_table {shared_ptr<htable> table;}
shared_ptr<hash_node> Hash::InitNode(std::string key, unsigned int hashcode, std::string val)
{
  shared_ptr<hash_node> ret(new hash_node);
  ret->deleted=false;
  ret->key=key;
  ret->hashcode=hashcode;
  ret->value=val;
  return ret;
}

//NOTE: This is basically the same as insert after calculating hash code and bucket.

// SetKVP establishes a mapping between the given key and value pair
  // in the provided hash table. if the key (as identified by its hash
  // code) is already in the hash table, its value is potentially
  // updated. otherwise a new key/value pair is added to the hash table.
  //
  // on exit, the size and occupancy of the hash table is increased if a
  // new key/value pair was added.
  //
  // if there is no room in the hash table, return false. 
  //
  // the return value should be true unless there was no room in the
  // hash table.
bool Hash::SetKVP(shared_ptr<hash_table> tbl, std::string key, std::string value)
{
  //if occupied==capacity, then tbl is full.
  if(tbl->occupied==tbl->capacity)
  {
    return false;
  }
  //keep track of num probed so that infinite loops don't happen
  unsigned int nProbed=0;
  //first, calculate the hashcode based on the passed key.
  unsigned int code=tbl->hash_func(key);
  //Initialize Node with this hashcode 
  shared_ptr<hash_node> new_node=InitNode(key, code, value);
  //next, use this hashcode to calc correct initial bucket (index) to put hashcode in.
  int index= tbl->bucket_func(code, tbl->capacity);
  //Linear probe: Keep probing until empty spot is located.
  //or update key with new value if key is already found in table.

  //if table->at(index)!=NULL means that there is already a hashcode stored at index.
  //so scroll until NULL (empty) index found, or kvp in code bucket found to already exist.
  while(tbl->table->at(index)!=NULL && nProbed<tbl->capacity) 
  {
    //if hashcode does not already exist at (non-empty) spot:
    if((tbl->table->at(index)->hashcode != code))
    {
    //increment index. Wrap around size of capacity, so it is never greater than capacity.
      index = (index + 1) % tbl->capacity;
      //increment num probed so infinte loops don't occur.
      ++nProbed;
    }

    //if hashcode already exists, update code with new value by breaking out of loop.
    else 
    {
      break;
    }
  }

//if nProbed==capacity, that means there is no free spot to insert.
if(nProbed==tbl->capacity)
{
  return false;
}

  //if we are adding to empty spot, increase size and occupied member vars.
  if (tbl->table->at(index)==NULL) 
  {
    tbl->occupied++;
    tbl->size++;   
  }

  //insert node into correct NULL or already occupied (matching hashcode) bucket.
  tbl->table->at(index) = new_node;

  return true;
}

//returns size/capacity, which is more standard.
float Hash::Load(shared_ptr<hash_table> tbl)
{
  //must cast unsigned ints into floats.
  float load=(float)tbl->size/(float)tbl->capacity;
  return load;
}

 // GetVal returns the value associated with the provded key in the
  // table, or the empty string "" if no such mapping exists (or if
  // there is a mapping but it is deleted).
std::string Hash::GetVal(shared_ptr<hash_table> tbl, std::string key)
{
  //first, calc hashcode from the key to know where to first look in table.
  unsigned int code=tbl->hash_func(key);
  //next, calc index (bucket) to look in from hashcode.
  int index= tbl->bucket_func(code, tbl->capacity);
  //keep track of num probed so that infinite loops don't happen
  int unsigned nProbed=0;
  //First, look in this index. If it is NULL, it means value is not present.
  if(tbl->table->at(index)==NULL)
  {
    return "";
  }
  else
  {
    //Linear probe: Keep probing until empty spot is located, or hashcode is found.

    //if table->at(index)!=NULL means that there is already a hashcode stored at index.
    //so scroll until NULL (empty) index found, or current hashcode is found.
    while(tbl->table->at(index)!=NULL && nProbed<tbl->capacity) 
      {
        //keep scrolling if current bucket does not contain hashcode to account for linear probing
        if((tbl->table->at(index)->hashcode != code))
        {
        //increment index. Wrap around size of capacity, so it is never greater than capacity.
          index = (index + 1) % tbl->capacity;
          ++nProbed;
        }
      //if hashcode is found, break out of loop, so value at that index can be returned.
        else
        {
          break;
        }
      }
  }

  //if an index is found that matches hashcode, that means value is found. Return that string.
  if((tbl->table->at(index)) && tbl->table->at(index)->hashcode==code)
  {
    return tbl->table->at(index)->value;
  }

  //if hashcode not already stored in table, return empty string.
  return "";
}

  // Contains returns true if the table has a non-deleted node whose
  // hashcode matches the given key's hashcode.
bool Hash::Contains(shared_ptr<hash_table> tbl, std::string key)
{
  //first, calc hashcode from the key to know where to look in table.
  unsigned int code=tbl->hash_func(key);
  //next, calc index (bucket) to look in from hashcode.
  int index= tbl->bucket_func(code, tbl->capacity);
  //keep track of num probed so that infinite loops don't happen
  unsigned int nProbed=0;
  //check this spot first. If found and not deleted, return true
  //NOTE: (tbl->table->at(index) must be first to avoid segmentation fault for accessing NULL index.
  if((tbl->table->at(index)) && (tbl->table->at(index)->hashcode==code) && (tbl->table->at(index)->deleted==false))
  {
    return true;
  }
  else
  {
  //linear probe to look in other spots.

    //if table->at(index)!=NULL means that there is already a hashcode stored at index.
    //so scroll until NULL (empty) index found, or correct hashcode is found.
    while(tbl->table->at(index)!=NULL && nProbed<tbl->capacity) 
      {
       //if code in bucket does not match current, scroll forward.
        if((tbl->table->at(index)->hashcode != code))
        {
        //increment index. Wrap around size of capacity, so it is never greater than capacity.
          index = (index + 1) % tbl->capacity;
          ++nProbed;
        }
     //if hashcode found, break out of loop to check if it is not deleted.
        else
        {
          break;
        }
      }

    //if nProbed==capacity, that means that key was not found. 
    if(nProbed==tbl->capacity)
    {
      return false;
    }
    //now check that value at index not already deleted.
    if((tbl->table->at(index)) && (tbl->table->at(index)->hashcode==code) && (tbl->table->at(index)->deleted==false))
    {
      return true;
    }
  }

  return false;
}

  // Remove marks as 'deleted' any existing non-deleted hash_node with
  // the same hashcode as the provided key's hashcode. if it finds such
  // a hash node, it decrements the table's size (but not occupancy) and
  // returns true. it returns false otherwise.
bool Hash::Remove(shared_ptr<hash_table> tbl, std::string key)
{
  //first, calc hashcode from the key to know where to look in table.
  unsigned int code=tbl->hash_func(key);
  //next, calc index (bucket) to look in from hashcode.
  int index= tbl->bucket_func(code, tbl->capacity);
  //keep track of num probed so that infinite loops don't happen
  unsigned int nProbed=0;
  //if hashcode found at expected index, "delete" it
  if((tbl->table->at(index)) && tbl->table->at(index)->hashcode==code)
  {
    tbl->size--;
    //mark as deleted.
    tbl->table->at(index)->deleted=true;
    return true;
  }
  //else, linear probe.
  else
  {
     //if table->at(index)!=NULL means that there is a hashcode stored at index.
    //so scroll until NULL (empty) index found, or current hashcode is found.
    while(tbl->table->at(index)!=NULL && nProbed<tbl->capacity) 
      {
        //scroll forward if current hashcode not found.
        if((tbl->table->at(index)->hashcode != code))
        {
        //increment index. Wrap around size of capacity, so it is never greater than capacity.
          index = (index + 1) % tbl->capacity;
          ++nProbed;
        }
      //if hashcode found, break out of loop to delete it.
        else
        {
          break;
        }
      }

    //if nProbed==capacity, that means that key was not found. 
    if(nProbed==tbl->capacity)
    {
      return false;
    }

    //now delete node at this index found by probing.
    if((tbl->table->at(index)) && tbl->table->at(index)->hashcode==code)
    {
      tbl->size--;
      tbl->table->at(index)->deleted=true;
      return true;
    }
  }

  return false;
}

//Resize creates a tbl of greater size, and copies all old values to new bucket locations.
void Hash::Resize(shared_ptr<hash_table> tbl, unsigned int new_capacity)
{
    shared_ptr<hash_table> newTbl=InitTable(new_capacity);
    //old capacity. Use this and NOT size, which does not account for each bucket.
    int currentCap=tbl->capacity;
    int idx=0;
    //iterate over each bucket, while idx<original tbl size.
    while(idx<currentCap)//I tried <currentSize, did NOT work.
    //that did NOT scan each bucket, where some might be filled or empty.
    {
      //if this bucket is not NULL, then reinsert into newTbl
      if(tbl->table->at(idx)!=NULL)
      {
        //no need to recalculate new code and idx here, this is calculated in setKVP 
        //from original key and new cap.
        //insert into newTbl
        SetKVP(newTbl, tbl->table->at(idx)->key, tbl->table->at(idx)->value);
      }
      //scroll to next bucket.
      ++idx;
    }
  //Now, update original tbl to be replaced with newTbl.
  tbl->table=newTbl->table;
  tbl->capacity=new_capacity;
  return;
}

// implemented for you - feel free to change this one if you like
void Hash::PrintTable(shared_ptr<hash_table> tbl){
  cout << "Hashtable:" << endl;
  cout << "  capacity: " << tbl->capacity << endl;
  cout << "  size:     " << tbl->size << endl;
  cout << "  occupied: " << tbl->occupied << endl;
  cout << "  load:     " << Load(tbl) << endl;
  if (tbl->capacity < 130) {
    for (unsigned int i=0; i < tbl->capacity; i++) {
      cout << "[" << i << "]    ";
      if (!tbl->table->at(i)) {
        cout << "<empty>" << endl;
      } else if (tbl->table->at(i)->deleted) {
        cout << "<deleted>" << endl;
      } else {
        cout << "\"" << tbl->table->at(i)->key << "\" = \"" << tbl->table->at(i)->value << "\"" << endl;
      }
    }
  } else {
    cout << "    <hashtable too big to print out>" << endl;
  }
}

