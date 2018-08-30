// v1.2

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define REAL double


int main(int argc,char *argv[]){
  if(!argv[1]){
    puts("USAGE: ./a.out ssdump.dat ");
    printf("You can add the second argment for no elimination \nof the initial frame of your trajectory file\n");
    printf("For example, ./a.out ssdump.dat 1 \n");
    return 1;
  }

  printf("\nYour file: %s \n",argv[1]);

  FILE *fin1;

  if((fin1=fopen(argv[1],"r")) == NULL){
    printf("File Open Error!! 1 \n");
    exit(1);    
  }

  //secondary structure
  char ss[64];

  ss[0]='H';
  ss[1]='B';
  ss[2]='E';
  ss[3]='G';
  ss[4]='I';
  ss[5]='T';
  ss[6]='S';

  int i=0,j=0;
  for(i=7;i<64;i++){
    ss[i]='0';
  }

  int n_frame=0, n_ss_type=7, n_residue;

  char c_buf;

  //fscanf(fin1,"%d", &n_residue);
  char s_buf[512];
  fgets(s_buf,sizeof(s_buf),fin1);
  sscanf(s_buf,"%d",&n_residue);
   
  int n_ss[n_residue][64];
  for(i=0;i<64;i++){
    for(j=0;j<n_residue;j++){
      n_ss[j][i]=0;
    }
  }

  if(!argv[2])fgets(s_buf,sizeof(s_buf),fin1); //for elimination of the initial structure

  while(fgets(s_buf,sizeof(s_buf),fin1)!=NULL){
    int bool1=0;
    //printf("\n %c",c_buf);
    //printf("\n %s",s_buf);
    
    for(j=0;j<n_residue;j++){
      i=0;
      c_buf=s_buf[j];
      //printf(" %c",c_buf);
      while(ss[i]!='0'){
        if(c_buf==ss[i]){
          n_ss[j][i]++;
          bool1=1;
          //printf("j=%d, i=%d, ss[i]=%c, c_buf=%c \n",j,i,ss[i],c_buf);
        }
        i++;
      }
      if(bool1==0){
        ss[i]=c_buf; 
        n_ss[j][i]++;
        n_ss_type++;
        //printf("j=%d, i=%d, ss[i]=%c, c_buf=%c \n",j,i,ss[i],c_buf);
        printf("Unknown secondary structure found: id %d, symbol %c\n",i+1, ss[i]);
      }
      //fscanf(fin1,"%c", &c_buf);
    }
    //fscanf(fin1,"%*c");
    n_frame++;
  }
  fclose(fin1);

  printf("\nThe number of types of secondary structure: %d \n", n_ss_type);
  printf("The number of residues: %d \n", n_residue);
  printf("The number of frames: %d \n", n_frame);

  printf("\nTypes of secondary structure\n");
  for(i=0;i<n_ss_type;i++){
    printf("%d %c \n",i+1,ss[i]);
  }

  printf("\nresidue ");
  for(i=0;i<n_ss_type;i++){
    printf("%7c ",ss[i]);
  }
  printf("\n");
  for(j=0;j<n_residue;j++){
    printf("%-7d",j+1);
    for(i=0;i<n_ss_type;i++){
      printf(" %7.5f",(REAL)n_ss[j][i]/(REAL)n_frame);
    }
    printf("\n");
  }

  int n_other[n_residue];
  for(j=0;j<n_residue;j++){
    n_other[j]=0;
    for(i=7;i<n_ss_type;i++)n_other[j]+=n_ss[j][i];
    //printf("n_other[%d]=%d \n",j,n_other[j]);
  }
  printf("\nresidue   helix   sheet    coil\n");
  for(j=0;j<n_residue;j++){
    printf("%-7d",j+1);
      printf(" %7.5f %7.5f %7.5f\n",\
          (REAL)(n_ss[j][0]+n_ss[j][3]+n_ss[j][4])/(REAL)n_frame,\
          (REAL)(n_ss[j][1]+n_ss[j][2])/(REAL)n_frame,\
          (REAL)(n_ss[j][5]+n_ss[j][6]+n_other[j])/(REAL)n_frame);
  }

  return 0;
  }
