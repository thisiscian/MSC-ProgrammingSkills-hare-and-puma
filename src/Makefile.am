bin_PROGRAMS = hare-and-puma

hare_and_puma_SOURCES = board_setter.cpp tile.cpp options.cpp main.cpp
hare_and_puma_CPPFLAGS = $(BOOST_CPPFLAGS)
hare_and_puma_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LDFLAGS)
hare_and_puma_LDADD = $(BOOST_PROGRAM_OPTIONS_LIBS)
 

<<<<<<< HEAD
check_PROGRAMS = board_test tile_test update_test input_test output_test qt_test
TESTS = board_test tile_test update_test input_test output_test qt_test

board_test_SOURCES = board_test.cpp
tile_test_SOURCES = tile_test.cpp
input_test_SOURCES = input_test.cpp
update_test_SOURCES = update_test.cpp update_hares.cpp update_pumas.cpp
output_test_SOURCES = output.cpp output_test.cpp
qt_test_SOURCES = qt_test.cpp qt.cpp
=======
check_PROGRAMS = board_test tile_test update_test input_test output_test distribution_test
TESTS = board_test tile_test update_test input_test output_test distribution_test

board_test_SOURCES = board_test.cpp
tile_test_SOURCES = tile.cpp tile_test.cpp
input_test_SOURCES = board_setter.cpp tile.cpp input_test.cpp
update_test_SOURCES = tile.cpp update_test.cpp update_hares.cpp update_pumas.cpp
output_test_SOURCES = tile.cpp output.cpp output_test.cpp
distribution_test_SOURCES = distribution_test.cpp
>>>>>>> 964b4a9d90e039f8a99799a2a55db319575c2820
