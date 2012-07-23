/* 
 * File:   main.cpp
 * Author: ben
 *
 * Created on April 8, 2012, 12:11 PM
 */

#include "Maze.h"
using namespace std;
/*
 * 
 */
int main(int argc, char** argv) 
{
    AlgType t;
    string option = argv[1];
    
    if(option == "--backtracking" ) t = BACKTRACKING;
    else if (option == "--optimal") t = OPTIMAL;
    else { cerr << "Invalid arguments.\n"; exit(1);}
    Maze maze;
    
    maze.setType(t);
        
    try
    {
    
        maze.initMaze();
        maze.initGraph();
        maze.executeAlg();
        maze.printMaze();
       
        
    }
    catch (MazeError& e)
    {
        e.print();
        return 1;
    }
    
    return 0;
}

