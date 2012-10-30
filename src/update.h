#ifndef __UPDATE_H__
#define __UPDATE_H__

#include <iostream>
#include <stdlib.h>
#include "board.h"
#include "tile.h"
/*header file containing the update routines*/

void update_animals(Board<Tile> &field, double timeStep, double a, double b, double k, double l, double m, double r);

#endif
