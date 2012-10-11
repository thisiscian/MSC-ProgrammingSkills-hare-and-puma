#include "update.h"

/*function that takes in the arrays of hares and pumas and updates them using the update equations*/

void update_animals_p(Board<Tile> &field, double timeStep, double a, double b, double k, double l, double m, double r)
{

	int NY = field.get_height();
	int NX = field.get_width();
	Board<Tile> new_field(NX,NY);


	for(int x=1; x<NX-1; x++)
	for(int y=1; y<NY-1; y++)
	{
		if(field(x,y).is_land() == 1)
		{
			new_field(x,y).hare = field(x,y).hare + timeStep* \
			(r*field(x,y).hare - a*field(x,y).hare * field(x,y).puma + k* \
			(field(x-1,y).hare + field(x+1,y).hare + field(x,y-1).hare + field(x,y+1).hare - \
			(field(x+1,y).is_land() + field(x-1,y).is_land() + field(x,y+1).is_land() + field(x,y-1).is_land())*field(x,y).hare));

			new_field(x,y).puma = field(x,y).puma + timeStep* \
      (b*field(x,y).hare*field(x,y).puma - m*field(x,y).puma + l* \
      ((field(x-1,y).puma + field(x+1,y).puma + field(x,y-1).puma + field(x,y+1).puma) - \
      (field(x-1,y).is_land() + field(x+1,y).is_land() + field(x,y-1).is_land() + field(x,y+1).is_land())*field(x,y).puma));
		}
		else
		{
			new_field(x,y).hare = new_field(x,y).puma = 0;
		}
	}

	for(int x=1; x<NX-1; x++)
	for(int y=1; y<NY-1; y++)
	{
		if(new_field(x,y).hare < 0)
		{
			field(x,y).hare = 0;
		}	
		else
		{
			field(x,y).hare = new_field(x,y).hare;
		}

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
