#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "CNN_for_origin.h"

using namespace std;

int main(int argc, char **argv)
{
  if(argc != 4)
  {
    printf("Usage : %s [cluster number] [input text] [result]\n",argv[0]);
    return 0;
  }
  CNN_origin a;
  a.init("CNN");
  a.read_input(argv[2]);
  a.read_setting(atoi(argv[1]));
  a.learning();
  a.write_all_data(argv[3]);


  return 0;
}
