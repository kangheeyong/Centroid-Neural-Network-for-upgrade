import numpy as np
import tensorflow as tf


#import theano
#import scipy.io as sio

#mat_data = sio.loadmat('matlab_data.mat')

#print('mat_data : \n',mat_data)


temp = np.array([[1.01,-1,1],[-1,1,-1]])

print(temp)

np.savetxt(fname="aaaa.txt",X=temp,fmt="%f")

bbb = np.loadtxt(fname = "edge_BP/London_5by5_input.txt")




print("-----")
print(bbb[0:5])
print("-----")


W2 = tf.Variable(bbb, name= "aasd",dtype = "float")

print(W2)
W1 = tf.Variable(tf.random_normal(shape = [2, 3], mean = 0,stddev = 1,seed = 1))
print(W1)

sess = tf.Session()
sess.run(tf.global_variables_initializer())

xxx = sess.run(W2)


np.savetxt(fname="xxxx.txt",X=xxx,fmt="%f")





