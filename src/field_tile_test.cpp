#include "board_setter.h"
#include "ncurses_field.h"
#include "update.h"
#include "options.h"
using namespace std;

void test_small_all_land()
{
	Board<Tile> board;
  Options options;
	options.land_filename = "../test_data/tile_all_land.dat";
	options.hare_filename = "../test_data/tile_hares.dat";
	options.puma_filename = "../test_data/tile_pumas.dat";
	
  BoardSetter::set_land_from_file(board, options.land_filename);
  BoardSetter::set_hare_from_file(board, options.hare_filename);
  BoardSetter::set_puma_from_file(board, options.puma_filename);
 
	NcursesField ncursesfield(board, options, 4, 6);
	endwin();
	ncursesfield.count_animals_in_tiles();
	if(ncursesfield.fieldtile.size() != 25)
	{
		cerr << "Error [all_land]: tiles did not have correct amount of elements" << endl;
		exit(1);
	}
	if(ncursesfield.get_hare_max() != 1)
	{
		cerr << "Error [all_land]: maxmimum number of hares was incorrect" << endl;
		exit(1);
	}
	if(ncursesfield.get_puma_max() != 2)
	{
		cerr << "Error [all_land]: maxmimum number of pumas was incorrect" << endl;
		exit(1);
	}
}

void test_small_all_water()
{
	Board<Tile> board;
  Options options;
	options.land_filename = "../test_data/tile_all_water.dat";
	options.hare_filename = "../test_data/tile_hares.dat";
	options.puma_filename = "../test_data/tile_pumas.dat";
	
  BoardSetter::set_land_from_file(board, options.land_filename);
  BoardSetter::set_hare_from_file(board, options.hare_filename);
  BoardSetter::set_puma_from_file(board, options.puma_filename);
 
	NcursesField ncursesfield(board, options, 4, 6);
	endwin();
	ncursesfield.count_animals_in_tiles();
	if(ncursesfield.fieldtile.size() != 25)
	{
		cerr << "Error [all_water]: tiles did not have correct amount of elements" << endl;
		exit(1);
	}
	if(ncursesfield.get_hare_max() != 1)
	{
		cerr << "Error [all_water]: maxmimum number of hares was incorrect" << endl;
		exit(1);
	}
	if(ncursesfield.get_puma_max() != 2)
	{
		cerr << "Error [all_water]: maxmimum number of pumas was incorrect" << endl;
		exit(1);
	}
}

void test_large_all_land()
{
	Board<Tile> board;
  Options options;
	options.land_filename = "../test_data/tile_all_land_large.dat";
	options.hare_filename = "../test_data/tile_hares_large.dat";
	options.puma_filename = "../test_data/tile_pumas_large.dat";
	
  BoardSetter::set_land_from_file(board, options.land_filename);
  BoardSetter::set_hare_from_file(board, options.hare_filename);
  BoardSetter::set_puma_from_file(board, options.puma_filename);
 
	NcursesField ncursesfield(board, options, 4, 6);
	endwin();
	ncursesfield.count_animals_in_tiles();
	if(ncursesfield.fieldtile.size() < 100*100)
	{
		cerr << "Error [all_land, large]: tiles did not have correct amount of elements" << endl;
		exit(1);
	}
	if(ncursesfield.fieldtile[555].area > 1)
	{
		cerr << "Error [all_land, large]: area of tile was incorrect" << endl;
		exit(1);
	}
		if(ncursesfield.get_hare_max() > 1)
	{
		cerr << "Error [all_land, large]: maxmimum number of hares was incorrect" << endl;
		exit(1);
	}
	if(ncursesfield.get_puma_max() > 2)
	{
		cerr << "Error [all_land, large]: maxmimum number of pumas was incorrect" << endl;
		exit(1);
	}
}
int main()
{
	test_small_all_land();
	test_small_all_water();
}
