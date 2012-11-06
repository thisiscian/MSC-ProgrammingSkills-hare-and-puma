#include "ncurses_lib.h"
#include "update.h"
#include "options.h"
#include "board_setter.h"
using namespace std;

int main(int argc, char* argv[])
{
	Board<Tile> board;
  Options options;
  options.parse_input(argc, argv);

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

	NcursesField nfield(board, 4, 6);	
	
	int finalTime = options.run_time;
	double timeStep = options.time_step;
	double time = 0.0;
	double a = options.puma_predation;
	double k = options.hare_diffusion;
	double b = options.puma_birth;
	double l = options.puma_diffusion;
	double m = options.puma_death;
	double r = options.hare_birth;

	for(time = 0.0; time < finalTime; time+=timeStep)
	{
		update_animals(board, timeStep, a, b, k, l, m, r);	
		nfield.update(time);
		getch();
	}
	endwin();
}
