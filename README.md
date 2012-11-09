hares and pumas
=======

Useage
------

    ./configure && make && make install
    hare-and-puma \
      --landfile test_data/sample_input_land.dat \
      --harefile test_data/sample_input_hare.dat \
      --pumafile test_data/sample_input_puma.dat

Introduction
------------

This is a simulation of a predator/pray model using a pair of coupled, time dependent PDEs

&part;H/&part;t = rH - aHP + k &nabla;^2 H  
&part;P/&part;t = bHP - mP + l &nabla;^2 P

Where H and P are 2D fields representing the densities of hares and pumas
at a given point in space,  
t is time,  
r is the rate of birth of hares,  
a is the rate of predation of hares by pumas,  
k is the diffusion coefficient of the hares,  
b is the rate of birth of pumas (dependant on the number of hares to
  feed their young),  
m is the rate of death of pumas (by old age) and  
l is the diffusion coefficient of the pumas.

These variables can be set by passing the appropriate option on the command line,
eg "-a 0.04" to set "a" to 0.04.
If no option is given, a sane default value is used.

These variables can also be set in bulk by specifying a configuration file.
Details of this can be found by running `hare-and-puma --help` for variable names
and in `test_data/test_config_file.cfg` for an example configuration file.
