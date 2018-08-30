#!/bin/bash -eu

#g++ -O3 nishi2.cpp -o exe_nishi2
#g++ nishi2.cpp -o exe_nishi2
g++ -O3 -Wall nishi2.cpp -o exe_nishi2

./exe_nishi2 ssdump_1_10_cut10ns.dat out_nishi2_1.dat 1  #> out.txt
#tail -n 27 out.txt > prob_dssp.dat

