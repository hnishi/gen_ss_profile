#!/bin/bash -eu

dn_in1=out_do7_subsets

mkdir -p $dn_in1 

for i in {0..49}
do
  awk -v zzz="${i}"  'BEGIN{print 27}NR>2&&NR%10==zzz{print $0}' ../ssdump_1_10_cut10ns.dat > ${dn_in1}/${i}.dat
done
