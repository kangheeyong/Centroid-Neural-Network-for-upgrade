import tensorflow as tf
import numpy as np


input_data = np.loadtxt(fname = "London_5by5_input.txt")
output_data = np.loadtxt(fname = "London_5by5_target.txt")
output_data.shape = (283696,1)


mini_batch = 100

my_seed = 1


x = tf.placeholder("float",[None,25])


temp = np.loadtxt(fname = "W1.txt")
temp.shape = (25,100)
W1 = tf.Variable(temp, name= "W1",dtype = "float")
temp = np.loadtxt(fname = "b1.txt")
temp.shape = (100)
b1 = tf.Variable(temp, name= "b1",dtype = "float")

temp = np.loadtxt(fname = "W2.txt")
temp.shape = (100,50)
W2 = tf.Variable(temp, name= "W2",dtype = "float")
temp = np.loadtxt(fname = "b2.txt")
temp.shape = (50)
b2 = tf.Variable(temp, name= "b2",dtype = "float")

temp = np.loadtxt(fname = "W3.txt")
temp.shape = (50,1)
W3 = tf.Variable(temp, name= "W3",dtype = "float")
temp = np.loadtxt(fname = "b3.txt")
temp.shape = (1)
b3 = tf.Variable(temp, name= "b3",dtype = "float")



z2 = tf.matmul(x,W1) + b1
a2 = tf.nn.sigmoid(z2)

z3 = tf.matmul(a2,W2) + b2
a3 = tf.nn.sigmoid(z3)

z4 = tf.matmul(a3,W3) + b3
a4 = tf.nn.sigmoid(z4)
y = a4


t = tf.placeholder("float",[None,1])

cost_function =tf.reduce_sum(tf.square(y - t)/mini_batch)

BP = tf.train.GradientDescentOptimizer(0.4).minimize(cost_function)



sess = tf.Session()
sess.run(tf.global_variables_initializer())



error = []
print('--------------')
for i in range(100) :
    temp = 0.0
    for j in range(0, int(283696/mini_batch)):
        _ , e = sess.run([BP, cost_function],feed_dict={x : input_data[j:j+mini_batch], t : output_data[j:j+mini_batch]})
        temp = temp + e
    print(i,temp/int(283696/mini_batch))
    error.append(temp/int(283696/mini_batch))
print('--------------')


weight1, bias1, weight2, bias2, weight3, bias3 = sess.run([W1,b1,W2,b2,W3,b3])


np.savetxt(fname="W1.txt",X=weight1,fmt="%f")
np.savetxt(fname="W2.txt",X=weight2,fmt="%f")
np.savetxt(fname="W3.txt",X=weight3,fmt="%f")
np.savetxt(fname="b1.txt",X=bias1,fmt="%f")
np.savetxt(fname="b2.txt",X=bias2,fmt="%f")
np.savetxt(fname="b3.txt",X=bias3,fmt="%f")















