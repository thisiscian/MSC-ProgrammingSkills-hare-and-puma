#include "options.h"

// Initially
//    ./hare-and-puma -r rabbit_file -p puma_file -l land_file -c config_file
void Options::parse_input(int argc, char** argv)
{
namespace po = boost::program_options;

  po::options_description desc("Allowed Options");
  desc.add_options()
    ("help", "produce help message")
    ("land,l", po::value<std::string>(), "set land input file")
    ("hare,h", po::value<std::string>(), "set hare input file")
    ("puma,p", po::value<std::string>(), "set puma input file");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if(vm.count("help")){
    std::cout << desc<< std::endl;
    exit(1);
  }

  if(vm.count("land")){
    land_filename = vm["land"].as<std::string>();
  }
  else{
    std::cerr << "You must specify a land input file" << std::endl;
    std::cout << desc<< std::endl;
    exit(1);
  }

  if(vm.count("hare")){
    hare_filename = vm["hare"].as<std::string>();
  }
  else{
    std::cerr << "You must specify a hare input file" << std::endl;
    std::cout << desc<< std::endl;
    exit(1);
  }

  if(vm.count("puma")){
    puma_filename = vm["puma"].as<std::string>();
  }
  else{
    std::cerr << "You must specify a puma input file" << std::endl;
    std::cout << desc<< std::endl;
    exit(1);
  }

}
