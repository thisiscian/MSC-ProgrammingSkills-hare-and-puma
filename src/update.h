#ifndef __UPDATE_H__
#define __UPDATE_H__

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "board.h"
#include "tile.h"
/*header file containing the update routines*/

void update_animals(Board<Tile> &board, double timeStep, double a, double b, double k, double l, double m, double r);

#endif
