#include <stdio.h>

/*takes in the array of hares and updates it using the update equations*/

void update_hares(double map[NX][NY] double hares[NX][NY],\
double pumas[NX][NY], double timeStep, double a, double k, double r)
{
	double newHares[NX][NY];
	

	for(int y=1; y<NY-1; y++)
	{
		for(int x=1; x<NX-1; x++)
		{
			newHares[x][y] = hares[x][y] + timeStep* (r*hares[x][y] - a*hares[x][y]\
			*pumas[x][y] + k* (hares[x-1][y] + hares[x+1][y] + hares[x][y-1] +\
			hares[x][j+1]) -\
			(map[x+1][y] + map[x-1][y] + map[x][y+1] + map[x][y-1])*hares[x][y]);
		}
	}

	for(int y=1; y<NY-1; y++)
	{
		for(int x=1; x<NX-1; x++)
		{
			hares[x][y] = newHares[x][y];
		}
	}

}
