import tensorflow as tf
import numpy as np





#input_data = np.array([[0,0],[0,1],[1,0],[1,1]])
#output_data = np.array([[1],[0],[0],[1]])
input_data = [[0,0],[0,1],[1,0],[1,1]]
output_data = [[1],[0],[0],[1]]
mini_batch = 4

my_seed = 1


x = tf.placeholder("float",[None,2])
W1 = tf.Variable(tf.random_normal(shape = [2, 3], mean = 0,stddev = 1,seed = my_seed))
b1 = tf.Variable(tf.random_normal(shape = [3], mean = 0,stddev = 1,seed = my_seed))


W2 = tf.Variable(tf.random_normal(shape = [3, 2], mean = 0,stddev = 1,seed = my_seed))
b2 = tf.Variable(tf.random_normal(shape = [2], mean = 0,stddev = 1,seed = my_seed))

W3 = tf.Variable(tf.random_normal(shape = [2, 1], mean = 0,stddev = 1,seed = my_seed))
b3 = tf.Variable(tf.random_normal(shape = [1], mean = 0,stddev = 1,seed = my_seed))



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



print(sess.run([W1,b1,W2,b2,W3,b3]))
print('--------------')
for i in range(5000) :
    _ , e = sess.run([BP, cost_function],feed_dict={x : input_data, t : output_data})

    print(e)
print('--------------')
print(sess.run(y,feed_dict={x : input_data}))
print(sess.run([W1,b1,W2,b2,W3,b3]))


weight1, bias1, weight2, bias2, weight3, bias3 = sess.run([W1,b1,W2,b2,W3,b3])


np.savetxt(fname="W1.txt",X=weight1,fmt="%f")
np.savetxt(fname="W2.txt",X=weight2,fmt="%f")
np.savetxt(fname="W3.txt",X=weight3,fmt="%f")
np.savetxt(fname="b1.txt",X=bias1,fmt="%f")
np.savetxt(fname="b2.txt",X=bias2,fmt="%f")
np.savetxt(fname="b3.txt",X=bias3,fmt="%f")















