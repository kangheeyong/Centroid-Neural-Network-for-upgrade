#include <iostream>
#include "My_Matrix.hpp"
#include <time.h>
#include <stdlib.h>



using namespace std;

int main()
{
  cout<<"hello world"<<endl;


  srand(4);

  My_Matrix a,b,c,d,temp;

  a.init(3,4);
  a.gaussian(0,0.1);
  a.print();

  a.vector(MY_ALL,0).transpose().print();

  a.vector(MY_ALL,1).print();

  b = a.vector(MY_ALL,1) * a.vector(MY_ALL,0).transpose() ;
  b.print();


  return 0;
}
