#include "ncurses_lib.h"
#include "update.h"
#include "options.h"
using namespace std;

int main()
{
	Board<Tile> field(6,6);
	defineConstantField(field);
	NcursesField nfield(field, 4, 6);	
	Options options;
	options.run_time = 10000;
	
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
		update_animals(field, timeStep, a, b, k, l, m, r);	
		nfield.update(time);
		getch();
	}
	endwin();
}
