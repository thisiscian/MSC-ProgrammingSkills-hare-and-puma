#include "update.h"

/*function that takes in the arrays of hares and pumas and updates them using the update equations*/

void update_animals_p(Board<Tile> &field, double timeStep, double a, double b, double k, double l, double m, double r)
{

	int NY = field.get_height();
	int NX = field.get_width();
	int landSum;
	int thread, totalThreads;
	Board<Tile> new_field(NX,NY);

#pragma omp parallel default(none) shared(field, timeStep, a, b, k, l, m, r, NX, NY, new_field, totalThreads) private(landSum, thread)
{
	if(NY > 10)
	{
		thread = omp_get_thread_num();
		totalThreads = omp_get_num_threads();
	}
	else
	{
		thread = 0;
		totalThreads = 1;
	}

	for(int y=(thread*(NY-2)/totalThreads)+1; y<((thread+1)*(NY-2)/totalThreads)+1; ++y)
	for(int x=1; x<NX-1; ++x)
	{
		if(field(x,y).is_land())
		{
		landSum = 0;
			for(int i=x-1; i<=x+1; i+=2)
			{
				if(field(i,y).is_land())
				{
					landSum++;
				}
			}
			for(int i=y-1; i<=y+1; i+=2)
			{
				if(field(x,i).is_land())
				{
					landSum++;
				}	
			}

			new_field(x,y).hare = field(x,y).hare + timeStep* \
			(r*field(x,y).hare - a*field(x,y).hare * field(x,y).puma + k* \
			(field(x-1,y).hare + field(x+1,y).hare + field(x,y-1).hare + field(x,y+1).hare - \
			(landSum)*field(x,y).hare));

			new_field(x,y).puma = field(x,y).puma + timeStep* \
      (b*field(x,y).hare*field(x,y).puma - m*field(x,y).puma + l* \
      ((field(x-1,y).puma + field(x+1,y).puma + field(x,y-1).puma + field(x,y+1).puma) - \
      (landSum)*field(x,y).puma));
		}
		else
		{
			new_field(x,y).hare = new_field(x,y).puma = 0;
		}
	}

	#pragma omp barrier

	for(int y=(thread+(NY-2)/totalThreads)+1; y<((thread+1)*(NY-2)/totalThreads)+1; ++y)
	for(int x=1; x<NX-1; x++)
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
	

}
