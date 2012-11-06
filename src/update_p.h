#ifndef __UPDATE_P_H__
#define __UPDATE_P_H__

#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include "board.h"
#include "tile.h"
/*header file containing the update routines*/

void update_animals(Board<Tile> &board, double timeStep, double a, double b, double k, double l, double m, double r);

void update_animals_p(Board<Tile> &board, double timeStep, double a, double b, double k, double l, double m, double r);

#endif
