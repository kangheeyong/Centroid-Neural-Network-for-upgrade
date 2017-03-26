#include <stdio.h>
#include <iostream>
#include "CNN_for_origin.h"

using namespace std;

int main(int argc, char **argv)
{
  CNN_origin a;
  a.init("CNN");
  a.read_input("input/20by20data.txt");
  a.read_setting(16);
  a.learning();
  a.write_all_data("temp");

  return 0;
}
