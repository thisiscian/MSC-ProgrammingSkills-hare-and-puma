
/*function that takes in the array of hares and updates it using the update equations*/

void update_hares(board<tile> &board, double timeStep, double a, double k, double r)
{
	int NY = board.get_height();
	int NX = board.getwidth();
	board<tile> new_board(NX,NY);


	for(int y=1; y<NY-1; y++)
	{
		for(int x=1; x<NX-1; x++)
		{
		new_board(x,y).hare = board(x,y).hare + timeStep* (r*board(x,y).hare - a*board(x,y).hare * board(x,y).puma + k* (board(x-1,y).hare + board(x+1,y).hare + board(x,y-1).hare + board(x,y+1).hare - board(x+1,y).is_land + board(x-1,y).is_land+ board(x,y+1).is_land + board(x,y-1).is_land())*board(x,y).hare);
		}
	}

	for(int y=1; y<NY-1; y++)
	for(int x=1; x<NX-1; x++)
	{	
			board(x,y).hare = new_board(x,y).hare;
	}
	

}
