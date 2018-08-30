#!/bin/bash -eu


dn_in1=out_do1_subsets 
dn_out1=out_do4_in_std

gcc -O3 nishi.c

rm -rf $dn_out1
mkdir -p $dn_out1

for i in {0..9}
do 
   echo $i 
   ./a.out ${dn_in1}/${i}.dat | tail -n 27 | awk -v zzz="${dn_out1}" '{print $2 >> zzz"/resi"NR"_h.txt"}'  
   ./a.out ${dn_in1}/${i}.dat | tail -n 27 | awk -v zzz="${dn_out1}" '{print $3 >> zzz"/resi"NR"_s.txt"}'  
   ./a.out ${dn_in1}/${i}.dat | tail -n 27 | awk -v zzz="${dn_out1}" '{print $4 >> zzz"/resi"NR"_l.txt"}'  
done

exit


tail -n 27 out.txt > prob_dssp.dat

 awk '{print $2 >> NR".txt"}' ../prob_dssp.dat

