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
