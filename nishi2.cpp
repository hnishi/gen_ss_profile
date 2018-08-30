// nishi2.cpp  v1.0
// bootstrap analysis of nishi.cpp

// C++ libraries
#include<iostream>
#include<vector> 
#include<string> // for vector<string>
#include<fstream>
#include<cmath>
#include<numeric>
using namespace std;

// C libraries
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define REAL double

int rand_lim(int limit, int seed) {
/* return a random number between 0 and limit inclusive.
 */
    srand(seed);
    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}


int calc_population(vector<string> seq_data, int n_residue, vector<REAL> *out_vec1){
  //secondary structure
  char ss[64];
  int n_ss_type=7;

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

  char c_buf;

  int n_ss[n_residue][64];
  for(i=0;i<64;i++){
    for(j=0;j<n_residue;j++){
      n_ss[j][i]=0;
    }
  }
  for(unsigned int ii=0;ii<seq_data.size();ii++){
    //cout<<ii<<" "<<seq_data[ii];
    int bool1=0;
    for(j=0;j<n_residue;j++){
      i=0;
      c_buf=seq_data[ii].c_str()[j];
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
        //printf("Unknown secondary structure found: id %d, symbol %c\n",i+1, ss[i]);
      }
      //fscanf(fin1,"%c", &c_buf);
    }
    //fscanf(fin1,"%*c");
  }
  int n_other[n_residue];
  for(j=0;j<n_residue;j++){
    n_other[j]=0;
    for(i=7;i<n_ss_type;i++)n_other[j]+=n_ss[j][i];
    //printf("n_other[%d]=%d \n",j,n_other[j]);
  }
  //printf("\nresidue   helix   sheet    coil\n");
  for(j=0;j<n_residue;j++){
  /*  printf("%-7d",j+1);
      printf(" %7.5f %7.5f %7.5f\n",\
          (REAL)(n_ss[j][0]+n_ss[j][3]+n_ss[j][4])/(REAL)seq_data.size(),\
          (REAL)(n_ss[j][1]+n_ss[j][2])/(REAL)seq_data.size(),\
          (REAL)(n_ss[j][5]+n_ss[j][6]+n_other[j])/(REAL)seq_data.size());
  */
    out_vec1->push_back((REAL)(n_ss[j][0]+n_ss[j][3]+n_ss[j][4])/(REAL)seq_data.size());
    out_vec1->push_back((REAL)(n_ss[j][1]+n_ss[j][2])/(REAL)seq_data.size());
    out_vec1->push_back((REAL)(n_ss[j][5]+n_ss[j][6]+n_other[j])/(REAL)seq_data.size());
  }
  return 0;
}

int main(int argc,char *argv[]){
  if(!argv[1]){
    puts("USAGE: ./a.out ssdump.dat output.dat int(random_seed) ");
    printf("You can add the second argment for no elimination \nof the initial frame of your trajectory file\n");
    printf("For example, ./a.out ssdump.dat 1 \n");
    return 1;
  }

  int n_sample = 10;

  printf("\nYour file: %s \n",argv[1]);

  FILE *fin1;

  if((fin1=fopen(argv[1],"r")) == NULL){
    printf("File Open Error!! 1 \n");
    exit(1);    
  }

  int random_seed = atoi(argv[3]);
  printf("Random seed: %d \n",random_seed);
  

  int n_frame=0, n_ss_type=7, n_residue;
  char c_buf;

  //fscanf(fin1,"%d", &n_residue);
  char s_buf[512];
  fgets(s_buf,sizeof(s_buf),fin1);
  sscanf(s_buf,"%d",&n_residue);
   
  int n_ss[n_residue][64];
  for(int i=0;i<64;i++){
    for(int j=0;j<n_residue;j++){
      n_ss[j][i]=0;
    }
  }

  if(!argv[2])fgets(s_buf,sizeof(s_buf),fin1); //for elimination of the initial structure

  vector<string> orig_data;
  int i_data = 0;
  while(fgets(s_buf,sizeof(s_buf),fin1)!=NULL){
    //string str1(s_buf);
    //orig_data.push_back(str1);
    orig_data.push_back(s_buf);
    //cout<<"i_data = "<<i_data<<", orig_data[i] = "<<orig_data[i_data]<<endl;
    
    i_data++;
  }
  fclose(fin1);

  cout<<"total num of data = "<<orig_data.size()<<endl;

  ofstream outfile1;
  outfile1.open(argv[2]);

  outfile1<< n_residue<< endl;
  for(unsigned int i=0;i<orig_data.size();i++){
    int z_seed = random_seed + (int)i + 1;
    int r = rand_lim(orig_data.size()-1, z_seed );
    //int r = rand_lim(20, i+2);
    //vec_buf.push_back(orig_data[r]);
    outfile1<< orig_data[r];
    //cout<<i<<", random num = "<<r<<", seq = "<<orig_data[r]<<endl;
  }

  /*for(int ii=0;ii<n_sample;ii++){
    vector<string> vec_buf;
    for(unsigned int i=0;i<orig_data.size();i++){
      int r = rand_lim(orig_data.size(), ii+i+2);
      //int r = rand_lim(20, i+2);
      //vec_buf.push_back(orig_data[r]);
      //cout<<orig_data[r];
      fprintf(fout1,"%s",orig_data[r].c_str());  
      //cout<<i<<", random num = "<<r<<", seq = "<<orig_data[r]<<endl;
      //cout<<i<<", random num = "<<r<<", seq = "<<vec_buf[i]<<endl;
    }
    //vector<REAL> in_vec1;
    //calc_population(vec_buf, n_residue, &in_vec1);
  }*/
  outfile1.close();
  return 0;
}
