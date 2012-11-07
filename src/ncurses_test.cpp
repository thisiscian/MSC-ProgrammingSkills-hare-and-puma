#include "ncurses_lib.h"
#include "options.h"
#include "board_setter.h"
using namespace std;

int test_scaling(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	if(test_scaling(argc, argv) != 0)
	{
		cout << "Scaling failed" << endl;
		return 1;
	}
}

int test_scaling(int argc, char* argv[])
{
	Board<Tile> board;
  Options options;
  options.parse_input(argc, argv);

	options.land_filename = "../test_data/small.dat";
	options.run_time = 100.0;
	options.time_step = 1.0;
  BoardSetter::set_land_from_file(board, options.land_filename);
  if(!options.hare_filename.empty())
  {
    BoardSetter::set_hare_from_file(board, options.hare_filename);
  }
  else
  {
    BoardSetter::set_hare_from_distribution(board, RandomDistribution());
  }
  if(!options.puma_filename.empty())
  {
    BoardSetter::set_puma_from_file(board, options.puma_filename);
  }
  else
  {
    BoardSetter::set_puma_from_distribution(board, RandomDistribution());
  }

	NcursesField ncursesfield(board, options.delay, 4, 6);
	double simulation_time = 0.0;
	double a = options.puma_predation;
	double k = options.hare_diffusion;
	double b = options.puma_birth;
	double l = options.puma_diffusion;
	double m = options.puma_death;
	double r = options.hare_birth;
	time_t old_time, new_time;

	for(simulation_time = 0.0; simulation_time < options.run_time; simulation_time+=options.time_step)
	{
		update_animals(board, options.time_step, a, b, k, l, m, r);	
		ncursesfield.update(simulation_time);
	}
	endwin();	
	return 1;
}
