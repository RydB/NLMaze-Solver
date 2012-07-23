/* 
 * File:   MazeNode.h
 * Author: ben
 *
 * Created on April 9, 2012, 7:51 PM
 */

#ifndef MAZENODE_H
#define	MAZENODE_H

#include "MazeGraph.h"


class MazeNode 
{
public:
    void setType(char c);
    char getChar();
    
    NodeType type;
    vector<Direction> visitedFrom;
    
    vector<node> verts;
};

#endif	/* MAZENODE_H */

