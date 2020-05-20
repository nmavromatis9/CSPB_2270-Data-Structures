#include "Vector10.h"

Vector10::Vector10(){
    last_open=0;
    for (int i=0; i<10; i++)
    {
        arr[i]=0;
    }
}

Vector10::~Vector10(){
    // You don't need to add anything here
}

// Implement this function first, since all tests use it.
int Vector10::ValueAt(int index){
    if (index<0 || index>9)
    {
        return -1;
    }

    else
    {
        return arr[index];
    }
}

// Implement this function second, since most tests use it.
bool Vector10::PushBack(int value){
    if (last_open>9)//if arr full
    {
        return false;
    }

    else
    {
        arr[last_open]=value;
        last_open++;
        return true;
    }
    
}

int Vector10::CountEmpty(){
    if (last_open>10)
    {
        return 0;
    }

    else
    {
        return (10-last_open);
    }
}

bool Vector10::Search(int value){
    for (int i=0; i<10; i++)
    {
        if (arr[i]==value)
        {
            return true;
        }
    }
    return false;
}

bool Vector10::Remove(int index){
    if(index<0 || index >9)
    {
        return false;
    }
    else{
        for (int i=index; i<last_open; i++)
        {
            arr[i]=arr[i+1];
        }
        last_open--;
        return true;
    }

}