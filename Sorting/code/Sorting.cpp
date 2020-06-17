#include "Sorting.h"
#include <iostream>
using namespace std;

/*
  Please refer to sorting.h for documentation on each function.

   + ------ N O T E: -- Big scary warning! -----------------------------\
   |                                                                    |
   |    We clearly can't use unit testing to ensure that you're         |
   |    actually implementing the correct algorithm. I suppose we could |
   |    write some complicated static analysis checker. But it is       |
   |    easier to just look at it with our eyeballs.                    |
   |                                                                    |
   |    After the assignment is due, we will look at the most recent    |
   |    version of your implementation that got the highest score and   |
   |    make sure you're not doing something sneaky like using a        |
   |    standard library call to sort a vector.                         |
   |                                                                    |
   |    Anyone caught doing this (even though it is kinda funny) will   |
   |    be given 0 points on the assignment.                            |
   |                                                                    |
   `--------------------------------------------------------------------/ 
*/

// constructor, initialize class variables and pointers here if you need.
Sorting::Sorting(){
  // Left blank on purpose.
}

//deconstructor,
Sorting::~Sorting(){
}

//My functions
//prints all values in vector 
 void Sorting::print(const vector<int>& data)
 {
   for (unsigned int i=0; i<data.size(); i++)
   {
     cout<<data[i]<<" ";
   }
   cout<<endl;
 }
//passes two pointers, swaps values stored at those two pointers.
//pass by reference, so that pointers point to memory of vector.at(index) locations.
 void Sorting::swap(int* val1, int* val2)
 {
   int temp=*val1;//store value pointed to by val1.
   *val1=*val2;
   *val2=temp;
 }

  //quicksort is a recursive function that calls the helper function quicksort_partition()
  //Divide and conquer:It selects high_idx as the pivot value,
  //Then sorts all elements less than pivot before pivot,
  //All elements greater than pivot after pivot, and finally places pivot in correct spot.
  //quicksort_partition does most of the heavy lifting of this process.
  //It then recursively repeats this process on both sub-vectors(greater and less than the pivot)

void Sorting::quicksort(vector<int>& data, int low_idx, int high_idx)
{
  //stopping condition is if(low_idx>=high_idx)
  if(low_idx<high_idx)
  {
    //recursively sort sub-vectors.
    //store index of final pivot location as partition.
    int part = quicksort_partition(data, low_idx, high_idx);  
    //recursively sort left of partition.
    quicksort(data, low_idx, part-1);
    //recursively sort right of partition. 
    quicksort(data, part+1, high_idx);
  }
}

 
  //This sorts vector so elements less than pivot are to left of pivot,
  //and elements greater than pivot are to right of pivot.
  //returns final index of pivot after placing pivot in right spot.
int Sorting::quicksort_partition(vector<int>& data, int low_idx, int high_idx)
{
  //store pivot value of high_idx as p
  int p=data.at(high_idx);
  //eventually, store index of element smaller than pivot at i.
  int i=low_idx;
  //j accesses current element of comparison.
  for (int j=low_idx; j<=high_idx-1; j++ )
  {
    //if current element smaller than pivot:
    if (data.at(j)<p)
    {
      //swap these values so that element (j) which smaller than p placed at i.
      //Increment i.
      swap(&data.at(i), &data.at(j));
      i++;
    }
  }
  //place pivot at correct location.
  swap(&data.at(i), &data.at(high_idx));
  //return index of this pivot, so that sub vectors surrounding pivot can then be sorted.
  return i;
}

//repeatedly swaps adjacent elements if they are out of order.
void Sorting::bubblesort(vector<int>& data)
{
  int s=data.size();
  //run loop size-1 times.
  for (int i=0; i<s-1; i++)
  {
    //after each outer iteration, final i elements are already in place. 
    //-1 is in loop because .at(j) compared to .at(j+1) 
    //j is var used to compare adjacent elements.
    for (int j=0; j<s-1-i; j++)
    {
      if(data.at(j)>data.at(j+1))
      {
        swap(&data.at(j), &data.at(j+1));
      }
    }
  }
}

//This recursively splits the list into Left and Right halves
//until each sublist has only one or zero values. Then merge() is called 
//to merge these parts in order. 
void Sorting::mergesort(vector<int>& data)
{
  //If data has 0 or 1 members, there is no need to sort anything.
  //This is also a recursive stopping case, because we want to split vector into halves
  //until each resulting vector has one member.
  if (data.size()<=1)
  {
    return;
  }
  
  else
  {
    //declare vectors for left and right halves.
    vector<int> L;
    vector<int> R;
    //find middle value to split halves around.
    unsigned int m=(data.size())/2;
    //cout<<"m= "<<m<<endl;
    for (unsigned int i=0; i<m; i++)
    {
      //push data to left of m to left vector, 
        L.push_back(data.at(i));
    }
    for(unsigned int i=m; i<data.size(); i++)
    {
      //push data to the right of m (including m) to right vector. 
      //Right gets extra value if data.size() is odd
        R.push_back(data.at(i));
    }
    
    //recursively call merge for Left vector, stopping when size of split vectors==1
      mergesort(L);
    //recursively call merge for Right vector, stopping when size of split vectors==1
      mergesort(R);
    //merge these back together, placing value in non-decreasing order.
    data=mergeH(L, R);
  }
}

//This is a helper function that returns a vector<int>, unlike normal merge which returns void.
//This makes it easier for it to work in tandem with recursive MergeSort() function.
//It merges the values in left and right in nondecreasing order.
vector<int> Sorting::mergeH(vector<int>& left, vector<int>& right)
{
  vector<int>result;
 //first, sort by ascending order while Left and right .size()>0
  while (left.size()>0 && right.size()>0)
  {
    if (left.front()<=right.front())
    {
      result.push_back(left.front());
      //remove pushed_back value from left.
      left.erase(left.begin()+0);
    }
    else//if right.front()>left.front()
    {
      result.push_back(right.front());
      //remove pushed_back value from right.
      right.erase(right.begin()+0);
    }
    
  }

  //sort remaining values, leftover in L and R vectors.
  //one of these two must have size==0.
  if(left.size()>0)
  {
    while(left.size()>0)
    {
      result.push_back(left.front());
      left.erase(left.begin()+0);
    }
  }

  else if(right.size()>0)
  {
    while(right.size()>0)
    {
      result.push_back(right.front());
      right.erase(right.begin()+0);
    }
  }
  
  //cout<<"RESULT= ";
  //print(result);
  return result;
}

void Sorting::merge(vector<int>& left, vector<int>& right, vector<int>& result)
{
//left blank on purpose. This does not return a vector, and so keeps giving me wrong answer. 
//returning a vector seems to be key to working with recursive mergesort() function.  
//Instead, the same function that returns a vector<int> (mergeH()) is used, above.
}

//Selection Sort: Each iteration, finds the smallest element in sublist and places it at beginning,
//(Swaps this next smallest value with value in beginning index being considered)
//Then narrows the sublist down to one less value, or one value further to the right.
//I.E. finds smallest element in range (i to array.size()) then (i+1 to array.size()), etc.
//and places element at i.
void Sorting::mystery_sort(vector<int>& data)
{
  //i is index of each element where smallest element in subvector will end up.
  for (unsigned int i=0; i<data.size(); i++)
  {
      //first, set min to first index for comparisons.
      unsigned int min=i;
      //compare to all remaining elements in subarray, and update min if appropriate.
      for (unsigned int j=i+1; j<data.size(); j++)
      {
        if(data[j]<data[min])
        {
          min=j;
        }
      }

      //if new min index found, place it at index i, so that sub vector in range(0 to i) is in order.
      if(i!=min)
      {
        swap(&data.at(i), &data.at(min));
      }
  }

  return;
}