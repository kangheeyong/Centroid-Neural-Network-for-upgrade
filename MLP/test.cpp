#include <iostream>
#include "My_Matrix.hpp"
#include <time.h>
#include <stdlib.h>
#include "MY_MLP.hpp"


using namespace std;

int main()
{
  My_Matrix input;
  srand(1);
  cout<<"hello world"<<endl;
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

  a.add_layer(2);
  a.add_layer(5);
  a.add_layer(2);
  a.add_layer(1);

  a.network_connect();
  a.init_gaussian(0, 0.1);
  
  a.set_intput() = input;
  
  a.activation();
  a.check();


  cout<<endl;




  return 0;
}
