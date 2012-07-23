/* 
 * File:   MazeGraph.cpp
 * Author: ben
 * 
 * Created on April 11, 2012, 1:30 PM
 */

#include "MazeGraph.h"

Edge::Edge()
{
    used = false;
}

Edge::Edge(node* o, node* d, int c)
{
    org = o;
    dest = d;
    weight = c;
    used = false;
}

bool Edge::operator <(const Edge& e) const
{
    return (weight < e.weight);
}

bool Edge::operator >(const Edge& e) const
{
    return (weight > e.weight);
}

node::node(Direction d, int r, int c, NodeType t)
{
    distance = -1;
    visited = false;
    prev = NULL;
    row = r;
    col = c;
    type = t;
    dir = d;
}

node::node(const node& n)
{
    distance = n.distance;
    visited = n.visited;
    prev = n.prev;
    adj = n.adj;
    dir = n.dir;
    row = n.row;
    col = n.col;
    type = n.type;    
}

bool node::operator <(const node& n) const
{
    if(distance >= 0 && n.distance == -1) return false;    
    return (distance < n.distance);
}



void node::addAdj(node* a, int w)
{
    Edge edge(this, a, w);
    adj.push_back(edge);
}

string node::direction() const
{
    string ret;
    
    switch(dir)
    {
        case TOP:
            ret = "UP";
            break;
        case BOTTOM:
            ret = "BOTTOM";
            break;
        case RIGHT:
            ret = "RIGHT";
            break;
        case LEFT:
            ret = "LEFT";
            break;
        case FAIL:
            ret = "FAIL";
            break;
    }
    return ret;
}

void node::printAdj() const
{
    using std::cout;
    
    cout << "At loc (" << row << ", " << col << ")\n";
    
    cout << "At direction " << direction() << std::endl;
    
    for(unsigned int i = 0; i < adj.size(); i++)
    {
        cout << "Direction: " << adj[i].dest->direction() << " at loc:" 
             <<"(" << adj[i].dest->row << ", " << adj[i].dest->col << ")\n";
    }
       
}

node::node(const node* n)
{
    distance = n->distance;
    visited = n->visited;
    prev = n->prev;
    adj = n->adj;
    dir = n->dir;
    row = n->row;
    col = n->col;
    type = n->type;
}

node::~node(){}

void node::print() const
{
    using std::endl;
    
    std::cout << "Node Information:\n" <<
            "Type: " << type << endl <<
            "Dir: " << dir << endl << 
            "Loc: (" << row << ", " << col << ")\n";
      
}

node& node::operator =(const node& n)
{
    distance = n.distance;
    visited = n.visited;
    prev = n.prev;
    adj = n.adj;
    dir = n.dir;
    row = n.row;
    col = n.col;
    type = n.type;
    return *this;
}

node& node::operator =(const node* n)
{
    distance = n->distance;
    visited = n->visited;
    prev = n->prev;
    adj = n->adj;
    dir = n->dir;
    row = n->row;
    col = n->col;
    type = n->type;
    return *this;
}