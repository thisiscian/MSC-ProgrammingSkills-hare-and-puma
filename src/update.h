#include <iostream>
#include <stdlib.h>
#include "board.h"
#include "tile.h"
/*header file containing the update routines*/

using namespace std;

void update_hares(Board<Tile> &field, double timeStep, double a, double k, double r);

void update_pumas(Board<Tile> &field, double timeStep, double b, double l, double m, double r);
