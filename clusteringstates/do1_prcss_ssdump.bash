#!/bin/bash -eu

dn_in1=../../../02dssp/bootstrap/out_do3_gen1000
dn_out1=out_do1_proccessed

mkdir -p $dn_out1

for i in {1..1000}
do
   ls ../../../02dssp/bootstrap/out_do3_gen1000/${i}.dat
   sed -e 's/[HGI]/H/g' -e 's/[^HGI0-9]/./g' ../../../02dssp/bootstrap/out_do3_gen1000/${i}.dat > ${dn_out1}/${i}.dat 
done

exit


sed -e 's/[HGI]/H/g' -e 's/[^HGI0-9]/./g' ../ssdump_1_10_cut10ns.dat > ssdump_1_10_cut10ns_do11.dat 

