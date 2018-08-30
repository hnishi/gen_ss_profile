#!/bin/bash -eu

NAME="do_std.bash";
VERSION=1.0;

#echo Program: $NAME  
#echo Version: $VERSION  

################################
# AWK scripts                  #
################################
read -d '' scriptVariable << 'EOF'
{
  x[NR] = $1
}
END{
  if(NR == 0) exit
  for(i in x){
    sum_x += x[i]
  }
  m_x = sum_x / NR
  for(i in x){
    sum_dx2 += (x[i] - m_x) ^ 2
  }
  #print "average ",m_x 
  #print "variance",sum_dx2 / NR
  #print "standard_deviation ",sqrt(sum_dx2 / NR)
  printf("%f ",  sqrt(sum_dx2 / NR) )
}
EOF
################################
# End of AWK Scripts           #
################################

#awk -v fn_out1=$outputfile "$scriptVariable" ${inputfile}
#echo $scriptVariable 

   awk "$scriptVariable" out_do2_prob/state1.dat  
   awk "$scriptVariable" out_do2_prob/state2.dat  
   awk "$scriptVariable" out_do2_prob/state3.dat  
   awk "$scriptVariable" out_do2_prob/state4.dat  
   awk "$scriptVariable" out_do2_prob/state5.dat  
   awk "$scriptVariable" out_do2_prob/state6.dat  
   echo

exit

for i in 1 2 3 4 6 7
do
  echo $i
  echo Rg
  awk  "$scriptVariable" rg_${i}.txt
  echo SASA
  awk  "$scriptVariable" sasa_${i}.txt
done  
