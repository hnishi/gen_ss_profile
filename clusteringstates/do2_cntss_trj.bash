#!/bin/bash -eu

NAME="do2_cntss_trj.bash";
VERSION=1.0;

echo Program: $NAME  
echo Version: $VERSION  


#awk '{print substr($1,8,4),substr($1,17,4),$2}' out_do12_105.txt |less

dn_in1=out_do1_proccessed
dn_out1=out_do2_prob

################################
# AWK scripts                  #
################################
read -d '' scriptVariable << 'EOF'
BEGIN {
  #print "start"
  #sum1=0  
  #sum2=0
  #sum3=0
  #sum4=0
  #sum5=0
}
NR>1{
  #print NR > fn_out1
  #print $1
  str1=substr($1,8,4)
  str2=substr($1,17,4) 
  str3=substr($1,12,5) 
  #print str1,str2,$0
  if( str1 ~ /H/ && str2 !~ /H/ )
  {
    #print str1,str2,$0
    print "1" > fn_out1
    sum1++ 
  }
  else if( str2 ~ /H/ && str1 !~ /H/ )
  {
    #print str1,str2,$0
    print "2" > fn_out1
    sum2++
  }
  else if( str1 ~ /H/ && str2 ~ /H/ )
  {
    #print str1,str2,$0
    print "3" > fn_out1
    sum3++
  }
  else if( str3 ~ /H/ )
  {
    #print str1,str2,str3,$0
    print "6" > fn_out1
    sum6++
  }
  else if( $1 !~ /H/ )
  {
    #print $0
    print "7" > fn_out1
    sum7++
  }
  else 
  {
    #print str1,str2,$0
    print "4" > fn_out1
    sum4++
  }
  #print substr($1,8,4),substr($1,17,4),$2 
  #print substr($1,8,4),substr($1,17,4),$2 
  #print $1 
  if( substr($1,10,9) ~ "HHHHHHHHH" )
  {
    #print str1,str2,$0
    #print "5" > fn_out1
    sum5++
  }
}
END {
  #print SUMMARY
  #print "1 Only_N-Boundary", sum1
  #print "2 Only_C-Boundary", sum2
  #print "3 Both_N_and_C-Boundary", sum3
  #print "6 Glu_Helix", sum6
  #print "4 Lys_Helix", sum4
  #print "7 No_Helix", sum7
  #print "SUM", sum1+sum2+sum3+sum4+sum6+sum7
  #print "5 Spec", sum5                
  print  sum1/(NR-1) >> dn_out1"/state3.dat" 
  print  sum2/(NR-1) >> dn_out1"/state2.dat" 
  print  sum3/(NR-1) >> dn_out1"/state1.dat" 
  print  sum6/(NR-1) >> dn_out1"/state4.dat" 
  print  sum4/(NR-1) >> dn_out1"/state5.dat" 
  print  sum7/(NR-1) >> dn_out1"/state6.dat" 
}
EOF
################################
# End of AWK Scripts           #
################################

rm -rf $dn_out1

mkdir -p $dn_out1

for i in {1..1000}
do
   echo $i
   awk -v fn_out1=dummy.txt -v dn_out1=$dn_out1 "$scriptVariable" ${dn_in1}/${i}.dat
done

exit

inputfile=out_do1_proccessed/1.dat 
awk -v fn_out1=$outputfile "$scriptVariable" ${inputfile}
#echo $scriptVariable 

