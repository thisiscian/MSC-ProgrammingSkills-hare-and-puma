
/*function that takes in the array of hares and updates it using the update equations*/

void update_hares(board<tile> board, double timeStep, double a, double k, double r)
{
	double newHares[NX][NY];
	

	for(int y=1; y<NY-1; y++)
	{
		for(int x=1; x<NX-1; x++)
		{
			newHares[x][y] = board(x,y).hares + timeStep* (r*board(x,y).hares - a*board(x,y).hares * board(x,y).pumas + k* (board(x-1,y).hares + board(x+1,y).hares + board(x,y-1).hares + board(x,y+1).hares - board(x+1,y).is_land() + board(x-1,y).is_land()+ board(x,y+1).is_land() + board(x,y-1).is_land())*board(x,y).hares);
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
