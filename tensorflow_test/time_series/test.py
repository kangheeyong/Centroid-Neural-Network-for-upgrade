

import numpy as np
import os


data = np.loadtxt(fname = "Sunspot_test.txt")

d = 100
start = 100
end = 150

result = []

for i in range(start,end) :
  #  result.append(data[i-d:i]/400.0 + 0.1)
 #   print(data[i-d:i+1]/500.0 + 0.1)
    result.append(data[i:i+1]/400.0 + 0.1)

np.savetxt(fname="origin_test.txt",X=result,fmt="%f")



