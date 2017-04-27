#ifndef __MY_MLP_CPP__
#define __MY_MLP_CPP__

#include "My_Matrix.hpp"


class nueral_layer{
  
  private :
  
  protected :
  
  public :
    My_Matrix w, b;
    My_Matrix z, a;
    My_Matrix delta;

    int index;
    int nuerals;
    int type;

    nueral_layer *next;
    nueral_layer *prev;
    
    nueral_layer();
    ~nueral_layer();
};


class MLP{
  private :

    int total_layers; 
   
  protected :
    double alpha; // learning_gain
    double ramda; // decay_para
    int mini_batch;

    nueral_layer *head;
    nueral_layer *tail;
    nueral_layer *cur;
    nueral_layer& prev() {return *(cur->prev);};
    nueral_layer& current() {return *cur;};
    nueral_layer& next() {return *(cur->next);};

    My_Matrix y;
    double W;

    void Lfirst();
    void Llast();
    bool Lnext();
    bool Lprev();
    void Linsert();
    bool Ldelete(); 
    int get_total_layers() {return total_layers;};


  public :

    My_Matrix& set_intput() { return head->z; };
    My_Matrix& set_output() { return y; };
    void  check();
    void network_connect();
    
    void batch_size(int num) { mini_batch = num; };

    double get_cost_function();
    void init_gaussian(double average, double stdev);
    void learning_gain(double alpha) {this->alpha = alpha; };
    void decay_para(double ramda) { this->ramda = ramda; };
    void add_layer(int nuerals);
    void del_layer(int index);
    void activation();
    void back_propagation();

    MLP();
    ~MLP();

};

#endif
