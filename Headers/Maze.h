/* 
 * File:   Maze.h
 * Author: ben
 *
 * Created on April 8, 2012, 12:22 PM
 */

#ifndef MAZE_H
#define	MAZE_H

#include "MazeNode.h"

enum AlgType {BACKTRACKING, OPTIMAL};

class Maze
{
public:
    
    void initMaze();
    void initGraph();
    void printMaze();
    void printGraphQueue();
    void dijkstras();
    void setWinningPath(node& n);
    void initQueue();
    void initdeque();
    void BFS();
    
    bool rightTurn(Direction orig, Direction dest);
    
    
    void initstack();
    void DFS();
    
    int getweight(bool right);
    /* Setters */
    void setMapFile(string file);
    void setType(AlgType t);
    
    void executeAlg();
    
    void inithelper(int orow, int ocol, int drow, int dcol,
    Direction orig, Direction dest, int w);
    
    vector< vector <MazeNode> > mazeMap;
    std::priority_queue<node> mazeGraph;
    std::deque<node> nodes;
    std::stack<node> d_stack;
    
    bool win;
    int rights;
    int s_row, s_col;
    int rows, cols; 
    string filename;
    AlgType type;
};

#endif	/* MAZE_H */

