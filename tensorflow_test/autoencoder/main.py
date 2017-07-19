#from tensorflow.examples.tutorials.mnist import input_data
#mnist = input_data.read_data_sets("MNIST_data", one_hot=True)
import numpy as np

#print(np.array(mnist.test.images).tolist())

import My_Mnist

a = My_Mnist.Mnist();
#a.shuffle(1)
b,c = a.test_next_batch(10)
print(np.array(b)/255.0)

a.show_image(95)

