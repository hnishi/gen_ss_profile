#!/bin/bash -eu

NAME="do_histo.bash";
VERSION=1.0;

echo Program: $NAME  
echo Version: $VERSION  


#inputfile=major_major_angle_400ns.dat  
inputfile=out_nishi2_1.dat  #major_major_angle_400ns.dat  
#outfile=histo.dat  
outfile=histo_${inputfile}.dat #histo.dat  

width_win=1.0
min_x=0
max_x=101

# for general histogram, interval_win shold be equal to width_win.
interval_win=1.0 # shift from a previous window

echo $inputfile
echo $outfile
################################
# AWK scripts                  #
################################
read -d '' scriptVariable << 'EOF'
BEGIN {
  for (i=v_min_x;i+v_width_win<=v_max_x;i+=v_interval_win) {
    num_sum[i] = 0; #initialization
  }
  total_data = 0;
}
{
  for (i=v_min_x;i+v_width_win<=v_max_x;i+=v_interval_win) {
    if (i<=$1 && $1<i+v_interval_win) {
      num_sum[i] ++; 
      total_data ++;
    }
  }
}
END {
  for (i=v_min_x;i+v_width_win<=v_max_x;i+=v_interval_win) {
      print i,num_sum[i] > v_outfile
  }
  print "total number of data =", total_data
}
EOF
################################
# End of AWK Scripts           #
################################

awk -v v_min_x="${min_x}" \
    -v v_width_win="${width_win}" \
    -v v_interval_win="${interval_win}" \
    -v v_max_x="${max_x}" \
    -v v_outfile="${outfile}" \
"$scriptVariable" ${inputfile}
