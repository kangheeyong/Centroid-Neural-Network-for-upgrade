#include <stdio.h>
#include <iostream>
#include "My_Types.h"
#include "CNN_for_origin.h"

using namespace std;

int main(int argc, char **argv)
{
  cout<<"hello world"<<endl;
  CNN_origin a;

  a.read_input("input/basic_data.txt");
  a.read_setting(4);
  a.learning();


  return 0;
}
