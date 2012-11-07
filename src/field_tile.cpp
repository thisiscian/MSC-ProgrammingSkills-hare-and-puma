#include "field_tile.h"

FieldTile::FieldTile(Board<Tile>* board_in, size_t i, size_t j, size_t i_max, size_t j_max)
{
	is_only_water = false;
	board = board_in;
	set_range(i,j,i_max,j_max);
	find_land_state();
	area = (i_max-i)*(j_max-j);
}

void FieldTile::set_range(size_t i, size_t j, size_t i_max, size_t j_max)
{
	x_min = i;
	y_min = j;
	x_max = i_max;
	y_max = j_max;
}

void FieldTile::find_land_state()
{
	land_count = 0;
	for(int j=y_min; j<y_max; j++)
	{
		for(int i=x_min; i<x_max; i++)
		{
			if((*board)(i,j).is_land()){land_count += 1.0;}
		}
	}
	if(land_count == 0){is_only_water = true;}
}
