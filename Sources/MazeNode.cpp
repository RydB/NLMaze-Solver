#include "MazeNode.h"

void MazeNode::setType(char c)
{
    if(c == 'S') type = START;
    else if(c == '.') type = VALID;
    else if(c == 'X') type = INVALID;
    else if(c == 'G') type = END;  
    else if(c == 'P') type = PATH;
}

char MazeNode::getChar()
{
    char ret = 'E';
    
    switch(type)
    {
        case START:
            ret = 'S';
            break;
        case VALID:
            ret = '.';
            break;
        case INVALID:
            ret = 'X';
            break;
        case END:
            ret = 'G';
            break;
        case PATH:
            ret = 'p';
            break;
    }
    
    return ret;
}