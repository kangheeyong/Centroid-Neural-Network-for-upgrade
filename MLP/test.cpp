#include <iostream>
#include "My_Matrix.hpp"
#include <time.h>
#include <stdlib.h>
#include "MY_MLP.hpp"


using namespace std;

int main()
{

  My_Matrix input, target;
  MLP a;

  input.init(4,2);

  input(0,0) = 0;
  input(0,1) = 0;
  input(1,0) = 0;
  input(1,1) = 1;
  input(2,0) = 1;
  input(2,1) = 0;
  input(3,0) = 1;
  input(3,1) = 1;

  target.init(4,1);
  
  target(0,0) = 1;
  target(1,0) = 0;
  target(2,0) = 0;
  target(3,0) = 1;


  a.add_layer(2);
  a.add_layer(5);
  a.add_layer(2);
  a.add_layer(1);

  a.network_connect();
  
  srand(1);
  a.init_gaussian(0, 1);

  a.batch_size(4);
  a.learning_gain(0.5);
  a.decay_para(0.000001);


  a.set_intput() = input;
  a.set_output() = target;
  for(int i = 0 ; i < 5000 ; i++)
  {
    a.activation();
    //a.check();
    cout<<a.get_cost_function()<<endl;

    a.back_propagation();
    // a.check();
  }
  a.check();

  return 0;
}
