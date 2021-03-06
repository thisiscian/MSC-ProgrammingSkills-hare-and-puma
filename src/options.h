#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include <string>
#include <boost/program_options.hpp>
#include <iostream>

class Options
{
  public:
  // set default values for options
  Options():
    run_time(500),
    time_step(0.4),
		output_frequency(1),
    hare_birth(0.08),
    puma_predation(0.04),
    hare_diffusion(0.02),
    puma_birth(0.02),
    puma_death(0.02),
    puma_diffusion(0.06),
		delay(1000),
    output_directory("output"),
		gui(false)
  {
  }

  std::string config_filename;

  std::string land_filename;
  std::string hare_filename;
  std::string puma_filename;

  std::string output_directory;


  // time values
  double run_time;       // t
  double time_step;      // dt
	int delay;						 // delay between frames in ms
	int output_frequency;	 // how often the .ppm files are written

  // hare equation values
  double hare_birth;     // r
  double puma_predation; // a
  double hare_diffusion; // k

  // puma equation values
  double puma_birth;     // b
  double puma_death;     // m
  double puma_diffusion; // l

	bool gui;

  int parse_input(int argc, char** argv);
};

#endif
