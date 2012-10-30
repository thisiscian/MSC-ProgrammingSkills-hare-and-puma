#! /bin/bash

g++ -o update_performance_test update_performance_test.cpp update_animals.cpp update_animals_p.cpp tile.cpp

echo Compilation complete. 
echo To continue please type 1, to stop type anything else

read checkVal

if [ 1 -eq "$checkVal" ]; then
echo Now running test, time will be measured in seconds

./update_performance_test

echo Test complete
fi
