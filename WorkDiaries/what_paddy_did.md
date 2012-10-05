The Paddy Diaries
=================

4/10/2012
---------

-Decided on implementing unit testing throughout project

-Wrote quick board class for handling 2d array
--Began by using new[] and delete[] to manage memory, then decided to inherit from std::vector instead so memory management could be implemented by some much smarter people than me

-Wrote tile class for handling data in each tile
--Has data on density for hares and pumas
--Has data on whether it''s land or not
---Has boolean method to check if it is land or not
---Has simple methods for making it land or not
---Means others don''t have to know how exactly how land and water is implemented

-Wrote board_setter class for setting a given board based on some input files
--Chose to follow a standard very similar to the pgm file format
--Wrote in some little bits to make file reading more resiliant to funny formatting
--Extended std::ifstream for reading rows of numbers so reading rows remained oo looking
