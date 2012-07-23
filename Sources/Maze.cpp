#include "Maze.h"


void Maze::setMapFile(string file)
{
    filename = file;
}

void Maze::initMaze()
{
    //std::ifstream in(filename.c_str());
    using std::cin;
    string holder;
    rights = 0;
    int rowCount = 0;
    
    getline(cin, holder);
    
    while(getline(cin, holder))
    {
        if(holder == "") break;
        vector<MazeNode> temp;
        if(!rowCount) cols = holder.length();
        for(unsigned int i = 0; i < holder.length(); i++)
        {
            MazeNode t;
            
            t.setType(holder[i]);  
            if (t.type == START)
            {
                s_row = rowCount;
                s_col = i;
            }
            
            node top(TOP, rowCount, i, t.type);
            node bot(BOTTOM, rowCount, i, t.type);
            node left(LEFT, rowCount, i,  t.type);
            node right(RIGHT, rowCount, i, t.type);
            
            t.verts.push_back(top);
            t.verts.push_back(bot);
            t.verts.push_back(left);
            t.verts.push_back(right);
            
            
            temp.push_back(t);
                   
            
        }
             
        mazeMap.push_back(temp);
        temp.clear();
                
        rowCount++;
    }
    
    rows = rowCount;
}


void Maze::setType(AlgType t)
{
    type = t;
}

void Maze::printMaze()
{
    std::cout << "# right turns: " << rights << "\n";
    
    
    std::cout << rows << "x" << cols << "\n";
    for(unsigned int i = 0; i < mazeMap.size(); i++)
    {
        for(unsigned int j = 0; j < mazeMap[i].size(); j++)
        {
            std::cout << mazeMap[i][j].getChar();
        }
        std::cout << "\n";
    }
    
}

int Maze::getweight(bool right)
{
    int ret = -1;
    switch(type)
    {
        case BACKTRACKING:
            if(right) ret = 10;
            else ret = 1;
            break;
        case OPTIMAL:
            if(right) ret = 1;
            else ret = 0;
            break;
    }
    
    if (ret == -1) throw MazeError("FAIL");
    return ret;
}

void Maze::initGraph()
{
    for(unsigned int i = 0; i < mazeMap.size(); i++)
    {
        for(unsigned int j = 0; j < mazeMap[i].size(); j++)
        {
            
            if(mazeMap[i][j].type != INVALID)
            {
                //Step 1: Up Vertice.  Connect it to the up vert in the 
                // square under it
                int poop = i+1;
                if(poop < rows && mazeMap[i+1][j].type != INVALID)
                {
                    
                    inithelper(i, j, i+1, j, TOP, TOP, getweight(false)); 
                }
                
                //Step 1b: Connect up vertice to right vert in the square
                // to the left
                if((j > 0) && mazeMap[i][j-1].type != INVALID)
                {
                    inithelper(i, j, i, j-1, TOP, RIGHT, getweight(true)); 
                }
                
                //Step 2: Do the same thing for the right vert
                if((j > 0) && mazeMap[i][j-1].type != INVALID)
                {
                    inithelper(i, j, i, j-1, RIGHT, RIGHT, getweight(false)); 
                }
                
                //Step 2a
                poop = i-1;
                if(poop > 0 && mazeMap[i-1][j].type != INVALID)
                {
                    inithelper(i, j, i-1, j, RIGHT, BOTTOM, getweight(true));   
                }
                
                //Step 3: Bottom vert
                if((i > 0) && (mazeMap[i-1][j].type != INVALID))
                {
                    inithelper(i, j, i-1, j, BOTTOM, BOTTOM, getweight(false));
                }
                
                //Step 3b
                poop = j+1;
                if(poop < cols && mazeMap[i][j+1].type != INVALID)
                {
                    inithelper(i, j, i, j+1, BOTTOM, LEFT, getweight(true));
                }
                
                //Step 4: Left
                if(poop < cols && mazeMap[i][j+1].type != INVALID)
                {
                    inithelper(i, j, i, j+1, LEFT, LEFT, getweight(false));
                }
                
                //Step 4b:
                poop = i+1;
                if(poop < rows && mazeMap[i+1][j].type != INVALID)
                {
                    inithelper(i, j, i+1, j, LEFT, TOP, getweight(true));
                }
            }
        }
    }
}

void Maze::inithelper(int orow, int ocol, int drow, int dcol,
                        Direction orig, Direction dest, int w)
{
    node* t1 = &mazeMap[orow][ocol].verts[orig];
    node* t2 = &mazeMap[drow][dcol].verts[dest];
    
    Edge e(t1, t2, w);
    t1->adj.push_back(e);
}

void Maze::initQueue()
{
    
    for(unsigned int i = 0; i < mazeMap.size(); i++)
    {
        for(unsigned int j = 0; j < mazeMap[i].size(); j++)
        {
            if(mazeMap[i][j].type != INVALID && mazeMap[i][j].type != START)
            {
                for(unsigned int k = 0; k < mazeMap[i][j].verts.size(); k++)
                {
                    node temp(mazeMap[i][j].verts[k]);
                    mazeGraph.push(temp);
                }
            }
        }
    }
    
    node sT(mazeMap[s_row][s_col].verts[TOP]);
    node sL(mazeMap[s_row][s_col].verts[LEFT]);
    node sB(mazeMap[s_row][s_col].verts[BOTTOM]);
    node sR(mazeMap[s_row][s_col].verts[RIGHT]);
    
    sT.distance = 0;
    sL.distance = 0;
    sB.distance = 0;
    sR.distance = 0;
    
    
    mazeGraph.push(sT);
    mazeGraph.push(sL);
    mazeGraph.push(sB);
    mazeGraph.push(sR);
}

void Maze::dijkstras()
{
    initQueue();
    
    unsigned int size = mazeGraph.size();
    
    for(unsigned int i = 0; i < size; i++)
    {
        node small = mazeGraph.top();
        if(small.distance == -1) break;
        
        mazeGraph.pop();
        
        if(small.type == END) 
        {
         
            setWinningPath(small);
            break;
        }
        //maybe edges going out from start weight = 0?
        
        for(unsigned int j = 0; j < small.adj.size(); j++)
        {
            Edge e = small.adj[j];
            int curr = e.weight + small.distance; 
            if(e.dest->distance == -1 || curr < e.dest->distance)
            {
                if(!(e.used)){
                    e.dest->distance = curr;
                    e.dest->prev = new node(small);
                    e.used = true;
                    mazeGraph.push(e.dest);
                }
            }
            
        }
    }
    
}


void Maze::printGraphQueue()
{
    std::cout << mazeGraph.size() << "\n";
    for(unsigned int i = 0; i < 16; i++)
    {
        std::cout << "ITERATION: " << i << "\n";
        mazeGraph.top().print();
        mazeGraph.pop();
        std::cout << mazeGraph.size() << "\n";
    }
}

void Maze::setWinningPath(node& n)
{
    vector<node> path;
    win = true;
    
    
    while(n.prev)
    {
        if(n.prev->type != START)
        {
            Direction orig = n.prev->dir;
            Direction dest = n.dir;
            if(rightTurn(orig, dest)) rights++;
        }
        path.push_back(*n.prev);
        n = n.prev;
    }
    
    
    
    unsigned int size = path.size();
   
    for(unsigned int i = 0; i < size; i++)
    {
        int r = path[i].row;
        int c = path[i].col;
        
        if(r == s_row && c == s_col && i == path.size()-1) break;
        
        if(mazeMap[r][c].type != END)
        {
            mazeMap[r][c].type = PATH;
        }
                
    }
}


void Maze::BFS()
{
    initdeque();
    
    while(!nodes.empty())
    {
        node t = nodes.front();
        nodes.pop_front();
        
        if(t.type == END)
        {
            setWinningPath(t);
            break;            
        }
        
        for(unsigned int i = 0; i < t.adj.size(); i++)
        {
            if(!t.adj[i].used)
            {
                if(!t.adj[i].dest->visited)
                {
                    t.adj[i].dest->visited = true;
                    

                    t.adj[i].dest->prev = new node(t); //Memory leak.  Hate.
                    
                    t.adj[i].used = true;

                    if(t.adj[i].weight == 1) 
                    {
                        nodes.push_back(t.adj[i].dest);
                    }
                    else nodes.push_front(t.adj[i].dest);                
                }
                
            }
            
        }
    }
    

    
}

void Maze::initdeque()
{
    node tt = mazeMap[s_row][s_col].verts[TOP];
    node r = mazeMap[s_row][s_col].verts[RIGHT];
    node b = mazeMap[s_row][s_col].verts[BOTTOM];
    node l = mazeMap[s_row][s_col].verts[LEFT];
    
    tt.visited = true;
    l.visited = true;
    b.visited = true;
    r.visited = true;
    
    nodes.push_back(tt);
    nodes.push_back(r);
    nodes.push_back(b);
    nodes.push_back(l);
    
    
}

void Maze::executeAlg()
{
    win = false;
    switch(type)
    {
        case BACKTRACKING:
            dijkstras();
            break;
        case OPTIMAL:
            BFS();
            break;
    }
}
//
//void Maze::initstack()
//{
//    node* tt = new node(mazeMap[s_row][s_col].verts[TOP]);
//    node* r = new node(mazeMap[s_row][s_col].verts[RIGHT]);
//    node* b = new node(mazeMap[s_row][s_col].verts[BOTTOM]);
//    node* l = new node(mazeMap[s_row][s_col].verts[LEFT]);
//    
//    
//    d_stack.push(*tt);
//    d_stack.push(*r);
//    d_stack.push(*b);
//    d_stack.push(*l);
//    
//    tt = NULL;
//    l = NULL;
//    b = NULL;
//    r = NULL;
//    delete tt;
//    delete l;
//    delete b;
//    delete r;
//}
//
//void Maze::DFS()
//{
//    initstack();
//    
//    while(!d_stack.empty())
//    {
//        node* t = new node(d_stack.top());
//        d_stack.pop();
//        //t->visited = true;
//        
//        if(t->type == END)
//        {
//            setWinningPath(t);
//            t = NULL;
//            delete t;
//            break;
//        }
//        
//        for(unsigned int i = 0; i < t->adj.size(); i++)
//        {
//            if(!t->adj[i].used)
//            {
//                t->adj[i].used = true;
//                d_stack.push(t->adj[i].dest);
//            }
//        }
//        
//        t = NULL;
//        delete t;
//    }
//    
//}


bool Maze::rightTurn(Direction orig, Direction dest)
{
    
    bool right = false;
    
    switch(orig)
    {
        case TOP:
            if(dest == RIGHT) right = true;
            break;
        case RIGHT:
            if(dest == BOTTOM) right = true;
            break;
        case BOTTOM:
            if(dest == LEFT) right = true;
            break;
        case LEFT:
            if(dest == TOP) right = true;
            break;
    }
    
    
    return right;
}