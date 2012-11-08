#include "write_ppm.h"
#include "board_setter.h"
#include <cstdio>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

void test_first_line_correct();
void test_correct_number_of_lines();
void test_correct_number_of_elements();
void test_no_hares_no_pumas_all_land();
void test_no_hares_no_pumas_all_water();
void test_constant_hares_constant_pumas_all_water();
void test_no_hares_constant_pumas_all_land();
void test_constant_hares_no_pumas_all_land();
void test_constant_hares_constant_pumas_all_land();
void test_no_hares_linear_pumas_all_land();
void test_linear_hares_no_pumas_all_land();
void test_non_integer_hares_no_pumas_all_land();
void test_no_hares_non_integer_pumas_all_land();
void test_sample_input();
void test_sample_input_xstretch();
void test_sample_input_ystretch();

void init_all_land(Board<Tile>& board);
void init_all_water(Board<Tile>& board);
void init_no_hares(Board<Tile>& board);
void init_no_pumas(Board<Tile>& board);
void init_constant_hares(Board<Tile>& board);
void init_constant_pumas(Board<Tile>& board);
void init_linear_hares(Board<Tile>& board);
void init_linear_pumas(Board<Tile>& board);
void init_non_integer_hares(Board<Tile>& board);
void init_non_integer_pumas(Board<Tile>& board);
void init_sample_input(Board<Tile>& board);
void init_sample_input_xstretch(Board<Tile>& board);
void init_sample_input_ystretch(Board<Tile>& board);

int count_elements_in_string(string str);
string return_next_element_in_string(string& str);

int main()
{
	create_output_directory("test");
	test_first_line_correct();
	test_correct_number_of_lines();
	test_correct_number_of_elements();
	test_no_hares_no_pumas_all_land();
	test_no_hares_no_pumas_all_water();
	test_constant_hares_constant_pumas_all_water();
	test_no_hares_constant_pumas_all_land();
	test_constant_hares_no_pumas_all_land();
	test_constant_hares_constant_pumas_all_land();
	test_no_hares_linear_pumas_all_land();
	test_linear_hares_no_pumas_all_land();
	test_sample_input();
	test_sample_input_xstretch();
	test_sample_input_ystretch();
}

void test_first_line_correct()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	
	init_all_land(board);
	init_no_hares(board);
	init_no_pumas(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	if(line != "P3 5 5 255")
	{
		cerr << "Error: First line was not as expected" << endl;
		exit(1);
	}
}

void test_correct_number_of_lines()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	int line_count= 0;
	
	init_all_land(board);
	init_no_hares(board);
	init_no_pumas(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	while(getline(test_file, line))
	{
		line_count++;
	}
	if(line_count != 12)
	{
		cerr << "Error: Line count was incorrect, actually counted" << endl;
		exit(1);
	}
}

void test_correct_number_of_elements()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	int element_count=0;
	
	init_all_land(board);
	init_no_hares(board);
	init_no_pumas(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	while(getline(test_file, line))
	{
		element_count += count_elements_in_string(line);
	}
	if(element_count != 25)
	{
		cerr << "Error: Element count was incorrect" << endl;
		exit(1);
	}
}

void test_no_hares_no_pumas_all_land()
{
	
	Board<Tile> board;
	ifstream test_file;
	string line;
	string element;
	
	init_all_land(board);
	init_no_hares(board);
	init_no_pumas(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	while(getline(test_file, line))
	{
		element = return_next_element_in_string(line);
		if(element == "NULL")
		{
			break;
		}
		else if(element != "0 0 0")
		{
			cerr << "Error: Non-Zero RGB value found " << endl;
			exit(1);
		}
	}
}

void test_no_hares_no_pumas_all_water()
{
	
	Board<Tile> board;
	ifstream test_file;
	string line;
	string element;
	
	init_all_water(board);
	init_no_hares(board);
	init_no_pumas(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	while(getline(test_file, line))
	{
		element = return_next_element_in_string(line);
		while(element != "NULL")
		{
			if(element != "  0   0 255")
			{
				cerr << "Error: Non-water found (this is a serious problem): " << endl;
				exit(1);
			}
			element = return_next_element_in_string(line);
		}
	}
}

void test_constant_hares_constant_pumas_all_water()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	string element;
	
	init_all_water(board);
	init_constant_hares(board);
	init_constant_pumas(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	while(getline(test_file, line))
	{
		element = return_next_element_in_string(line);
		while(element != "NULL")
		{
			if(element != "  0   0 255")
			{
				cerr << "Error: Animals found in the water" << endl;
				exit(1);
			}
			element = return_next_element_in_string(line);
		}
	}
}

void test_constant_hares_no_pumas_all_land()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	string element;
	
	init_all_land(board);
	init_constant_hares(board);
	init_no_pumas(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	while(getline(test_file, line))
	{
		element = return_next_element_in_string(line);
		while(element != "NULL")
		{
			if(element != "  0   1   0")
			{
				cerr << "Error: Constant hares incorrectly displayed" << endl;
				exit(1);
			}
			element = return_next_element_in_string(line);
		}
	}
}

void test_no_hares_constant_pumas_all_land()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	string element;
	
	init_all_land(board);
	init_no_hares(board);
	init_constant_pumas(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	while(getline(test_file, line))
	{
		element = return_next_element_in_string(line);
		while(element != "NULL")
		{
			if(element != "  2   0   0")
			{
				cerr << "Error: Constant pumas incorrectly displayed" << endl;
				exit(1);
			}
			element = return_next_element_in_string(line);
		}
	}
}

void test_constant_hares_constant_pumas_all_land()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	string element;
	
	init_all_land(board);
	init_constant_hares(board);
	init_constant_pumas(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	while(getline(test_file, line))
	{
		element = return_next_element_in_string(line);
		while(element != "NULL")
		{
			if(element != "  2   1   0")
			{
				cerr << "Error: Constant hares and pumas incorrectly displayed" << endl;
				exit(1);
			}
			element = return_next_element_in_string(line);
		}
	}
}

void test_no_hares_linear_pumas_all_land()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	string element;
	stringstream expected_element;
	
	init_all_land(board);
	init_no_hares(board);
	init_linear_pumas(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	for(int i=5; i>=1; i--)
	{
		getline(test_file, line);
		getline(test_file, line);
		for(int j=5; j>=1; j--)
		{
			expected_element.str("");	
			expected_element << "  " <<  i+j-1 << "   0   0";
			element = return_next_element_in_string(line);
			if(element != expected_element.str())
			{
				cerr << "Error: linear pumas incorrectly displayed;" << element << " " << expected_element.str() << endl;
				exit(1);
			}
		}
	}
}

void test_linear_hares_no_pumas_all_land()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	string element;
	stringstream expected_element;
	
	init_all_land(board);
	init_linear_hares(board);
	init_no_pumas(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	for(int i=1; i<=5; i++)
	{
		getline(test_file, line);
		getline(test_file, line);
		for(int j=1; j<=5; j++)
		{
			expected_element.str("");
			expected_element << "  0   " <<  i+j-1 << "   0";
			element = return_next_element_in_string(line);
			if(element != expected_element.str())
			{
				cerr << "Error: linear hares incorrectly displayed" << endl;
				exit(1);
			}
		}
	}
}

void test_no_hares_non_linear_pumas_all_land()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	string element;
	stringstream expected_element;
	
	init_all_land(board);
	init_no_hares(board);
	init_non_integer_pumas(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	for(int i=5; i>=1; i--)
	{
		getline(test_file, line);
		getline(test_file, line);
		for(int j=5; j>=1; j--)
		{
			expected_element.str("");
			expected_element << "  " <<  i+j-1 << "   0   0";
			element = return_next_element_in_string(line);
			if(element != expected_element.str())
			{
				cerr << "Error: non_integer pumas incorrectly displayed" << endl;
				exit(1);
			}
		}
	}
}

void test_non_integer_hares_no_pumas_all_land()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	string element;
	stringstream expected_element;
	
	init_all_land(board);
	init_non_integer_hares(board);
	init_no_pumas(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	for(int i=1; i<=5; i++)
	{
		getline(test_file, line);
		getline(test_file, line);
		for(int j=1; j<=5; j++)
		{
			expected_element.str("");
			expected_element << "  0   " <<  i+j-1 << "   0";
			element = return_next_element_in_string(line);
			if(element != expected_element.str())
			{
				cerr << "Error: non_integer hares incorrectly displayed" << endl;
				exit(1);
			}
		}
	}
}

void test_sample_input()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	string element;
	stringstream expected_element;
	int hares;
	int pumas;
	
	init_sample_input(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	for(int i=1; i<=24; i++)
	{
		getline(test_file, line);
		getline(test_file, line);
		for(int j=1; j<=24; j++)
		{
			expected_element.str("");
			if(i <= 16 && i >= 9 && j <= 16 && j >= 9)
			{
				expected_element << "  0   0 255";
			}
			else
			{
				if(i<=12)
				{
					hares = j*10;
				}
				else hares = 0;
				if(j>12)
				{
					pumas = 250-i*10;
				}
				else pumas = 0;
				expected_element << setfill(' ') << setw(3) << pumas << " " << setfill(' ') << setw(3) << hares << "   0";
			}
			element = return_next_element_in_string(line);
			if(element != expected_element.str())
			{
				cerr << "Error: sample input incorrectly displayed" << endl;
				exit(1);
			}
		}
	}
}

void test_sample_input_xstretch()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	string element;
	stringstream expected_element;
	int hares;
	int pumas;

	init_sample_input_xstretch(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm", "test");
	test_file.open("test/test_ppm_0.000.ppm", ifstream::in);
	getline(test_file, line);
	for(int i=1; i<=24; i++)
	{
		getline(test_file, line);
		getline(test_file, line);
		for(int j=1; j<=25; j++)
		{
			expected_element.str("");
			if(i <= 16 && i >= 9 && j <= 16 && j >= 9)
			{
				expected_element << "  0   0 255";
			}
			else
			{
				if(i<=12)
				{
					hares = j*10;
				}
				else hares = 0;
				if(j>12)
				{
					pumas = 250-i*10;
				}
				else pumas = 0;
				expected_element << setfill(' ') << setw(3) << pumas << " " << setfill(' ') << setw(3) << hares << "   0";
			}
			element = return_next_element_in_string(line);
			if(element != expected_element.str())
			{
				cerr << "Error: sample input incorrectly displayed" << endl;
				exit(1);
			}
		}
	}
}

void test_sample_input_ystretch()
{
	Board<Tile> board;
	ifstream test_file;
	string line;
	string element;
	stringstream expected_element;
	int hares;
	int pumas;
	
	init_sample_input_ystretch(board);

	write_adjustable_ppm(board, 0.0, 1, 0, "test_ppm_ystretch", "test");
	test_file.open("test/test_ppm_ystretch_0.000.ppm", ifstream::in);
	getline(test_file, line);
	for(int i=1; i<=25; i++)
	{
		getline(test_file, line);
		getline(test_file, line);
		for(int j=1; j<=24; j++)
		{
			expected_element.str("");
			if(i <= 16 && i >= 9 && j <= 16 && j >= 9)
			{
				expected_element << "  0   0 255";
			}
			else
			{
				if(i<=12)
				{
					hares = j*10;
				}
				else hares = 0;
				if(j>12)
				{
					pumas = 250-i*10;
				}
				else pumas = 0;
				expected_element << setfill(' ') << setw(3) << pumas << " " << setfill(' ') << setw(3) << hares << "   0";
			}
			element = return_next_element_in_string(line);
			if(element != expected_element.str())
			{
				cerr << "Error: sample input ystretch incorrectly displayed: ("<<j<<","<<i<<") " << element << ": " << expected_element.str() << endl;
				exit(1);
			}
		}
	}
}

void init_all_land(Board<Tile>& board)
{
  BoardSetter::set_land_from_file(board, "../test_data/test_all_land.dat");
}

void init_all_water(Board<Tile>& board)
{
  BoardSetter::set_land_from_file(board, "../test_data/test_all_water.dat");
}

void init_no_hares(Board<Tile>& board)
{
  BoardSetter::set_hare_from_file(board, "../test_data/test_no_hares.dat");
}

void init_no_pumas(Board<Tile>& board)
{
  BoardSetter::set_puma_from_file(board, "../test_data/test_no_pumas.dat");
}

void init_constant_hares(Board<Tile>& board)
{
  BoardSetter::set_hare_from_file(board, "../test_data/test_constant_hares.dat");
}

void init_constant_pumas(Board<Tile>& board)
{
  BoardSetter::set_puma_from_file(board, "../test_data/test_constant_pumas.dat");
}

void init_linear_hares(Board<Tile>& board)
{
  BoardSetter::set_hare_from_file(board, "../test_data/test_linear_hares.dat");
}

void init_linear_pumas(Board<Tile>& board)
{
  BoardSetter::set_puma_from_file(board, "../test_data/test_linear_pumas.dat");
}

void init_non_integer_hares(Board<Tile>& board)
{
  BoardSetter::set_hare_from_file(board, "../test_data/test_non_integer_hares.dat");
}

void init_non_integer_pumas(Board<Tile>& board)
{
  BoardSetter::set_puma_from_file(board, "../test_data/test_non_integer_pumas.dat");
}

void init_sample_input(Board<Tile>& board)
{
  BoardSetter::set_land_from_file(board, "../test_data/sample_input_land.dat");
  BoardSetter::set_hare_from_file(board, "../test_data/sample_input_hares.dat");
  BoardSetter::set_puma_from_file(board, "../test_data/sample_input_pumas.dat");
}

void init_sample_input_xstretch(Board<Tile>& board)
{
  BoardSetter::set_land_from_file(board, "../test_data/sample_input_xstretch_land.dat");
  BoardSetter::set_hare_from_file(board, "../test_data/sample_input_xstretch_hares.dat");
  BoardSetter::set_puma_from_file(board, "../test_data/sample_input_xstretch_pumas.dat");
}

void init_sample_input_ystretch(Board<Tile>& board)
{
  BoardSetter::set_land_from_file(board, "../test_data/sample_input_ystretch_land.dat");
  BoardSetter::set_hare_from_file(board, "../test_data/sample_input_ystretch_hares.dat");
  BoardSetter::set_puma_from_file(board, "../test_data/sample_input_ystretch_pumas.dat");
}

string return_next_element_in_string(string& str)
{
	string element;

	if(str.find("\t") == string::npos)
	{
		return "NULL";
	}
	element = str.substr(0, str.find("\t"));	
	str.erase(0, str.find("\t")+1);
	return element;
}

int count_elements_in_string(string str)
{
	int count = 0;
	while(str.find("\t") != string::npos)
	{
		str.erase(0, str.find("\t")+1);
		count ++;
	}
	return count;
}
