#!/bin/bash -eu

# REQUIREMENT
# 1) mkdssp (DSSP program)
# 2) nishi.c

export DSSP=~/local/bin/mkdssp #/usr/bin/mkdssp

gcc -O3 nishi.c

#gmx_d do_dssp -f ../merge_6_10_prot.xtc -s ../in_prot.gro -ssdump -sss HGI <<< 0 

#awk '{print $2}' scount.xvg > helix_count.dat
./a.out ssdump_1_10_cut10ns.dat > out.txt
tail -n 27 out.txt > prob_dssp.dat

