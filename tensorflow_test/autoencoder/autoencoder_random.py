import tensorflow as tf
import My_Mnist
import numpy as np
import os
import math
import sys
import new_activation as na


if len(sys.argv) != 2 :
    print("USAGE : ",sys.argv[0]," [file name]")
    sys.exit()

dname = sys.argv[1]
if os.path.exists(dname) != 1 :
    os.mkdir(dname)


data = My_Mnist.Mnist()
data.shuffle(1)


epoch = 500
mini_batch = 100


x = tf.placeholder("float", shape = [None, 784])
t = tf.placeholder("float", shape = [None, 784])


W1 = tf.Variable(tf.random_normal(shape = [784, 1000], mean = 0,stddev = 0.1))
b1 = tf.Variable(tf.random_normal(shape = [1000], mean = 0,stddev = 0.1))


W2 = tf.Variable(tf.random_normal(shape = [1000, 500], mean = 0,stddev = 0.1))
b2 = tf.Variable(tf.random_normal(shape = [500], mean = 0,stddev = 0.1))

W3 = tf.Variable(tf.random_normal(shape = [500, 250], mean = 0,stddev = 0.1))
b3 = tf.Variable(tf.random_normal(shape = [250], mean = 0,stddev = 0.1))


W4 = tf.Variable(tf.random_normal(shape = [250, 2], mean = 0,stddev = 0.1))
b4 = tf.Variable(tf.random_normal(shape = [2], mean = 0,stddev = 0.1))

W5 = tf.Variable(tf.random_normal(shape = [2, 250], mean = 0,stddev = 0.1))
b5 = tf.Variable(tf.random_normal(shape = [250], mean = 0,stddev = 0.1))


W6 = tf.Variable(tf.random_normal(shape = [250, 500], mean = 0,stddev = 0.1))
b6 = tf.Variable(tf.random_normal(shape = [500], mean = 0,stddev = 0.1))

W7 = tf.Variable(tf.random_normal(shape = [500, 1000], mean = 0,stddev = 0.1))
b7 = tf.Variable(tf.random_normal(shape = [1000], mean = 0,stddev = 0.1))


W8 = tf.Variable(tf.random_normal(shape = [1000, 784], mean = 0,stddev = 0.1))
b8 = tf.Variable(tf.random_normal(shape = [784], mean = 0,stddev = 0.1))



z2 = tf.matmul(x,W1) + b1
a2 = na.tf_new_activation(z2)

z3 = tf.matmul(a2,W2) + b2
a3 = na.tf_new_activation(z3)

z4 = tf.matmul(a3,W3) + b3
a4 = na.tf_new_activation(z4)

z5 = tf.matmul(a4,W4) + b4
a5 = na.tf_new_activation(z5)

z6 = tf.matmul(a5,W5) + b5
a6 = na.tf_new_activation(z6)

z7 = tf.matmul(a6,W6) + b6
a7 = na.tf_new_activation(z7)

z8 = tf.matmul(a7,W7) + b7
a8 = na.tf_new_activation(z8)

z9 = tf.matmul(a8,W8) + b8
a9 = tf.nn.sigmoid(z9)


y = a9

cost_function =tf.reduce_sum(tf.square(y - t)/mini_batch/784)



autoencoder = tf.train.GradientDescentOptimizer(0.1).minimize(cost_function)



sess = tf.Session()

#gpu_options = tf.GPUOptions(per_process_gpu_memory_fraction=0.2)

#sess = tf.Session(config=tf.ConfigProto(gpu_options=gpu_options))


sess.run(tf.global_variables_initializer())

error = []
print('--------------')
for i in range(epoch) :
    temp = 0.0
    for j in range(0, int(9000/mini_batch)):
        train, _ = data.train_next_batch(mini_batch)
        train = np.array(train)/255.0
    
        _, e = sess.run([autoencoder, cost_function],feed_dict={x : train, t : train})
        temp = temp + e

    print(i,temp/int(9000/mini_batch))
    error.append(temp/int(9000/mini_batch))


print('--------------')

weight1, bias1, weight2, bias2, weight3, bias3 = sess.run([W1,b1,W2,b2,W3,b3])

weight4, bias4, weight5, bias5, weight6, bias6 = sess.run([W4,b4,W5,b5,W6,b6])

weight7, bias7, weight8, bias8 = sess.run([W7,b7,W8,b8])




np.savetxt(fname=dname + "/W1.txt",X=weight1,fmt="%f")
np.savetxt(fname=dname + "/W2.txt",X=weight2,fmt="%f")
np.savetxt(fname=dname + "/W3.txt",X=weight3,fmt="%f")
np.savetxt(fname=dname + "/W4.txt",X=weight4,fmt="%f")
np.savetxt(fname=dname + "/W5.txt",X=weight5,fmt="%f")
np.savetxt(fname=dname + "/W6.txt",X=weight6,fmt="%f")
np.savetxt(fname=dname + "/W7.txt",X=weight7,fmt="%f")
np.savetxt(fname=dname + "/W8.txt",X=weight8,fmt="%f")

np.savetxt(fname=dname + "/b1.txt",X=bias1,fmt="%f")
np.savetxt(fname=dname + "/b2.txt",X=bias2,fmt="%f")
np.savetxt(fname=dname + "/b3.txt",X=bias3,fmt="%f")
np.savetxt(fname=dname + "/b4.txt",X=bias4,fmt="%f")
np.savetxt(fname=dname + "/b5.txt",X=bias5,fmt="%f")
np.savetxt(fname=dname + "/b6.txt",X=bias6,fmt="%f")
np.savetxt(fname=dname + "/b7.txt",X=bias7,fmt="%f")
np.savetxt(fname=dname + "/b8.txt",X=bias8,fmt="%f")



np.savetxt(fname=dname + "/error.txt",X=error,fmt="%f")



train, label = data.train_next_batch(9000)
train = np.array(train)/255.0
    
  
r = sess.run(a5,feed_dict={x : train})
  
temp = np.array([[0],[1],[2],[3],[4],[5],[6],[7],[8],[9]])

l = np.dot(label,temp)

np.savetxt(fname=dname + "/train_encoder.txt",X=r,fmt="%f")
np.savetxt(fname=dname + "/train_encoder_label.txt",X=l,fmt="%f")



test, label = data.test_next_batch(1000)
test = np.array(test)/255.0
 
r = sess.run(a5,feed_dict={x : test})
  
temp = np.array([[0],[1],[2],[3],[4],[5],[6],[7],[8],[9]])

l = np.dot(label,temp)

np.savetxt(fname=dname + "/test_encoder.txt",X=r,fmt="%f")
np.savetxt(fname=dname + "/test_encoder_label.txt",X=l,fmt="%f")


