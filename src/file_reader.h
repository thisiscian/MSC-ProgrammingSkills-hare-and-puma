#ifndef __FILE_READER_H__
#define __FILE_READER_H__

#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

class FileReader : public std::ifstream
{
  public:

  std::vector<double> parse_line()
  {
    std::vector<double> values;
    std::string line;

    // ignore comments
    while(true)
    {
      // check if line is comment
      if(peek() == '#')
      {
        std::getline(*this, line);
        continue;
      }
      break;
    }

    // read the line in from the file
    std::getline(*this, line);

    // if line contains no data, just return;
    if(line.length() == 0)
    {
      return values;
    }

    // initialize start to start of string
    size_t number_start = line.find_first_not_of(' ');
    size_t number_end = 0;

    // loop over all numbers in the string
    do
    {
      double this_value = 0;

      // fine next space
      number_end = line.find(' ', number_start);

      // if space not matched, set to end of line
      if(number_end == std::string::npos)
      {
        number_end = line.length();
      }

      // convert string value to numerical value
      this_value = std::atof(
        line.substr(number_start,number_end-number_start).c_str()
      );

      // set next start position to current end position
      // plus 1 for extra space
      number_start = line.find_first_not_of(' ', number_end);

      // push number to output vector
      values.push_back(this_value);
    }
    while(number_start < line.length());


    return values;
  }

};

#endif
