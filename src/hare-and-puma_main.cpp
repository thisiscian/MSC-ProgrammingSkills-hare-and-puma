#include "output.h"
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
  int finalTime = options.run_time;
  double timeStep = options.time_step;
  double time = 0.0;
  double a = options.puma_predation;
  double k = options.hare_diffusion;
  double b = options.puma_birth;
  double l = options.puma_diffusion;
  double m = options.puma_death;
  double r = options.hare_birth;

  create_output_directory(options.output_directory);
  while(time <= finalTime)
  {
          update_animals(board, timeStep, a, b, k, l, m, r);
          if(i%1 == 0)
          {
                  cout << "writing ppm for time: " << time << endl;
                  write_ppm(board, time);
          }
          time += timeStep;
          i++;    
  }
}
