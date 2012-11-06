#! /bin/bash

g++ -fopenmp -o update_performance_test update_performance_test.cpp update_animals.cpp update_animals_p.cpp tile.cpp -lm

echo Compilation complete. 
echo To continue please type 1, to stop type anything else

read checkVal

if [ 1 -eq "$checkVal" ]; then
echo Now  submitting test to Morar, time will be measured in seconds

qsub -cwd -pe omp 4 update.sge

echo Test complete
fi
