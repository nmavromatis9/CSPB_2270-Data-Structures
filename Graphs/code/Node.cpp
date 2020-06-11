#include "Node.h"

Node::Node(string s) {
  // DONE FOR YOU
  data = s;
}

Node::~Node() {
  // "DONE" FOR YOU
  //
  // This is equivalent to the default destructor the compiler will
  // generate for you. As a rule of thumb, you only need to `delete`
  // member variables that were created with `new` inside this
  // class. So, you don't need to do anything here. It could have been
  // left out of the header/impl file entirely.
}

string Node::getData() {
  // DONE FOR YOU
  return data;
}

void Node::setRank(int r) {
  // DONE FOR YOU
  rank = r;
}

void Node::clear() 
{
  color=1; //white
  discovery_time=-1;
  completion_time=-1;
  rank=-1;
  predecessor=NULL;

}

  // setColor sets the 'color' of a node. Be sure to set the
  // appropriate time variable depending on what the new color is: set
  // discovery_time if the node is now GRAY, and completion_time if
  // the node is now BLACK. If it is now WHITE, this should be
  // equivalent to calling clear().
void Node::setColor(int search_color, int time) 
{
  color=search_color;
  if(color==1)//white
  {
    clear();//resets all member variables to -1.
    return;
  }
  else if(color==2)//gray
  {
    discovery_time=time;
    return;
  }
  else if(color==3)//black
  {
    completion_time=time;
    return;
  }
  else
  {
    cout<<"Invalid color."<<endl;
    return;
  }
}

  // getDiscoveryInformation gets (copies) the color, discovery time, and
  // finish time to 'color', 'disco_time', 'finish_time', and
  // 'bfs_rank' respectively.
void Node::getDiscoveryInformation(int& thecolor, int& disco_time, 
				   int& finish_time, int& bfs_rank) 
{
  thecolor=color;
  disco_time=discovery_time;
  finish_time=completion_time;
  bfs_rank=rank;
  return;
}

bool Node::isAncestor(shared_ptr<Node> other) 
{
   //if predecessor of calling object is the same as other,
   //This means calling object is the ancestor of other.
  if (other == this->predecessor)
  {
	return true;
	} 
  //if calling object has no predecessor, must be false.
  else if (this->predecessor == NULL)
  {
	return false;
  }
  
	
  //recursive call.
	return this->predecessor->isAncestor(other);
}

//sets other as calling object's predecessor.
void Node::setPredecessor(shared_ptr<Node> other) 
{
  this->predecessor=other;
}

// overloading operator << lets you put a Node object into an output
// stream.
ostream &operator << (std::ostream& out, Node node) {
  // DONE FOR YOU
  out << node.data;
  return out;
}

//My function
int Node::getColor()
{
  return this->color;
}