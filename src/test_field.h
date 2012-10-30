#ifndef __TEST_FIELD__
#define __TEST_FIELD__

#include "tile.h"
#include "board.h"
#include <cmath>
#include <algorithm>

void defineConstantField(Board<Tile>& field);
void defineLinearField(Board<Tile>& field);
void defineNonLinearField(Board<Tile>& field);

#endif
