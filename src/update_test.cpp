#include <iostream>
#include "tile.h"
#include "board.h"
#include "update.h"

/*a piece of code to test the update routines*/

int main()
{
	double timeStep, a, k, r;
	board<tile> b(10, 10);

	for(size_t i=0; i<10; ++i)
	for(size_t j=0; j<10; ++j)
	{
		b(i,j).hare = 1;
		b(i,j).puma = 0;	
	}

	update_hares(b, timeStep, a, k, r);

}
