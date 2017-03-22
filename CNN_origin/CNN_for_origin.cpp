#include "CNN_for_origin.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;


void CNN_origin :: init(const char* name)
{
  sprintf(this->name,"%s",name);
}

void CNN_origin :: read_input(const char* fname)
{
  this->origin.fread(fname);
}
void CNN_origin :: read_weight(const char *fname)
{
  this->weight.fread(fname);
}
void CNN_origin :: read_setting(int cluster)
{
  this->cluster = cluster;
}

void CNN_origin :: write_all_data(const char* fname)
{
  char buff[1024];

  mkdir(fname,0755);
  sprintf(buff,"%s/weight",fname);
  mkdir(buff,0755);
  sprintf(buff,"%s/weight_table",fname);
  mkdir(buff,0755);

  sprintf(buff,"%s/weight/weight",fname);
  q_weight.lwrite(buff);

  sprintf(buff,"%s/weight_table/weight_table",fname);
  q_weight_table.lwrite(buff);

  sprintf(buff,"%s/errors.txt",fname);
  errors.fwrite(buff);
 
  sprintf(buff,"%s/weight.txt",fname);
  weight.fwrite(buff);

  sprintf(buff,"%s/setting.txt",fname);
  setting.fwrite(buff);

  sprintf(buff,"%s/origin.txt",fname);
  origin.fwrite(buff);




//  input.print();
  
 // this->weight_table.print();
//  this->status(name);
  //errors.print();
  //q_weight.lwrite("weight");
  //q_weight_table.lwrite("weight_table");

}
void CNN_origin :: write_weight(const char* fname)
{
  this->weight.fwrite(fname);
}
void CNN_origin :: write_result(const char *fname)
{
  this->result.fwrite(fname);
}
void CNN_origin :: write_errors(const char *fname)
{
  this->errors.fwrite(fname);
}
void CNN_origin :: write_setting(const char *fname)
{
  this->setting.fwrite(fname);
}

void CNN_origin :: status(char *name)
{
  cout<<"---------"<<name<<"---------"<<endl;
  cout<<"epoch : "<<epoch<<endl;
  cout<<"MSE : "<<MSE<<endl;
  cout<<"cluster : "<<cluster<<endl;
  cout<<"--------- weight --------"<<endl;
  this->weight.print(); 
}
void CNN_origin ::  first_init() //전체 평균 구하기
{
  data_dimension = origin.get_row();
  data_set = origin.get_column();

  center.init(data_dimension);

  for(int x = 0 ; x < data_dimension ; x++)
  {
    for(int y = 0 ; y < data_set ; y++)
    {
      center(x) = center(x) + origin(y,x);
    }
    center(x) = center(x)/data_set;
  }

  weight.init(cur_cluster,data_dimension);
  PR1_DATA small;
  small.init(data_dimension);
  small.random(-0.001 ,0.001);

  for(int x = 0 ; x < data_dimension ; x++)
  {
    weight(0,x) = center(x) + small(x);
    weight(1,x) = center(x) - small(x);
  }
  weight_table.init(cluster,3);
  for(int y = 0 ; y < cluster ; y++)
  {
    weight_table(y,0) = y;
  }
  t_errors.init(MAX_EPOCH,6);
}
void CNN_origin ::  second_init()
{
  table.init(data_set);
  for(int y = 0 ; y < data_set ;y++)
  {
    table(y) = -1;
  }
  input = origin;
}
double CNN_origin ::  divergence(double *arr_in, double *arr_w) //error 계산 함수
{
  int data_dimension = this->data_dimension;
  double  temp = 0.0;
  
  for(int i = 0 ; i < data_dimension ; i++)
    temp = temp + (arr_in[i] - arr_w[i])*(arr_in[i] - arr_w[i]);
  
  return temp;
}
int CNN_origin ::  pre_proccess(int cur_c)//원본데이터에서 실제 쓸데이터를 빼옴 반환값은 0부터 n번째까지 데이터
{
  input.suffle(1);
  table.suffle(1);
  return data_set;//*cur_c/cluster;
}  
int CNN_origin ::  search_winner(double *arr,PR1_DATA *w)// 반환값은 winner weight number
{
  double temp = 0.0;
  double min = 0.0;
  int winner;
  int set = w->get_column();

  min = divergence(arr,w->get_line(0));
  winner = 0;
  for(int y = 1 ; y < set ;y++)
  {
    temp = divergence(arr,w->get_line(y));
    if(temp < min)
    {
      min =temp;
      winner = y;
    }
  }
  weight_table(winner,1) =  weight_table(winner,1) + min;
  return winner;
}
int CNN_origin ::  calculate_winner_loser(double *arr,PR1_DATA *w,int winner, int loser)//반환값은 
{
  if(winner != loser)
  {
    weight_table(winner,2)++;
    for(int x = 0 ; x < data_dimension ; x++)
    {
      (*w)(winner,x) = (*w)(winner,x) + (arr[x] - (*w)(winner,x))/weight_table(winner,2);
    }
    if(loser != -1)
    {
      weight_table(loser,2)--;
      for(int x = 0 ; x < data_dimension ; x++)
      {
        (*w)(loser,x) = (*w)(loser,x) - (arr[x] - (*w)(loser,x))/weight_table(loser,2);
      }
    }
    return 1;
  }
  return 0;
}
int CNN_origin ::  cluster_inclease_method(int before)
{
  return  before + 1;
}


int CNN_origin ::  cluster_increase(int before, int after)
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
void CNN_origin ::  post_proccess()
{
  errors.init(epoch,6);
  for(int i = 0 ; i < epoch ; i++)
  {
    for(int j = 0 ; j < 6 ; j++)
    {
      errors(i,j) = t_errors(i,j);
    }
  }

  this->status(name);
}


void CNN_origin :: learning()
{
  this->first_init();
  this->second_init();


  while(1){
    int currunt_winner;
    int before_winner;

    iteration_set = this->pre_proccess(cur_cluster);
    do{
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
        trade = trade + this->calculate_winner_loser(input.get_line(y),&weight,currunt_winner,before_winner);
      }
      MSE = 0.0;
      for(int c = 0 ; c < cur_cluster ; c++) MSE = MSE + weight_table(c,1);

      t_errors(epoch-1,0) = epoch;
      t_errors(epoch-1,1) = MSE;
      t_errors(epoch-1,2) = cur_cluster;
      t_errors(epoch-1,3) = trade;
      t_errors(epoch-1,4) = iteration_set;

      if(trade < trade_standard && cur_cluster != cluster) break;
    }while(trade != 0);
    
    system("clear");
    cout<<"----- "<<name<<" -----"<<endl;
    cout<<"percent : "<<100*cur_cluster/cluster<<"%"<<endl;
    cout<<"cluster : "<<cur_cluster<<endl;
    cout<<"epoch : "<<epoch<<endl;
    cout<<"------------"<<endl;

    if(cluster == cur_cluster) break;

    before_cluster = cur_cluster;
    cur_cluster = this->cluster_inclease_method(before_cluster);
    
    this->cluster_increase(before_cluster, cur_cluster);
  }
  setting.init(4);
  setting(0) = epoch;
  setting(1) = MSE;
  setting(2) = cluster;
  //setting(3) = ;
  this->post_proccess();

  
}
void CNN_origin :: testing()
{

}


CNN_origin :: CNN_origin()
{
    epoch = 0;
    MSE = 0.0;
    cluster = 2;
    cur_cluster = 2;
    before_cluster = 0;
    trade = 0;
    trade_standard = 0;
    iteration_set = 0;
    data_dimension = 0;
    data_set = 0;
}

CNN_origin :: ~CNN_origin()
{

}
