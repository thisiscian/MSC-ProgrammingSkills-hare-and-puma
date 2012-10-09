#include "update.h"

/*function that takes in the array of pumas and updates it using the update equations*/

void update_pumas(Board<Tile> &field, double timeStep, double b, double l, double m, double r)
{

	int NY = field.get_height();
	int NX = field.get_width();
	Board<Tile> new_field(NX,NY);


	for(int y=1; y<NY-1; y++)
	for(int x=1; x<NX-1; x++)
	{
		new_field(x,y).puma = field(x,y).puma + timeStep* \
		(b*field(x,y).hare*field(x,y).puma - m*field(x,y).puma + l* \
		((field(x-1,y).puma + field(x+1,y).puma + field(x,y-1).puma + field(x,y+1).puma) - \
		(field(x-1,y).is_land() + field(x+1,y).is_land() + field(x,y-1).is_land() + field(x,y+1).is_land())*field(x,y).puma));
	}

	for(int y=1; y<NY-1; y++)
	for(int x=1; x<NX-1; x++)
	{
		if(new_field(x,y).puma < 0)
		{
			field(x,y).puma = 0;
		}	
		else
		{
		field(x,y).puma = new_field(x,y).puma;
		}
	}
	
}
