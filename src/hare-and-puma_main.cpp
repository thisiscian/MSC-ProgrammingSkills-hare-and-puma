#include "test_field.h"
#include "output.h"
#include "update.h"
#include "options.h"
using namespace std;

int main()
{
	Board<Tile> field(2002,2002);
	defineGaussian(field);
	Options options;
	options.run_time = 10;
	
	int i = 0;
	int finalTime = options.run_time;
	double timeStep = options.time_step;
	double time = 0.0;
	double a = options.puma_predation;
	double k = options.hare_diffusion;
	double b = options.puma_birth;
	double l = options.puma_diffusion;
	double m = options.puma_death;
	double r = options.hare_birth;

	create_output_folder("output");
	while(time <= finalTime)
	{
		update_animals(field, timeStep, a, b, k, l, m, r);
		if(i%1 == 0)
		{
			cout << "writing ppm for time: " << time << endl;
			write_ppm(field, time);
		}
		time += timeStep;
		i++;	
	}
}
