The Paddy Diaries
=================

4/10/2012
---------

- Decided on implementing unit testing throughout project

- Wrote quick board class for handling 2d array
  - Began by using new[] and delete[] to manage memory,
    then decided to inherit from std::vector instead so
    memory management could be implemented by some much
    smarter people than me

- Wrote tile class for handling data in each tile
  - Has data on density for hares and pumas
  - Has data on whether it''s land or not
    - Has boolean method to check if it is land or not
    - Has simple methods for making it land or not
    - Means others don''t have to know how exactly how
      land and water is implemented, free to change internal implementation

- Wrote board_setter class for setting a given board based on some input files
  - Chose to follow a standard very similar to the pgm file format
  - Wrote in some little bits to make file reading more resiliant
    to funny formatting
  - Extended std::ifstream for reading rows of numbers so reading
    rows remained oo looking


7/8/2012
--------
- Added boost library for parsing command line options
  - Required including .m4 file written by some kind soul
  - Configure now checks to make sure boost library is installed
    and specifically that boost::program_options is available

- Added command line arguments
  - Will eventually add support for defining configuration files
    that contain much the same arguments. This sort of thing is
    supported by boost::program_options.

- Added support for compiling with the Qt library
  - Found set of scripts by TrollTech which runs qmake on a fake
    project and processes the generated Makefile to find paths
    and libraries that qmake adds.
  - Required editing configure.ac, Makefile.am and adding M4 script
  - Didn''t have to switch from using Automake to qmake like a chump
  - Configure should now check that Qt is installed.

- Added support for custom distributions when setting tiles at random
  - Messed about with function pointers
  - Decided that wasn''t dynamic enough for what I wanted, so I
    played about with functional programming a bit
  - Found that C++ didn''t support that in a way that would be useful,
    so I figured I was probably doing it wrong and that there should
    be a better way.
  - Eventually settled on writing classes that inherit from a
    DistributionBase<T> class, so functions requiring an input
    distribution can be defined f(DistributionBass<some_type> dist)
    and have some class with an overloaded operator()(size_t,size_t)
    passed in that has inherited DistributionBase<some_type>.
  - This inheritence model also makes it much more obvious for another
    programmer how a new distribution can be defined.
