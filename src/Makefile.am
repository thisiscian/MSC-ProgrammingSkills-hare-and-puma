bin_PROGRAMS = hare-and-puma ncurses_test

hare_and_puma_SOURCES = board_setter.cpp tile.cpp options.cpp main.cpp
hare_and_puma_CPPFLAGS = $(BOOST_CPPFLAGS)
hare_and_puma_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LDFLAGS)
hare_and_puma_LDADD = $(BOOST_PROGRAM_OPTIONS_LIBS)
 

check_PROGRAMS = board_test tile_test update_test input_test output_test distribution_test
TESTS = board_test tile_test update_test input_test output_test distribution_test

board_test_SOURCES = board_test.cpp
tile_test_SOURCES = tile.cpp tile_test.cpp
input_test_SOURCES = board_setter.cpp tile.cpp input_test.cpp
update_test_SOURCES = tile.cpp update_test.cpp update_hares.cpp update_pumas.cpp
output_test_SOURCES = tile.cpp output.cpp output_test.cpp statistics.cpp
distribution_test_SOURCES = distribution_test.cpp
ncurses_test_SOURCES = tile.cpp ncurses_test.cpp ncurses_output.cpp statistics.cpp
ncurses_test_CXXFLAGS = -lncurses
