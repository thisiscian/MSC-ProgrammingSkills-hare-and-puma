#include "options.h"


#define EXECUTABLE "./src/options_test"

#define test_option(option, value, assertion) \
{\
  Options options;\
  int argc = 5;\
  char *argv[] = {\
    (char*) EXECUTABLE, \
    (char*) "--land", (char*) "../test_data/test_land_input.dat", \
    (char*) option, (char*) value, (char*) NULL\
  };\
\
  int ret = options.parse_input(argc, argv);\
\
  /* parse_input should not return error */\
  if(ret != 0)\
  {\
    std::cerr.rdbuf(oldCerrStreamBuf);\
    std::cout.rdbuf(oldCoutStreamBuf);\
    std::cerr << option << " test returned error" << std::endl;\
    return 1;\
  }\
\
  /* config filename should be set */\
  if(!(assertion))\
  {\
    std::cerr.rdbuf(oldCerrStreamBuf);\
    std::cout.rdbuf(oldCoutStreamBuf);\
    std::cerr << "There was an error processing the " << option << " option"\
              << std::endl;\
    return 1;\
  }\
}



int main()
{

  // redirect cout and cerr
  std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
  std::stringstream strCout;
  std::cout.rdbuf( strCout.rdbuf() );

  std::streambuf* oldCerrStreamBuf = std::cerr.rdbuf();
  std::stringstream strCerr;
  std::cerr.rdbuf( strCerr.rdbuf() );


  // test empty initialization
  // Should return error
  {
    Options options;
    int argc = 0;
    char *argv[] = {};

    int ret = options.parse_input(argc, argv);

    if( ret != 1 )
    {
      std::cerr.rdbuf(oldCerrStreamBuf);
      std::cout.rdbuf(oldCoutStreamBuf);

      std::cerr << "Empty initialization did not return error"
                << std::endl;
      return 1;
    }
  }


  // check land file
  // should be minimum required data
  {
    Options options;
    int argc = 3;
    char *argv[] = {
      (char*) EXECUTABLE,
      (char*) "--land", (char*) "../test_data/test_land_input.dat",
      (char*) NULL
    };

    int ret = options.parse_input(argc, argv);

    // parse_input should not return error
    if(ret != 0)
    {
      std::cerr.rdbuf(oldCerrStreamBuf);
      std::cout.rdbuf(oldCoutStreamBuf);

      std::cerr << "Land test returned error" << std::endl;
      return 1;
    }

    // config filename should be set
    if(options.land_filename != "../test_data/test_land_input.dat")
    {
      std::cerr.rdbuf(oldCerrStreamBuf);
      std::cout.rdbuf(oldCoutStreamBuf);

      std::cerr << "There was an error processing the land file name"
                << std::endl;
      return 1;
    }
  }


  // check initialization without land file
  // should return error
  {
    Options options;
    int argc = 3;
    char *argv[] = {
      (char*) EXECUTABLE,
      (char*) "--run_time", (char*) "10",
      (char*) NULL
    };

    int ret = options.parse_input(argc, argv);

    // parse_input should not return error
    if(ret != 1)
    {
      std::cerr.rdbuf(oldCerrStreamBuf);
      std::cout.rdbuf(oldCoutStreamBuf);

      std::cerr << "Land file not specified and no error given" << std::endl;
      return 1;
    }
  }



  // check hare file
  test_option("--hare", "../test_data/test_hare_input.dat",
      options.hare_filename == "../test_data/test_hare_input.dat");

  // check puma file
  test_option("--puma", "../test_data/test_puma_input.dat",
      options.puma_filename == "../test_data/test_puma_input.dat");

  // check running time
  test_option("--run_time", "10", options.run_time==10);
  test_option("-t", "10", options.run_time==10);

  // check time step
  test_option("--time_step", "1", options.time_step == 1);
  test_option("-d", "1", options.time_step == 1);

  // check hare birth rate
  test_option("--hare_birth", "10", options.hare_birth == 10);
  test_option("-r", "0.1", options.hare_birth == 0.1);

  // check puma predation rate
  test_option("--puma_predation", "10", options.puma_predation == 10);
  test_option("-a", "0.1", options.puma_predation == 0.1);

  // check hare diffusion rate
  test_option("--hare_diffusion", "10", options.hare_diffusion == 10);
  test_option("-k", "0.1", options.hare_diffusion == 0.1);

  // check puma birth rate
  test_option("--puma_birth", "10", options.puma_birth == 10);
  test_option("-b", "0.1", options.puma_birth == 0.1);

  // check puma death rate
  test_option("--puma_death", "10", options.puma_death == 10);
  test_option("-m", "0.1", options.puma_death == 0.1);

  // check puma diffusion rate
  test_option("--puma_diffusion", "10", options.puma_diffusion == 10);
  test_option("-l", "0.1", options.puma_diffusion == 0.1);

  test_option("--output", "some_output_directory",
      options.output_directory == "some_output_directory");
  test_option("-o", "some_output_directory",
      options.output_directory == "some_output_directory");


  // check input config file
  {
    Options options;
    int argc = 3;
    char *argv[] = {
      (char*) EXECUTABLE,
      (char*) "-c", (char*) "../test_data/test_config_file.cfg",
      (char*) NULL
    };

    int ret = options.parse_input(argc, argv);

    // parse_input should not return error
    if(ret != 0)
    {
      std::cerr.rdbuf(oldCerrStreamBuf);
      std::cout.rdbuf(oldCoutStreamBuf);

      std::cerr << "Config test returned error" << std::endl;
      return 1;
    }

    // config filename should be set
    if(options.config_filename != "../test_data/test_config_file.cfg")
    {
      std::cerr.rdbuf(oldCerrStreamBuf);
      std::cout.rdbuf(oldCoutStreamBuf);

      std::cerr << "There was an error processing the config file name"
                << std::endl;
      return 1;
    }

    // Some other stuff should be set
    if(options.land_filename != "test_data/test_land_input.dat"
        || options.puma_filename != "test_data/test_puma_input.dat"
        || options.hare_filename != "test_data/test_hare_input.dat"
        || options.run_time != 10
      )
    {
      std::cerr.rdbuf(oldCerrStreamBuf);
      std::cout.rdbuf(oldCoutStreamBuf);

      std::cerr << options.land_filename << std::endl;
      std::cerr << options.puma_filename << std::endl;
      std::cerr << options.hare_filename << std::endl;
      std::cerr << options.run_time << std::endl;
      std::cerr << "There was an error processing the config data"
                << std::endl;
      return 1;
    }
  }

  std::cerr.rdbuf(oldCerrStreamBuf);
  std::cout.rdbuf(oldCoutStreamBuf);

  return 0;
}
