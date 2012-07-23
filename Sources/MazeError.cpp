#include "MazeError.h"

MazeError::MazeError(string e)
{
    error = e;
}

void MazeError::print()
{
    std::cerr << error;
}
