#include "options.h"

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
    // input files
    ("land", po::value<std::string>(), "set land input file")
    ("hare", po::value<std::string>(), "set hare input file")
    ("puma", po::value<std::string>(), "set puma input file")
    // time steps
    (
     "run_time,t",
     po::value<double>()->default_value(run_time),
     "set total running time"
    )
    (
     "time_step,dt",
     po::value<double>()->default_value(time_step),
     "set time step"
    )
    // hare equation values
    (
     "hare_birth,r",
     po::value<double>()->default_value(hare_birth),
     "set hare birth rate"
    )
    (
     "puma_predation,a",
     po::value<double>()->default_value(puma_predation),
     "set puma predation rate"
    )
    (
     "hare_diffusion,k",
     po::value<double>()->default_value(hare_diffusion),
     "set hare diffusion rate"
    )
    // puma equation values
    (
     "puma_birth,b",
     po::value<double>()->default_value(puma_birth),
     "set puma birth rate"
    )
    (
     "puma_death,m",
     po::value<double>()->default_value(puma_death),
     "set puma death rate"
    )
    (
     "puma_diffusion,l",
     po::value<double>()->default_value(puma_diffusion),
     "set puma diffusion rate"
    );

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);


  /*
   * Process arguments
   */

  if(vm.count("help")){
    std::cout << desc<< std::endl;
    exit(1);
  }

  if(vm.count("land")){
    land_filename = vm["land"].as<std::string>();
  }
  else{
    std::cerr << "You must specify a land input file"
              << std::endl
              << std::endl;
    std::cerr << desc<< std::endl;
    exit(1);
  }

  if(vm.count("hare")){
    hare_filename = vm["hare"].as<std::string>();
  }
  else{
    std::cerr << "No hare input file specified. Setting to random." << std::endl;
  }

  if(vm.count("puma")){
    puma_filename = vm["puma"].as<std::string>();
  }
  else{
    std::cerr << "No puma input file specified. Setting to random." << std::endl;
  }

  if(vm.count("run_time")){
    run_time = vm["run_time"].as<double>();
  }

  if(vm.count("time_step")){
    time_step = vm["time_step"].as<double>();
  }

  if(vm.count("hare_birth")){
    hare_birth = vm["hare_birth"].as<double>();
  }

  if(vm.count("puma_predation")){
    puma_predation = vm["puma_predation"].as<double>();
  }

  if(vm.count("puma_birth")){
    puma_birth = vm["puma_birth"].as<double>();
  }

  if(vm.count("puma_diffusion")){
    puma_diffusion = vm["puma_diffusion"].as<double>();
  }

  if(vm.count("puma_death")){
    puma_death = vm["puma_death"].as<double>();
  }


}
