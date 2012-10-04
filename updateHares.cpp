#include <stdio.h>

/*takes in the array of hares and updates it using the update equations*/

void updateHares(double map[NX+2][NY+2] double hares[NX][NY],\
double pumas[NX][NY], double timeStep, double a, double k, double r)
{
	double newHares[NX][NY];
	

	for(int y=0; y<NY; y++)
	{
		for(int x=0; x<NX;x++)
		{
			newHares[x][y] = hares[x][y] + timeStep* (r*hares[x][y] - a*hares[x][y]\
			*pumas[x][y] + k* (hares[x-1][y] + hares[x+1][y] + hares[x][y-1] +\
			hares[x][j+1]) -\
			(map[x+1][y] + map[x-1][y] + map[x][y+1] + map[x][y-1])*hares[x][y]);
		}
	}

	for(int y=0; y<NY; y++)
	{
		for(int x=0; x<NX; x++)
		{
			hares[x][y] = newHares[x][y];
		}
	}

}
