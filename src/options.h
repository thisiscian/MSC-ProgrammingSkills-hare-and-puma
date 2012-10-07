#include <string>
#include <boost/program_options.hpp>
#include <iostream>

class Options
{
  public:

  std::string land_filename;
  std::string hare_filename;
  std::string puma_filename;

  double dt;
  double r;


  // Initially
  //    ./hare-and-puma -r rabbit_file -p puma_file -l land_file -c config_file
  void parse_input(int argc, char** argv);
};
