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
update_test_SOURCES = tile.cpp update_test.cpp update_animals.cpp
output_test_SOURCES = tile.cpp output.cpp output_test.cpp statistics.cpp
distribution_test_SOURCES = distribution_test.cpp
ncurses_test_SOURCES = tile.cpp ncurses_test.cpp statistics.cpp ncurses_lib.cpp test_field.cpp update_animals.cpp
ncurses_test_CXXFLAGS = -lncurses


GUI_TESTS = board_test tile_test


#
# Guitest macro. Builds and runs gui tests by running "make guitest".
# A proxy target exists in the root Makefile.am that cds into this
# directory and makes this one.
#
#   Useage:
#     // in Makefile.am:
#     GUI_TESTS = test_1 test_2 test_3 ...
#     // on command line:
#     make guitest
#
.PHONY : guitest
guitest : $(GUI_TESTS)
	@pass_count=0;\
	for i in $(GUI_TESTS); do \
		./$$i \
		&& echo "PASS: $$i" \
		|| echo FAIL: $$i; \
	done;
