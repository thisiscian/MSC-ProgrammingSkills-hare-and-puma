#include "options.h"
#include <fstream>

// Initially
//    ./hare-and-puma -r rabbit_file -p puma_file -l land_file -c config_file
void Options::parse_input(int argc, char** argv)
{
  namespace po = boost::program_options;


  /*
   * Name and describe arguments
   */

  po::options_description desc("Allowed Options");
  desc.add_options()
    ("help,h", "produce help message")
    ("config,c",
     po::value<std::string>(&config_filename),
     "name a configuration file"
    )
    // input files
    ("land", po::value<std::string>(&land_filename), "set land input file")
    ("hare", po::value<std::string>(&hare_filename), "set hare input file")
    ("puma", po::value<std::string>(&puma_filename), "set puma input file")
    // time steps
    (
     "run_time,t",
     po::value<double>(&run_time)->default_value(run_time),
     "set total running time"
    )
    (
     "time_step,dt",
     po::value<double>(&time_step)->default_value(time_step),
     "set time step"
    )
    // hare equation values
    (
     "hare_birth,r",
     po::value<double>(&hare_birth)->default_value(hare_birth),
     "set hare birth rate"
    )
    (
     "puma_predation,a",
     po::value<double>(&puma_predation)->default_value(puma_predation),
     "set puma predation rate"
    )
    (
     "hare_diffusion,k",
     po::value<double>(&hare_diffusion)->default_value(hare_diffusion),
     "set hare diffusion rate"
    )
    // puma equation values
    (
     "puma_birth,b",
     po::value<double>(&puma_birth)->default_value(puma_birth),
     "set puma birth rate"
    )
    (
     "puma_death,m",
     po::value<double>(&puma_death)->default_value(puma_death),
     "set puma death rate"
    )
    (
     "puma_diffusion,l",
     po::value<double>(&puma_diffusion)->default_value(puma_diffusion),
     "set puma diffusion rate"
    );

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  std::ifstream ifs(config_filename.c_str());
  if (!ifs)
  {
      std::cout << "can not open config file: " << config_filename << "\n";
      exit(1);
  }
  else
  {
      store(parse_config_file(ifs, desc), vm);
      notify(vm);
  }


  /*
   * Process arguments
   */

  if(vm.count("help")){
    std::cout << desc<< std::endl;
    exit(1);
  }

  if(!vm.count("land")){
    std::cerr << "You must specify a land input file"
              << std::endl
              << std::endl;
    std::cerr << desc<< std::endl;
    exit(1);
  }

}
