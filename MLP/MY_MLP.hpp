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
    int mini_batch;
  protected :
    nueral_layer *head;
    nueral_layer *tail;
    nueral_layer *cur;
    nueral_layer& prev() {return *(cur->prev);};
    nueral_layer& current() {return *cur;};
    nueral_layer& next() {return *(cur->next);};

    void Lfirst();
    void Llast();
    bool Lnext();
    bool Lprev();
    void Linsert();
    bool Ldelete(); 
    int get_total_layers() {return total_layers;};


  public :

    My_Matrix& set_intput() { return head->z; };
    //  virtual MLP set_output(int y, int x);
    void  check();
    void network_connect();
    
    //void mini_batch(int num);

    //  double get_cost_function()
    void  init_gaussian(double average, double stdev);
    //  virtual MLP learning_gain(double alpha);
    //  virtual MLP decay_para(double ramda)
    void add_layer(int nuerals);
    void del_layer(int index);
    void activation();

    //  virtual MLP back_propagation();

    MLP();
    ~MLP();

};

#endif
