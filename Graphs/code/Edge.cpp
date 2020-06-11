#include "Edge.h"

Edge::Edge(shared_ptr<Node> n1, shared_ptr<Node> n2) {
  // DONE FOR YOU
  a = n1;
  b = n2;
}

Edge::~Edge() {
  // "DONE" FOR YOU
}


shared_ptr<Node> Edge::getStart() {
  // DONE FOR YOU
  return a;
}

shared_ptr<Node> Edge::getEnd() {
  // DONE FOR YOU
  return b;
}

int Edge::getType() {
  // DONE FOR YOU
  return type;
}

//#define UNDISCOVERED_EDGE 9
//#define TREE_EDGE 10
//#define BACK_EDGE 11
//#define FORWARD_EDGE 12
//#define CROSS_EDGE 13
void Edge::setType(int edge_type) 
{
  type=edge_type;
}

// overloading operator << lets you put an Edge object into an output
// stream.
ostream &operator << (std::ostream& out, Edge edge) {
  // DONE FOR YOU
  out << *edge.a << " -- " << *edge.b;
  return out;
}