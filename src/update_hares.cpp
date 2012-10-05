#include "update.h"

/*function that takes in the array of hares and updates it using the update equations*/

void update_hares(board<tile> &field, double timeStep, double a, double k, double r)
{

	int NY = field.get_height();
	int NX = field.get_width();
	board<tile> new_field(NX,NY);


	for(int y=1; y<NY-1; y++)
	{
		for(int x=1; x<NX-1; x++)
		{
		new_field(x,y).hare = field(x,y).hare + timeStep* (r*field(x,y).hare - a*field(x,y).hare * field(x,y).puma + k* (field(x-1,y).hare + field(x+1,y).hare + field(x,y-1).hare + field(x,y+1).hare - field(x+1,y).is_land() + field(x-1,y).is_land() + field(x,y+1).is_land() + field(x,y-1).is_land())*field(x,y).hare);
		}
	}

	for(int y=1; y<NY-1; y++)
	for(int x=1; x<NX-1; x++)
	{	
			field(x,y).hare = new_field(x,y).hare;
	}
	

}
