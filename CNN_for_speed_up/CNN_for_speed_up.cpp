#include "CNN_for_speed_up.h"
#include <iostream>

using namespace std;
void CNN_RANDOM_INCREASE ::  second_init()
{
  table.init(data_set);
  for(int y = 0 ; y < data_set ;y++)
  {
    table(y) = -1;
  }

  origin.suffle();
  input = origin;
}
int CNN_RANDOM_INCREASE ::  pre_proccess(int cur_c)//원본데이터에서 실제 쓸데이터를 빼옴 반환값은 0부터 n번째까지 데이터
{
  //input.suffle(1);
  //table.suffle(1);
  return data_set*cur_c/cluster;
}
void CNN_SORT_INCREASE ::  second_init()
{
  table.init(data_set);
  for(int y = 0 ; y < data_set ;y++)
  {
    table(y) = -1;
  }

  sort_table.init(data_set,2);
  for(int y = 0 ; y < data_set ; y++)
  {
    sort_table(y,0) = y;
    sort_table(y,1) = divergence(origin.get_line(y),center.get_line(0));
  }

  //origin.print();
  //center.print();
  //sort_table.print();
  sort_table.ascending(1);

  //sort_table.print();

  //int a;
  //cin>>a;
  
  //input = origin;
}
int CNN_SORT_INCREASE ::  pre_proccess(int cur_c)//원본데이터에서 실제 쓸데이터를 빼옴 반환값은 0부터 n번째까지 데이터
{
  int num = data_set*cur_c/cluster;
  input.init(num,data_dimension);

  for(int y = 0 ; y < num ;y++)
  {
    for(int x = 0 ; x < data_dimension ; x++)
    {
      input(y,x) = origin(sort_table(y,0),x);
    }
  }
  //input.suffle(1);
  //table.suffle(1);
  return num;
}

CNN_FIBONACCI :: CNN_FIBONACCI()
{
  fibo_before = 1;
}
int CNN_FIBONACCI ::  cluster_increase(int before, int after)
{
  int gap = after - before;
  PR1_DATA temp;
  
  temp.init(after,data_dimension);
  
  for(int y = 0 ; y < before ; y ++)
  {
    for(int x = 0 ; x < data_dimension ; x++)
    {
      temp(y,x) = weight(y,x);
    }
  }
  weight = temp;
  temp = weight_table;  
 /* for(int y = 0 ; y < temp.get_row() ; y++)
  {
    if(temp(y,2) == 0) break;
    temp(y,1) = temp(y,1)/temp(y,2);
  }*/
  temp.ascending(1);

  PR1_DATA small;
  small.init(data_dimension);
  small.random(-0.01,0.01);
  int i = 0;
  for(int y = cluster-gap ; y < cluster ; y++, i++)
  {
    for(int x = 0 ; x < data_dimension ; x++)
    {
      weight(before + i,x) = weight(temp(y,0),x) + small(x); 
    }
  }


}

int CNN_FIBONACCI ::  cluster_inclease_method(int before)
{
  int temp = fibo_before;
  fibo_before = before;

  if(before + temp > cluster)
  {
    return cluster;
  }
  else
    return  before + temp;
}