#include "Graph.h"

#include <iostream>
#include <sstream>

using namespace std;

// fwd declarations
string make_dot(Graph* g);
string what(int& v);

Graph::Graph() {
  // DONE FOR YOU
  directed = false; // graphs are undirected by default
}

Graph::~Graph() {
  // "DONE" FOR YOU
  // no implementation needed
}

vector<shared_ptr<Node>> Graph::getNodes() {
  // DONE FOR YOU
  return nodes;
}

vector<shared_ptr<Edge>> Graph::getEdges() {
  // DONE FOR YOU
  return edges;
}

int Graph::getClock() {
  // DONE FOR YOU
  return clock;
}

void Graph::addNode(shared_ptr<Node> n) {
  // DONE FOR YOU
  nodes.push_back(n);
}

void Graph::addEdge(shared_ptr<Edge> e) {
  // DONE FOR YOU
  edges.push_back(e);
}
 
void Graph::removeNode(shared_ptr<Node> n) {
  // DONE FOR YOU
  for (vector<shared_ptr<Node>>::iterator it = nodes.begin(); it != nodes.end(); it++) {
    if (n == *it) {
      nodes.erase(it);
      break;
    }
  }
}
 
void Graph::removeEdge(shared_ptr<Edge> e) {
  // DONE FOR YOU
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin();
       it != edges.end(); 
       it++) {
    if (e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  // DONE FOR YOU
  directed = val;
}

bool Graph::isDirected() {
  // DONE FOR YOU
  return directed;
}

set<shared_ptr<Edge>> Graph::getAdjacentEdges(shared_ptr<Node> n) {
  // DONE FOR YOU
  set<shared_ptr<Edge>> ret;
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin(); it != edges.end(); it++) {
    shared_ptr<Edge> edge = *it;
    if (edge->getStart() == n) {
      ret.insert(edge);
    }
    if (!directed && (edge->getEnd() == n)) {
      ret.insert(edge);
    }
  }
  return ret;
}

// clear resets all nodes to have WHITE color, with -1 discovery and
  // finish times and rank. Resets all edges to type
  // UNDISCOVERED_EDGE. It resets the graph clock to 0.
void Graph::clear() 
{
  //use it iterator pointer to make iterating through edges and nodes easier.
  for (vector<shared_ptr<Node>>::iterator it = nodes.begin(); it != nodes.end(); it++) 
  {
    //store as a shared_ptr so that correct type can be used on member function.
    shared_ptr<Node> node = *it;
    //call node::clear() to save space.
    node->clear();
  }
  for (vector<shared_ptr<Edge>>::iterator it = edges.begin(); it != edges.end(); it++) 
  {
    //store as a shared_ptr so that correct type can be used on member function.
    shared_ptr<Edge> edge = *it;
    edge->setType(9);//undiscovered edge.
  }
  //this is unnecessary, but it doesn't hurt to use pointer to claling object.
  this->clock=0;
}

void Graph::tick(string message) {
  // DONE FOR YOU
  //
  // optional debugging function, disabled with if(false) to prevent
  // unused var warning. Change this however you want.
  //
  // recommended use: call it just after incrementing the clock.
  if (false) {
    cout << "// " << message << endl << make_dot(this) << endl;
  }
}

/*
dfs(node): 
  mark node gray
  visit node
  E = edges related to node
  for all edges e in E:
    a = end of e that isn't node
    if a is white:
      dfs(a)
  mark node black
  */
//dfs works on stack, or recursion which has an inherent stack.
void Graph::dfs(shared_ptr<Node> start) 
{
  //set visited node to grey/2 (visited), 
  //set discovery time by current clock value.
  //Note: real start node gets time of zero, this is why clock is iterated after call.
  start->setColor(2,this->clock); 
  //iterate clock to simulate a time action upon node. Used by next call.
  this->clock+=1;
  //return and store all adjacent edges of node being visited
  set<shared_ptr<Edge>> adj=getAdjacentEdges(start);
  //iterate over each edge in adjacency set, store in edge ptr variable e.
  //could also do auto e:adj, but this way makes type explicit.
  for (shared_ptr<Edge> e: adj)
  {
    //In current adj edge, store node opposite of currently explored node
    //as otherEnd.
    shared_ptr<Node> otherEnd(NULL);
    if(e->getStart()==start)
    {
      otherEnd=e->getEnd();
    }
    else if(e->getEnd()==start)
    {
      otherEnd=e->getStart();
    }
    
    //if end node is white(Unvisited), recursively call dfs on it.
    if(otherEnd->getColor()==1)
    {
      //set the start of the edge to be the predecessor to the end of the edge.
      e->getEnd()->setPredecessor(e->getStart());
      //TREE: A tree edge start to end means that end node is white when visited
      //aka end node discovered by start node.
      e->setType(10); //10==treeEdge.
      //recurisely call dfs on this otherEnd node.
      dfs(otherEnd);
    }
    //if end node is grey:
    else if(otherEnd->getColor()==2)
    {
      //Back edges are when the end node is gray.
      e->setType(11);//back edge==11
    }
    //two cases for black end nodes.
    
    //FORWARD: A forward edge means that end node is black when visited, 
    //and start node is ancestor of end node.

    //CROSS: A cross edge means that end node is black when visited, 
    // and start node is NOT ancestor of end node.
  
    else if(otherEnd->getColor()==3)//black
    {
      if(e->getEnd()->isAncestor(e->getStart()))
      {
        e->setType(12);//forward edge
      }
      else//if end node is NOT the ancestor of start node.
      //this is a cross edge.
      {
        e->setType(13);//cross edge.
      }
    }
  }
  
  
  //after all adjacent nodes of node are recursively visited, mark node as black.
  //set current finish time also.
  start->setColor(3,this->clock);
  //iterate clock. I tried putting this before setColor() call, 
  //and completion_time was one too high. You actually update clock for NEXT use/call.
  this->clock+=1; 
  
}

void Graph::bfs(shared_ptr<Node> start) 
{
  
  //create a queue to keep track of Nodes
  queue <shared_ptr<Node>>q;
  //create a Node pointer to store each node from queue
  shared_ptr<Node>curr(NULL);
  //create vars to store color and rank of each accessed parent node,
  //so that each rank of next visited node can be properly updated from rank of previous node.
  int color=0;
  int disco_time=0;
  int finish_time=0;
  int bfs_rank=0;
  //set start node to visited, and time to 0
  start->setColor(2, this->clock);
  //set start rank to 0
  start->setRank(bfs_rank);
  q.push(start);
  //iterate clock so it is correct for other visited Nodes.
  this->clock++;

  //only grey nodes are pushed onto queue.
  while(!q.empty())
  {
    //store current node in queue to explore it's adjacent nodes.
    curr=q.front();
    q.pop();

    //store information of current (parent) node
    curr->getDiscoveryInformation(color, disco_time, finish_time, bfs_rank);
    //explore and store all adjacent nodes to current node.
    set<shared_ptr<Edge>> adj=getAdjacentEdges(curr);

    for (shared_ptr<Edge> e: adj)
    {
      //store other end of edges adjacent to curr Node
      shared_ptr<Node> otherEnd(NULL);
      if(e->getStart()==curr)
      {
      otherEnd=e->getEnd();
      }
      else if(e->getEnd()==curr)
      {
      otherEnd=e->getStart();
      }
      //store color of this end node.
      int endColor=otherEnd->getColor();
      //if other end is unexplored, iterate rank from parent rank, 
      //color it grey, push onto queue, iterate clock
      if(endColor==1)
      {
        otherEnd->setColor(2, this->clock);
        otherEnd->setRank(bfs_rank+1);
        this->clock++;
        q.push(otherEnd);
      }
    }
    //when all adjacent nodes of curr node are discovered(visited), 
    //curr node is now fully explored.
    //So color node black, update clock.
    curr->setColor(3, this->clock);
    this->clock++; //iterate clock so it is ready for next node.
  }

}

void Graph::bfs(shared_ptr<Node> start, shared_ptr<Node> finish) 
{
  //create a queue to keep track of Nodes
  queue <shared_ptr<Node>>q;
  //create a Node pointer to store each node from queue
  shared_ptr<Node>curr(NULL);
  //create vars to store color and rank of each accessed parent node,
  //so that each rank of next visited node can be properly updated from rank of previous node.
  int color=0;
  int disco_time=0;
  int finish_time=0;
  int bfs_rank=0;
  //bool for found finish node.
  bool found=false;
  //set start node to visited, and time to 0
  start->setColor(2, this->clock);
  //set start rank to 0
  start->setRank(bfs_rank);
  q.push(start);
  //iterate clock so it is correct for other visited Nodes.
  this->clock++;

  //only grey nodes are pushed onto queue.
  //End while loop when finish node is visited.
  while(!q.empty() && !found)
  {
    //store current node in queue to explore it's adjacent nodes.
    curr=q.front();
    q.pop();

    //store information of current (parent) node
    curr->getDiscoveryInformation(color, disco_time, finish_time, bfs_rank);
    //explore and store all adjacent nodes to current node.
    set<shared_ptr<Edge>> adj=getAdjacentEdges(curr);

    for (shared_ptr<Edge> e: adj)
    {
      //store other end of edges adjacent to curr Node
      shared_ptr<Node> otherEnd(NULL);
      if(e->getStart()==curr)
      {
      otherEnd=e->getEnd();
      }
      else if(e->getEnd()==curr)
      {
      otherEnd=e->getStart();
      }
      //store color of this end node.
      int endColor=otherEnd->getColor();
      //if other end is unexplored, (and finish node not discovered) 
      //iterate rank from parent rank, 
      //color other end grey, push onto queue, iterate clock
      if(endColor==1 && !found)
      {
        otherEnd->setColor(2, this->clock);
        otherEnd->setRank(bfs_rank+1);
        this->clock++;
        q.push(otherEnd);
      }
      //if finish node is visited, then end exploration.
      //color finish node black, set finish_time.
      if(otherEnd->getData()==finish->getData())
      {
        found=true;
        otherEnd->setColor(3, this->clock);
        this->clock++;
      }
    }
    //when all adjacent nodes of curr node are discovered(visited), 
    //curr node is now fully explored.
    //So color node black, update clock.
    curr->setColor(3, this->clock);
    this->clock++; //iterate clock so it is ready for next node.
  }
}


// overloading operator << lets you put a Graph object into an output
// stream.
ostream &operator << (ostream& out, Graph graph) {
  // DONE FOR YOU
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (vector<shared_ptr<Node>>::iterator it = graph.nodes.begin(); it != graph.nodes.end(); it++) {
    shared_ptr<Node> n = *it;
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (vector<shared_ptr<Edge>>::iterator it = graph.edges.begin(); it != graph.edges.end(); it++) {
    shared_ptr<Edge> e = *it;
    out << *e << ", ";
  }
  out << "]";
  return out;
}

// what is a helper function that turns a constant (e.g. WHITE or
// FORWARD_EDGE) into a string for debugging goodness. 
string what(int& v) {
  // DONE FOR YOU
  string ret = "Unknown";
  if (v == WHITE) {
    ret = "white";
  } else if (v == GRAY) {
    ret = "gray";
  } else if (v == BLACK) {
    ret = "black";
  } else if (v == UNDISCOVERED_EDGE) {
    ret = "undiscovered";
  } else if (v == TREE_EDGE) {
    ret = "tree";
  } else if (v == BACK_EDGE) {
    ret = "back";
  } else if (v == FORWARD_EDGE) {
    ret = "forward";
  } else if (v == CROSS_EDGE) {
    ret = "cross";
  }
  return ret;
}

// make_dot generates a dotfile string for viewing your graph. Have
// tick() print out the results of this function, and then use
// http://www.webgraphviz.com/ (or get a copy of GraphViz) to view the
// result. If you're stuck, this can help you get un-stuck.
string make_dot(Graph* g) {
  // DONE FOR YOU
  stringstream ss;
  vector<shared_ptr<Node>> nodes = g->getNodes();
  vector<shared_ptr<Edge>> edges = g->getEdges();
  string gt = "graph";
  string con = "--";
  if (g->isDirected()) {
    con = "->";
    gt = "digraph";
  }
  ss << gt << " homework {" << endl;
  int c, dt, ft, r;
  string textColor = "black";
  for (auto it=nodes.begin(); it != nodes.end(); ++it) {
    shared_ptr<Node> n = *it;
    n->getDiscoveryInformation(c, dt, ft, r);
    if (c == BLACK) {
      textColor = "white";
    } else {
      textColor = "black";
    }
    ss << "  " << n->getData() << " [ style=\"filled\" fontcolor=\"" << textColor << "\" fillcolor=\"" << what(c) << "\"" << " ]" << endl;
  }
  
  string edgeColor = "black";
  for (auto it=edges.begin(); it != edges.end(); ++it) {
    shared_ptr<Edge> e = *it;
    if (e->getType() == TREE_EDGE) {
      edgeColor = "black";
    } else if (e->getType() == FORWARD_EDGE) {
      edgeColor = "purple";
    } else if (e->getType() == BACK_EDGE) {
      edgeColor = "blue";
    } else if (e->getType() == CROSS_EDGE) {
      edgeColor = "green";
    } else {
      edgeColor = "gray";
    }
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData() << " [color=\"" << edgeColor << "\"]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}