/* 
 * File:   MazeGraph.h
 * Author: ben
 *
 * Created on April 11, 2012, 1:30 PM
 */

#ifndef MAZEGRAPH_H
#define	MAZEGRAPH_H

#include "MazeError.h"

class node;
enum NodeType {START, VALID, INVALID, END, PATH};
enum Direction {TOP, BOTTOM, LEFT, RIGHT, FAIL};



class Edge
{
public:
    Edge();
    Edge(node* o, node* d, int c);
    bool operator<(const Edge& e) const;
    bool operator>(const Edge& e) const;
    node* org;
    node* dest;
    int weight;
    bool used;
};

class node
{
public:
    node();
    node(Direction d, int r, int c, NodeType t);
    ~node();
    node(const node* n);
    node(const node& n);
    node& operator=(const node& n);
    node& operator=(const node* n);
    
    void addAdj(node* a, int w);
    void printAdj() const;
    string direction() const;
    
    void print() const;
    bool operator<(const node& n) const;
    
    
    int distance; //from start
    bool visited;
    node* prev;
    vector<Edge> adj;
    Direction dir;
    int row, col;
    NodeType type;
};


#endif	/* MAZEGRAPH_H */

