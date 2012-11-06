#! /bin/bash

make check

#qsub -cwd -pe omp 4 update.sge
./src/update_performance_test

echo Test complete
