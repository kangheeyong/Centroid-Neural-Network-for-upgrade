#ifndef __CNN_FOR_ORIGIN_CPP__
#define __CNN_FOR_ORIGIN_CPP__

#define MAX_EPOCH       50000


#include "My_Types.h"


class CNN_origin
{
  private :
    PR1_DATA t_errors;
    char name[100];
  protected :

    PR1_DATA origin; 
    PR1_DATA input;
    PR1_DATA result;

    PR1_DATA center;
    PR1_DATA weight;
    PR1_DATA weight_table; //weight num, SSE, n;
    PR1_DATA table; //어떤 기준, index, cluster 
    PR1_QUEUE q_weight; 
    PR1_QUEUE q_weight_table;

    PR1_DATA errors; //epoch마다 MSE, trade, cluster num, 1-interation data , 1-iteration time
    PR1_DATA setting;
    
    int epoch;
    double MSE;
    int cluster;
    int cur_cluster;
    int before_cluster;

    int trade;
    int trade_standard; // 루저 기준
    int iteration_set;
    int data_dimension;
    int data_set;

    virtual void first_init(); //전체 평균 구하기
    virtual void second_init();
    virtual double divergence(double *arr_in, double *arr_w); //error 계산 함수
    virtual int pre_proccess(int cur_c);//원본데이터에서 실제 쓸데이터를 빼옴 반환값은 0부터 n번째까지 데이터
    int search_winner(double *arr,PR1_DATA *w);// 반환값은 winner weight number
    int calculate_winner_loser(double *arr,PR1_DATA *w,int winner, int loser);//반환값은 
    
    int cluster_increase(int before, int after);
    virtual int cluster_inclease_method(int before);
    
    virtual void post_proccess();

  public :
    void init(const char *name);
    void read_input(const char* fname);
    void read_weight(const char *fname);
    void read_setting(int cluster);

    void status(char *name);

    void write_all_data(const char* fname);
    void write_weight(const char* fname);
    void write_result(const char *fname);
    void write_errors(const char *fname);
    void write_setting(const char *fname);

    void learning();
    void testing();

    CNN_origin();
    ~CNN_origin();
};


#endif
