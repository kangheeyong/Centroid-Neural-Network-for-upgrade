#include "CNN_for_speed_up.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>

using namespace std;



int WCNN ::  wcnn_calculate_winner_loser(double *arr,PR1_DATA *w,int winner, int loser,int iteration)//반환값은 
{
  if(winner != loser)
  {
    weight_table(winner,2) = weight_table(winner,2) + d_weight(iteration,0);
    for(int x = 0 ; x < data_dimension ; x++)
    {
      (*w)(winner,x) = (*w)(winner,x) +   d_weight(iteration,0)*(arr[x] - (*w)(winner,x))/weight_table(winner,2);
    }
    if(loser != -1)
    {
      weight_table(loser,2) = weight_table(loser,2) - d_weight(iteration,0); 
      for(int x = 0 ; x < data_dimension ; x++)
      {
        (*w)(loser,x) = (*w)(loser,x) -  d_weight(iteration,0)*(arr[x] - (*w)(loser,x))/weight_table(loser,2);
      }
    }
    return 1;
  }
  return 0;
}

void WCNN :: wcnn_learning()
{
  clock_t before_time,now_time;
  time_t timer;
  int before_epoch = 0;
  int average_loser = 0;
  double average_time = 0.0;
  timer = time(NULL); // 현재 시각을 초 단위로 얻기
  double entropy = 0.0;
  int total_n = 0;
  
  c_increase = 0;

  this->first_init();
  this->second_init();
  for(int i = 0 ; i < d_weight.get_column() ;i++) total_n += d_weight(i,0);
  
  while(1){
    int currunt_winner;
    int before_winner;

    iteration_set = pre_proccess(cur_cluster);
    d_weight.suffle(1);
    do{
      before_time = clock();
      q_weight<<weight;
      q_weight_table<<weight_table;
      for(int y = 0 ; y < cluster;y++ )  weight_table(y,1) = 0.0;
      epoch++;
      trade = 0;

      for(int y = 0 ; y < iteration_set ;y++)
      {
        currunt_winner = this->search_winner(input.get_line(y),&weight);
        before_winner = table(y);
        table(y) = currunt_winner;
        trade = trade + this->wcnn_calculate_winner_loser(input.get_line(y),&weight,currunt_winner,before_winner,y);
      }
      MSE = 0.0;
      for(int c = 0 ; c < cur_cluster ; c++) MSE = MSE + weight_table(c,1);
      MSE =MSE / iteration_set;

      now_time = clock();
      epoch_time = (double)(now_time - before_time) / CLOCKS_PER_SEC;

      t_errors(epoch-1,0) = epoch;
      t_errors(epoch-1,1) = MSE;
      t_errors(epoch-1,2) = cur_cluster;
      t_errors(epoch-1,3) = trade;
      t_errors(epoch-1,4) = iteration_set;
      t_errors(epoch-1,5) = epoch_time;
      average_time += epoch_time;
      average_loser += trade;
    //  cout<<trade<<endl;
      if(trade < trade_standard && cur_cluster != cluster) break;
    }while(trade != 0);

    t_c_errors(c_increase,0) = cur_cluster;
    t_c_errors(c_increase,1) = epoch - before_epoch;
    before_epoch = epoch;
    t_c_errors(c_increase,2) = (double)average_loser/t_c_errors(c_increase,1);
    average_loser = 0;
    t_c_errors(c_increase,3) = iteration_set;
    
    for(int i = 0 ; i < cur_cluster ;i++)
    {
      if(weight_table(i,2) > 0.0000000001)
        entropy = entropy - weight_table(i,2)/total_n*log(weight_table(i,2)/total_n)/log(cur_cluster);
    }
    t_c_errors(c_increase,4) = entropy;
    entropy = 0.0;
 
    
    t_c_errors(c_increase++,5) = average_time;
    average_time = 0.0;

    system("clear");
    cout<<"----- "<<name<<" -----"<<endl;
    cout<<"percent : "<<100*cur_cluster/cluster<<"%"<<endl;
    cout<<"cluster : "<<cur_cluster<<endl;
    cout<<"epoch : "<<epoch<<endl;
    cout<<"time : "<<time(NULL)-timer<<"s"<<endl;
    cout<<"------------"<<endl;

    if(cluster == cur_cluster) break;

    before_cluster = cur_cluster;
    cur_cluster = this->cluster_inclease_method(before_cluster);
    
    this->cluster_increase(before_cluster, cur_cluster);
  }
  total_time = (double)(time(NULL) - timer); // 현재 시각을 초 단위로 얻기


  setting.init(4);
  setting(0) = epoch;
  setting(1) = MSE;
  setting(2) = cluster;
  setting(3) = total_time;
  this->post_proccess();
  
}
PR1_DATA CNN_SEPERATE :: get_weight_number()
{
  PR1_DATA temp;

  temp.init(weight.get_column(), weight.get_row()+1);
  
  for(int y = 0 ; y < weight.get_column() ; y++)
  {
    for(int x = 0 ; x < weight.get_row() ; x++)
    {
      temp(y,x) = weight(y,x);
    }
    temp(y,weight.get_row()) = weight_table(y,2);
  }
  return temp;
}
int CNN_SEPERATE ::  pre_proccess(int cur_c)//원본데이터에서 실제 쓸데이터를 빼옴 반환값은 0부터 n번째까지 데이터
{
  input.suffle(1);
  table.suffle(1);

  trade_standard = data_set*0.05;  

  return data_set;//*cur_c/cluster;
}




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

void CNN_LOSER_CHANGE ::  second_init()
{
  table.init(data_set);
  for(int y = 0 ; y < data_set ;y++)
  {
    table(y) = -1;
  }

  origin.suffle();
  input = origin;
}
int CNN_LOSER_CHANGE ::  pre_proccess(int cur_c)//원본데이터에서 실제 쓸데이터를 빼옴 반환값은 0부터 n번째까지 데이터
{
  input.suffle(1);
  table.suffle(1);
  cluster_per_data_error.suffle(1);  
  trade_standard = data_set*0.05;  
  

  return data_set;//*cur_c/cluster;
}



