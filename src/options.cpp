#include "options.h"
#include <fstream>

// Initially
//    ./hare-and-puma -r rabbit_file -p puma_file -l land_file -c config_file
//
//    Return 0 on success or 1 on invalid input.
//
int Options::parse_input(int argc, char** argv)
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
    ("landfile", po::value<std::string>(&land_filename), "set land input file")
    ("harefile", po::value<std::string>(&hare_filename), "set hare input file")
    ("pumafile", po::value<std::string>(&puma_filename), "set puma input file")
    (
      "output,o",
      po::value<std::string>(&output_directory),
      "set output directory"
    )
    // time steps
    (
     "run_time,t",
     po::value<double>(&run_time),
     "set total running time"
    )
    (
     "time_step,d",
     po::value<double>(&time_step),
     "set time step"
    )
		(
		 "delay,D",
			po::value<int>(&delay),
			"set delay between frames in milliseconds"
		)
 		(
		 "output_frequency,T",
			po::value<int>(&output_frequency),
			"set how often the .ppm files are written"
		)
    // hare equation values
    (
     "hare_birth,r",
     po::value<double>(&hare_birth),
     "set hare birth rate"
    )
    (
     "puma_predation,a",
     po::value<double>(&puma_predation),
     "set puma predation rate"
    )
    (
     "hare_diffusion,k",
     po::value<double>(&hare_diffusion),
     "set hare diffusion rate"
    )
    // puma equation values
    (
     "puma_birth,b",
     po::value<double>(&puma_birth),
     "set puma birth rate"
    )
    (
     "puma_death,m",
     po::value<double>(&puma_death),
     "set puma death rate"
    )
    (
     "puma_diffusion,l",
     po::value<double>(&puma_diffusion),
     "set puma diffusion rate"
    )
		// gui options
		(
			"gui,g",
			po::value<bool>(&gui)->implicit_value(true),
			"sets program to gui mode"
		)
		;


  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);


  /*
   * Process arguments
   */
  // if help flag passed or no arguments passed
  if(vm.count("help") || argc == 0){
    std::cerr << desc<< std::endl;
    return 1;
  }

  if(!config_filename.empty())
  {
    std::ifstream ifs(config_filename.c_str());
    if (!ifs)
    {
        std::cerr << "can not open config file: " << config_filename << "\n";
        return 1;
    }
    else
    {
        store(parse_config_file(ifs, desc), vm);
        notify(vm);
    }
  }


  if(!vm.count("landfile"))
	{
    std::cerr << "You must specify a land input file"
              << std::endl
              << std::endl;
    std::cerr << desc<< std::endl;
    return 1;
  }
	
	if(!vm.count("gui"))
	{
		gui = false;
	}


  return 0;

}
