bin_PROGRAMS = hare-and-puma

hare_and_puma_SOURCES = board_setter.cpp tile.cpp options.cpp main.cpp update_animals.cpp write_ppm.cpp statistics.cpp ncurses_field.cpp field_tile.cpp
hare_and_puma_CPPFLAGS = $(BOOST_CPPFLAGS)
hare_and_puma_CXXFLAGS = -fopenmp
hare_and_puma_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LDFLAGS)
hare_and_puma_LDADD = $(BOOST_PROGRAM_OPTIONS_LIBS)
 

check_PROGRAMS = board_test tile_test update_test board_setter_test write_ppm_test distribution_test options_test ncurses_field_test update_performance_test field_tile_test
TESTS = board_test tile_test update_test board_setter_test write_ppm_test distribution_test options_test main_test.sh

board_test_SOURCES = board_test.cpp
tile_test_SOURCES = tile.cpp tile_test.cpp
board_setter_test_SOURCES = board_setter.cpp tile.cpp board_setter_test.cpp
update_test_SOURCES = tile.cpp update_test.cpp update_animals.cpp
update_test_CXXFLAGS = -fopenmp
write_ppm_test_SOURCES = tile.cpp write_ppm.cpp write_ppm_test.cpp statistics.cpp board_setter.cpp
distribution_test_SOURCES = distribution_test.cpp

options_test_SOURCES = options.cpp options_test.cpp
options_test_CPPFLAGS = $(BOOST_CPPFLAGS)
options_test_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LDFLAGS)
options_test_LDADD = $(BOOST_PROGRAM_OPTIONS_LIBS)

GUI_TESTS = field_tile_test ncurses_test 

field_tile_test_SOURCES = field_tile_test.cpp tile.cpp statistics.cpp field_tile.cpp ncurses_field.cpp update_animals.cpp board_setter.cpp options.cpp 
field_tile_test_CXXFLAGS = -lncurses $(BOOST_CPPFLAGS) -DGUI_TEST
field_tile_test_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LDFLAGS)
field_tile_test_LDADD = $(BOOST_PROGRAM_OPTIONS_LIBS)


ncurses_field_test_SOURCES = tile.cpp ncurses_field_test.cpp statistics.cpp field_tile.cpp ncurses_field.cpp update_animals.cpp board_setter.cpp options.cpp 
ncurses_field_test_CXXFLAGS = -lncurses $(BOOST_CPPFLAGS)
ncurses_field_test_LDFLAGS = $(BOOST_PROGRAM_OPTIONS_LDFLAGS)
ncurses_field_test_LDADD = $(BOOST_PROGRAM_OPTIONS_LIBS)
 
PERFORMANCE_TESTS = update_performance_test
update_performance_test_SOURCES = update_performance_test.cpp update_animals.cpp tile.cpp
update_performance_test_CXXFLAGS = -fopenmp


#
# Custom targets. Build and runs targets by running "make target".
# A proxy target exists in the root Makefile.am that cds into this
# directory and makes this one.
#

#
#   guitest
#
#   Usage:
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

.PHONY : performancetest
performancetest : $(PERFORMANCE_TESTS)
	@for i in $(PERFORMANCE_TESTS); do \
		./$$i; \
	done;
