#!/bin/bash -eu

dn_out1=out_do3_gen1000

#g++ -O3 nishi2.cpp -o exe_nishi2
#g++ nishi2.cpp -o exe_nishi2
g++ -O3 -Wall nishi2.cpp -o exe_nishi2
  # exe_nishi2 input output random_seed

mkdir -p $dn_out1

cd $dn_out1 

for i in {1..1000}
do
  ../exe_nishi2 ../ssdump_1_10_cut10ns.dat ${i}.dat $i  #> out.txt
done
#tail -n 27 out.txt > prob_dssp.dat

cd ..

