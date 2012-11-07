#include "board_setter.h"
#include "ncurses_lib.h"
#include "update.h"
#include "options.h"
using namespace std;

void test_very_small_all_land()
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
	if(ncursesfield.fieldtile.size() != 25)
	{
		cout << "Error: tile did not have 25 segments, actually had " << ncursesfield.fieldtile.size() << endl;
		exit(1);
	}
	endwin();
}

int main()
{
	test_very_small_all_land();
}
