/* 
 * File:   MazeError.h
 * Author: ben
 *
 * Created on April 8, 2012, 12:25 PM
 */

#ifndef MAZEERROR_H
#define	MAZEERROR_H

#include "Globals.h"

const string SIZE_ERROR = "Error: invalid rows or columns.\n";


class MazeError
{
public:
    MazeError(string e);
    void print();
private:
    string error;
};

#endif	/* MAZEERROR_H */

