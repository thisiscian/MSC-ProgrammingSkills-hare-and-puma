#!/usr/bin/env bash

#
# Tests to verify implementation of solution to:
#   dH/dt = r*H - a*H*P + k*(d2H/dx2 + d2H/dy2)
#   dP/dt = b*H*P - m*P + l*(d2P/dx2 + d2H/dy2)
#

#
# This may need a bit of work. Currently, testing
#   exponential growths and decays doesn't seem to work,
#   so it's been left out.
#


#
# Generate board files
#
direct_file=$(mktemp);
checkerboard_file=$(mktemp);
uniform_file=$(mktemp);

#
# Generate output directory
#
output_directory=$(mktemp -d);

clean_output_directory()
{
  ls $output_directory/* >/dev/null 2>/dev/null && rm $output_directory/*
}

extract_hare()
{
  local data="$1"
  echo "$data" |
  sed 's/\(^\|\t\) \+[[:digit:]]\+\ \+\([[:digit:]]\+\)[^\t]*/\2\t/g'
}

extract_puma()
{
  local data="$1"

  echo "$data" |
  sed 's/\(^\|\t\) \+\([[:digit:]]\+\)[^\t]*/\2\t/g'
}

#
# Generate distributions
#

#direct distribution
direct=$(cat <<EOF
 1  2  3  4  5
 6  7  8  9 10
11 12 13 14 15
16 17 18 19 20
21 22 23 24 25
EOF
)
echo "5 5"     >  $direct_file
echo "$direct" >> $direct_file

#checkerboard distribution
checkerboard=$(cat <<EOF
10  0 10  0 10
 0 10  0 10  0
10  0 10  0 10
 0 10  0 10  0
10  0 10  0 10
EOF
)
echo "5 5"           >  $checkerboard_file
echo "$checkerboard" >> $checkerboard_file

#uniform distribution
uniform=$(cat <<EOF
10 10 10 10 10
10 10 10 10 10
10 10 10 10 10
10 10 10 10 10
10 10 10 10 10
EOF
)
echo "5 5"      >  $uniform_file
echo "$uniform" >> $uniform_file


#
# Test 1
#   Set only a, b nonzero
#   Expect H_{t} - H_{t-1} = -a/b * (P_{t} - P_{t-1})
#
clean_output_directory

./hare-and-puma \
  --landfile "$uniform_file" \
  --harefile "$direct_file" \
  --pumafile "$direct_file" \
  --output "$output_directory" \
  --run_time 1 \
  --time_step 0.1 \
  -r 0 \
  -a 0.5 \
  -k 0 \
  -b 0.5 \
  -m 0 \
  -l 0   >/dev/null

data_0=$(cat $output_directory/population_0.000.ppm | tail -n +2)
puma_0=( $( extract_puma "$data_0" ) )
hare_0=( $( extract_hare "$data_0" ) )

data_1=$( cat $output_directory/population_0.100.ppm | tail -n +2)
puma_1=( $( extract_puma "$data_1" ) )
hare_1=( $( extract_hare "$data_1" ) )

maxdiff=2
for i in {0..24}; do
  diff=$(
    echo "( ${hare_0[$i]} - ${hare_1[$i]} ) " \
         "+ ( ${puma_0[$i]} - ${puma_1[$i]} )" |
    bc
  )

  diff=$(echo "$diff" | sed 's/-//')

  if test "$diff" -gt "$maxdiff"; then
    echo "$diff" "$maxdiff"
    echo "Hare and puma equations not coupling properly"
    exit 1;
  fi
done



#
# Test 2
#   Checkerboards with diffusion at 0 should leave 0 entries at 0
#
clean_output_directory

./hare-and-puma \
  --landfile "$uniform_file" \
  --harefile "$checkerboard_file" \
  --pumafile "$checkerboard_file" \
  --output "$output_directory" \
  --run_time 1 \
  --time_step 0.1 \
  -r 0 \
  -a 0.5 \
  -k 0 \
  -b 0.5 \
  -m 0 \
  -l 0  >/dev/null

data_0=$(cat $output_directory/population_0.000.ppm | tail -n +2)
puma_0=( $( extract_puma "$data_0" ) )
hare_0=( $( extract_hare "$data_0" ) )

data_1=$( cat $output_directory/population_0.100.ppm | tail -n +2)
puma_1=( $( extract_puma "$data_1" ) )
hare_1=( $( extract_hare "$data_1" ) )

for i in {0..24}; do
  if test "${puma_0[$i]}" -eq "0"; then
    if test "${puma_1[$i]}" -ne "0"; then
      echo "Empty Puma squares being filled with diffusion turned off"
      exit 1
    fi
  fi

  if test "${hare_0[$i]}" -eq "0"; then
    if test "${hare_1[$i]}" -ne "0"; then
      echo "Empty Hare squares being filled with diffusion turned off"
      exit 1
    fi
  fi
done


#
# Test 3
#   Hares should follow H_0*e^{rt}
#   Pumas should follow P_0*e^{-mt}
#
#clean_output_directory
#
#./hare-and-puma \
#  --landfile "$uniform_file" \
#  --harefile "$direct_file" \
#  --pumafile "$direct_file" \
#  --output "$output_directory" \
#  --run_time 1 \
#  --time_step 0.1 \
#  -r 0 \
#  -a 1 \
#  -k 0 \
#  -b 0 \
#  -m 1 \
#  -l 0  >/dev/null
#
#puma_0=( $(echo "$direct") )
#hare_0=( $(echo "$direct") )
#
#data_1=$(cat $output_directory/population_0.000.ppm | tail -n +2)
#puma_1=( $( extract_puma "$data_1" ) )
#hare_1=( $( extract_hare "$data_1" ) )
#
#data_2=$( cat $output_directory/population_0.100.ppm | tail -n +2)
#puma_2=( $( extract_puma "$data_2" ) )
#hare_2=( $( extract_hare "$data_2" ) )
#
#for i in {0..24}; do
#  chk=$( echo "${puma_0[$i]} * e(1 * 0.1)" | bc -l )
#  echo "$chk" "${puma_0[$i]}" "${puma_1[$i]}" "${puma_2[$i]}"
#done


#
# Test 4
#   Given only diffusion terms, should get a
#     steady state solution
#
clean_output_directory

./hare-and-puma \
  --landfile "$uniform_file" \
  --harefile "$direct_file" \
  --pumafile "$direct_file" \
  --output "$output_directory" \
  --run_time 50 \
  --time_step 0.1 \
  -r 0 \
  -a 0 \
  -k 1 \
  -b 0 \
  -m 0 \
  -l 1  >/dev/null

data_0=$(cat $output_directory/population_49.800.ppm | tail -n +2)
puma_0=( $( extract_puma "$data_0" ) )
hare_0=( $( extract_hare "$data_0" ) )

data_1=$( cat $output_directory/population_49.900.ppm | tail -n +2)
puma_steady=$( extract_puma "$data_1" )
puma_1=( $(echo $puma_steady) )
hare_steady=$( extract_hare "$data_1" )
hare_1=( $(echo $hare_steady) )

for i in {0..24}; do
  if test "${puma_0[$i]}" -ne "${puma_1[$i]}"; then
    echo "Steady state solution for Pumas not found in pure diffusion situation"
    exit 1
  fi
  if test "${hare_0[$i]}" -ne "${hare_1[$i]}"; then
    echo "Steady state solution for Hares not found in pure diffusion situation"
    exit 1
  fi
done

#
# Test 5
#   Given a steady state solution, the program should
#     return a steady state solution
#
clean_output_directory

steady_hare_file=$(mktemp)
steady_puma_file=$(mktemp)

echo "5 5"          >  $steady_hare_file
echo "$hare_steady" >> $steady_hare_file

echo "5 5"          >  $steady_puma_file
echo "$puma_steady" >> $steady_puma_file

./hare-and-puma \
  --landfile "$uniform_file" \
  --harefile "$steady_hare_file" \
  --pumafile "$steady_puma_file" \
  --output "$output_directory" \
  --run_time 10 \
  --time_step 0.1 \
  -r 0 \
  -a 0 \
  -k 1 \
  -b 0 \
  -m 0 \
  -l 1  >/dev/null


puma_0=( $(echo "$puma_steady") )
hare_0=( $(echo "$hare_steady") )

data_1=$( cat $output_directory/population_9.900.ppm | tail -n +2)
puma_1=( $(echo $puma_steady) )
hare_1=( $(echo $hare_steady) )

for i in {0..24}; do
  if test "${puma_0[$i]}" -ne "${puma_1[$i]}"; then
    echo -n "Steady state solution input for Pumas "
    echo    "does not return the same output in pure diffusion situation"
    exit 1
  fi
  if test "${hare_0[$i]}" -ne "${hare_1[$i]}"; then
    echo -n "Steady state solution input for Hares "
    echo    "does not return the same output in pure diffusion situation"
    exit 1
  fi
done


#
# Clean up
#
rm $direct_file;
rm $checkerboard_file;
rm $uniform_file;

rm -r $output_directory

exit 0;
