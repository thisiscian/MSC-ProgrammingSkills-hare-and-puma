What Ruairi Did With His Time
============================

04/10/12

-Discussed tasks to be done and conventions to be adopted
-I am doing the update implementations
-wrote update hares function
-considered whether to copy to hares array before computing update or after, decided on after
-comtemplating whether to compute number of adjacent land elements inline or in seperate loop for performance reasons

04/10/12 17:00
-wrote "update_pumas" code
-learned, to some degree how to you automake
-wrote 2 small tests to see if "update_hares" and "update_pumas" are working

04/10/12 23:00
-wrote more tests to check pumas die without hares

08/10/12 20:00
-wrote migration of pumas and hares test
-fixed bracketing mistake in "update_hares" formula
-made "update_hares" and "update_pumas" formulae more readable with new lines

09/10/12 21:00
-wrote test to check for negative animals
-stopped negative animals from occuring by setting them to 0 if they happen
-fixed brackets in "update_pumas.cpp" to make sure they die
-combined "update_hares.cpp" and "update_pumas.cpp" into one routine "update_animals.cpp"
-included if statement to ensure animals arent being updated on water sites
-wrote test to check if animals are being updated on water sites

29/10/12 20:00
-wrote performance test to determine best loop index ordering. Determined that the outer loop should be over the second coordinate in field
-considered updating in-place but decided against due to needing to know old hare values for pumas and vice versa
-changed land checking so that it is used properly
-deleted old performance test (results done and finished with, didnt need it anymore) and used framework to test performance of land checking
-found correct land checking to be faster

30/10/12 09:00
-wrote parallel version of update operation
-noted that it is probably an unnecessarily large amount of work to parallelize in a general sense though one can see very good speed-ups if the grid size is large

6/11/12 09:00
-added -Wall to compilation flags
-decided to simply add documentation to say that it can be run in parallel and it will show better performance for large grids but not for small ones of large number of processors are used

6/11/12 17:00
-changed parallel to introducing a parallel region and initiating parallel fors as this will allow the main program have a parallel region meaning that threads wont need to be initiated every time update_animals is called
-moved hare and puma negative checking to inline with update operation
-moved adjacent hare and puma computation to land chacking part to keep the memory access to adjacent tiles together

7/11/12 10:00
-changed loop index ordering and found x outer, y inner to be better
