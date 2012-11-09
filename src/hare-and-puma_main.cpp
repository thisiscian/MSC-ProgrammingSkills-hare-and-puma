#include "write_ppm.h"
#include "update.h"
#include "options.h"
#include "board_setter.h"
using namespace std;

int main(int argc, char* argv[])
{
	Board<Tile> board;
  Options options;
  if(options.parse_input(argc, argv) != 0)
  {
    return 1;
  }

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


  int i=0;        
  int run_time = options.run_time;
  double time_step = options.time_step;
  double simulation_time = 0.0;
  double a = options.puma_predation;
  double k = options.hare_diffusion;
  double b = options.puma_birth;
  double l = options.puma_diffusion;
  double m = options.puma_death;
  double r = options.hare_birth;
	int T = options.output_frequency;

	time_t start_time = time(NULL);
  create_output_directory(options.output_directory);

  cout << "writing ppm for time: " << 0.0 << endl;
  write_ppm(board, 0.0, options.output_directory);

	while(simulation_time < run_time)
  {
    simulation_time += time_step;
    update_animals(board, time_step, a, b, k, l, m, r);

    if(i%T == 0)
    {
			output_averages(board, simulation_time);
      
			cout << "writing ppm for time: " << simulation_time << endl;
      write_ppm(board, simulation_time, options.output_directory);
    }
    i++;    
  }
	time_t stop_time = time(NULL);
	cout << "\nRan for " << stop_time - start_time << " seconds" << endl;
}
