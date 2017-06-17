#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "CNN_for_origin.h"

using namespace std;

int main(int argc, char **argv)
{
  if(argc != 4)
  {
    printf("Usage : %s [weight txt] [input text] [result]\n",argv[0]);
    return 0;
  }
  CNN_origin a;
  a.init("CNN continue");
  a.read_input(argv[2]);
  a.read_weight(argv[1]);
  a.learning_continue();
  a.write_all_data(argv[3]);


  return 0;
}
