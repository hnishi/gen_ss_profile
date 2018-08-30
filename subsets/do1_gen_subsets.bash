#!/bin/bash -eu

mkdir -p out_do1_subsets

for i in {0..9}
do
  awk -v zzz="${i}"  'BEGIN{print 27}NR>2&&NR%10==zzz{print $0}' ../ssdump_1_10_cut10ns.dat > out_do1_subsets/${i}.dat
done
