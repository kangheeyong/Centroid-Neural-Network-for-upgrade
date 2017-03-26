#ifndef __CNN_FOR_SPEED_UP_CPP__
#define __CNN_FOR_SPEED_UP_CPP__

#include "CNN_for_origin.h"

class CNN_RANDOM_INCREASE : public CNN_origin 
{
  private : 
  protected :
    void second_init();
 
    int pre_proccess(int cur_c);//원본데이터에서 실제 쓸데이터를 빼옴 반환값은 0부터 n번째까지 데이터

  public :



};
class CNN_SORT_INCREASE : public CNN_origin 
{
  private :
    PR1_DATA sort_table;    
  protected :
    void second_init();
 
    int pre_proccess(int cur_c);//원본데이터에서 실제 쓸데이터를 빼옴 반환값은 0부터 n번째까지 데이터

  public :



};

class CNN_FIBONACCI : public CNN_origin 
{
  private :
   int fibo_before; 
  protected :
   int cluster_inclease_method(int before);

  public :
   CNN_FIBONACCI();

};



#endif
