#include <iostream>
#include "tile.h"
#include "board.h"
#include "update.h"

/*a piece of code to test the update routines*/

int main()
{
	double timeStep, a, b, k, l, m, r, newHareSum, oldHareSum, newPumaSum, oldPumaSum;
	board<tile> field(10, 10), old_field(10,10);

	a = b = k = l = m = r = timeStep = 1.0;

	for(size_t i=0; i<10; ++i)
	for(size_t j=0; j<10; ++j)
	{
		field(i,j).hare = old_field(i,j).hare = 1;
		field(i,j).puma = old_field(i,j).puma = 0;
	}

	

	update_hares(field, timeStep, a, k, r);
	update_pumas(field, timeStep, b, l, m, r);	

	newHareSum = oldHareSum = newPumaSum = oldPumaSum = 0;	

	for(size_t i=0; i<10; ++i)
	for(size_t j=0; j<10; ++j)
	{
		newHareSum += field(i,j).hare;
		oldHareSum += old_field(i,j).hare;
		newPumaSum += field(i,j).puma;
		oldPumaSum += old_field(i,j).puma;
	}
	
	if(newHareSum == oldHareSum)
	{
		cout << "error: hare sums not changing" << endl;
		return 1;
	}
	else if(newPumaSum != 0)
	{
		cout << "error: pumas have spawned" << endl;
		return 1;
	}
	

	return 0;
}
