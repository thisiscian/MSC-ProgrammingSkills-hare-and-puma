#! /bin/bash

g++ -o update_performance_test update_performance_test.cpp update_animals.cpp update_animals_p.cpp tile.cpp

echo Compiled Succesfully
echo Now running test, time will be measured in seconds

./update_performance_test

echo Test complete
