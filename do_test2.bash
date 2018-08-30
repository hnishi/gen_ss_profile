  mkdir out_do3_gen1000_md5sum
  for i in {1..1000};do md5sum out_do3_gen1000/${i}.dat|cut -f 1 -d" " > out_do3_gen1000_md5sum/${i}.md5sum;done &
  for i in {2..1000};do diff -q out_do3_gen1000_md5sum/1.md5sum out_do3_gen1000_md5sum/${i}.md5sum;done > check_diff_md5sum.txt
  grep differ check_diff_md5sum.txt |wc -l 
  grep identical  check_diff_md5sum.txt |wc -l 
