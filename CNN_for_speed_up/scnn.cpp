#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "CNN_for_speed_up.h"
#include <time.h>


using namespace std;

int main(int argc, char **argv)
{
  if(argc != 5)
  {
    printf("Usage : %s [cluster number] [seperate number] [input text] [result]\n",argv[0]);
    return 0;
  }

  int s_num = atoi(argv[2]);
  int cluster = atoi(argv[1]);
  time_t timer = time(NULL); // 현재 시각을 초 단위로 얻기
  
  
  PR1_DATA data,temp,w_temp;
  PR1_DATA s_data, s_weight;

  data.fread(argv[3]);
  s_data.init(cluster*s_num,data.get_row());
  s_weight.init(cluster*s_num,1);
  temp.init(data.get_column()/s_num, data.get_row());
 
  data.suffle(1);


  CNN_SEPERATE *a = new CNN_SEPERATE[s_num];

  for(int i = 0 ; i < s_num ; i++)
  {
    for(int y = i*temp.get_column() ; y < (i+1)*temp.get_column() ; y++)
    {
      for(int x = 0 ; x < temp.get_row() ; x++)
      {
        temp(y- i*temp.get_column(),x) = data(y,x);
      }
    }

    char buff[100];
    sprintf(buff,"%d scnn",i);

    a[i].init(buff);
    a[i].origin = temp;
    a[i].read_setting(cluster);
    a[i].learning();
    
    w_temp = a[i].get_weight_number();

    for(int y = 0 ; y < w_temp.get_column(); y++)
    {
      for(int x = 0 ; x < w_temp.get_row()-1 ; x++)
      {
        s_data(i*w_temp.get_column() + y,x) = w_temp(y,x);
      }
      s_weight(i*w_temp.get_column() + y,0) = w_temp(y,w_temp.get_row()-1);
    }
  }

   s_data.fwrite("a.txt");
   s_weight.fwrite("b.txt");

 

  delete [] a;
 
  WCNN *b = new WCNN;
  b->init("CNN for speed up : seperate+ WCNN");
 
  b->origin = s_data;
  b->d_weight = s_weight;
  b->read_setting(cluster);
  b->wcnn_learning();
  b->write_all_data(argv[4]);

  
  delete b; 
  cout<<"total time : "<<(double)(time(NULL) - timer)<<"s"<<endl; 
  
  //  s_data.print();
//   s_weight.print();
 // data.print();
 // temp.print();

  return 0;
}
