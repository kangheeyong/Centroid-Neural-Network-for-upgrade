#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "CNN_for_speed_up.h"
#include <dirent.h>
#include <sys/stat.h>

using namespace std;


pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER; // 쓰레드 초기화
PR1_DATA global_input;
PR1_DATA WCNN_input;
PR1_DATA WCNN_weight;

char file_name[100];
char dir_name[100];


int ECNN_cluster;
int WCNN_cluster;
int core;

void *Ensenble(void *num); /*thread function*/

int main(int argc, char **argv)
{
  if(argc != 6)
  {
    printf("Usage : %s [core] [ECNN cluster number ][WCNN cluster number] [input text] [result dir]\n",argv[0]);
    return 0;
  }

  core = atoi(argv[1]);
  ECNN_cluster = atoi(argv[2]);
  WCNN_cluster = atoi(argv[3]);
  strcpy(file_name,argv[4]);
  strcpy(dir_name,argv[5]);


  //---------- 타이머 시작-----------------
  struct timespec begin, end ;
  clock_gettime(CLOCK_MONOTONIC, &begin);
  //---------------------------------------

  global_input.fread(file_name);
//  global_input.suffle();
  WCNN_input.init(core*ECNN_cluster,global_input.get_row());
  WCNN_weight.init(core*ECNN_cluster);

  
  mkdir(dir_name,0755);

  long thread; /*64비트 시스템의 경우 long을 사용한다*/
  pthread_t* thread_handles;
  
  thread_handles = (pthread_t*)malloc(core*sizeof(pthread_t));

  for(thread = 0 ; thread< core ; thread++)
  {
    pthread_create(&thread_handles[thread],NULL,Ensenble,(void*)thread);
  }


  printf("Ensenble Centroid NN start\n");

  for(thread = 0 ; thread< core ; thread++)
  {
    pthread_join(thread_handles[thread],NULL);
  }
  printf("Ensenble Centroid NN end\n");
  printf("Weighted Centroid NN start\n");
  free(thread_handles);
  //---------------------------------------------
  WCNN_input.fwrite("a.txt");
  WCNN_weight.fwrite("b.txt");
  


  
  
  CNN_origin *a = new CNN_origin;
  a->init("CNN for speed up : origin");
  a->origin = WCNN_input;
  
  a->read_setting(WCNN_cluster);

  //-----weight 가 없으면 일반 Centroid NN
  a->gain = WCNN_weight;
  //----------------------------------------
  a->learning();
  a->write_all_data(dir_name);
  
 

  delete a;


  printf("Weighted Centroid NN end\n");

  //----------- 타이머 끝 -----------------------
  clock_gettime(CLOCK_MONOTONIC, &end);
  cout<<"total time : " << (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1000000000.0 << endl;
  //--------------------------------------------


  
  return 0;
}



void *Ensenble(void *num) /*thread function*/
{
  long thread_id = (long)num;


  CNN_origin *a = new CNN_origin;
  
  a->init("CNN for speed up : origin");
  
  int row = global_input.get_row();
  int column = global_input.get_column();
 
  int gap = (int)(column/core);



  a->origin.init(gap,row);  
  for(int y = 0 ; y < gap ; y++)
  {
    for(int x = 0 ; x < row ; x++)
    {
      a->origin(y,x) = global_input(gap*thread_id+y,x);
    }
  }

  a->read_setting(ECNN_cluster);
  a->learning();

  char temp[100];
  sprintf(temp,"%s/ECNN_%d",dir_name,(int)thread_id);

 // pthread_mutex_lock(&mutex);
  
  for(int y = 0 ; y < ECNN_cluster ; y++)
  {
    for(int x = 0 ; x < row ; x++)
    {
      WCNN_input(thread_id*ECNN_cluster + y,x) = a->weight(y,x);
    }
    WCNN_weight(thread_id*ECNN_cluster + y) = a->weight_table(y,2); 
  }
  //pthread_mutex_unlock(&mutex);
 
  a->write_all_data(temp);
  
 

  delete a;
  
  printf("Ensenble Centroid NN from thread %ld of %d end\n",thread_id+1,core);


}








