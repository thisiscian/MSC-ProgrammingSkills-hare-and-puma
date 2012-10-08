#include "hare_and_puma_gui.h"

void initialise_simulation_gui()
{
	initscr();
	start_color();
        init_pair(1,COLOR_WHITE,COLOR_BLUE);
	output_height = LINES - input_height;
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
	printw("you shouldn't be able to see this");
	refresh();
	draw_output();
}

void draw_output()
{
	string title = "View of Habitat";
	output = newwin(10,10,10,10);
  box(output, 0 , 0);
	wmove(output, 0, (COLS-title.length())/2);
	attron(A_BOLD);
  wprintw(output,title.c_str());
	attroff(A_BOLD);
  wrefresh(output);
}
