#ifndef __FIELD_TILE_H__
#define __FIELD_TILE_H__

#include "tile.h"
#include "board.h"

class FieldTile
{
	public:
	Board<Tile>* board; // values from board are pointed to

	int land_count; // amount of land in tile
	bool is_only_water; // true if tile is only water
	int area;

	size_t x_min, x_max;	// range of values that
	size_t y_min, y_max;  // the tile owns

	double hare;	// number of hares
	double puma;	// and pumas in tile

	FieldTile(Board<Tile>* board_in, size_t x, size_t y, size_t x_max, size_t y_max);

	void find_land_state(); // finds the amount of land in the tile

	void set_range(size_t x, size_t y, size_t x_max, size_t y_max);
	private:
};

#endif
