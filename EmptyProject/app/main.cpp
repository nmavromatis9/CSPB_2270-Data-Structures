#include <iostream>
#include "../code/Treap.h"

using namespace std;

int main(){
   
    //initialize random seed. Use the current time as a seed.
    //time(0) returns the integer number of seconds from the system clock.
    //if called in class constructor, the values are the same for diff class instances(bad)
    srand(time(0));
    

    Treap t;
    Treap g;
    //build random treaps
    t=t.buildTreap();
    cout<<"First treap is: ";
    t.print();
    cout<<"Second treap is: ";
    g=g.buildTreap();
    g.print();
    t.findIntersection(t, g);
    t.findUnion(t,g);
    t.findDifference(t,g);
    t.findDifference(g,t);


    return 0;
}