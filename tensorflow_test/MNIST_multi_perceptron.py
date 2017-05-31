from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_data_sets("MNIST_data/",one_hot=True)


import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import tensorflow as tf


print(tf.convert_to_tensor(mnist.train.images).get_shape())


x = tf.placeholder("float",[None,784])
W1 = tf.Variable(tf.zeros([784, 144]))
b1 = tf.Variable(tf.zeros([144]))


W2 = tf.Variable(tf.zeros([144, 10]))
b2 = tf.Variable(tf.zeros([10]))


#y = tf.nn.softmax(tf.matmul(x,W)+b)
S1 = tf.matmul(x,W1) + b1
U2 = tf.nn.sigmoid(S1)


y = tf.nn.sigmoid(tf.matmul(U2,W2) + b2)
y_ = tf.placeholder("float",[None,10])

#cross_entroy = -tf.reduce_sum(y_*tf.log(y))
euclid = tf.reduce_sum(tf.square(y - y_))
#train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entroy)
train_step = tf.train.GradientDescentOptimizer(0.01).minimize(euclid)



#sess = tf.Session(config = tf.ConfigProto(log_device_placement=True))
sess = tf.Session()
sess.run(tf.global_variables_initializer())

for i in range(20000) :
    batch_xs, batch_ys = mnist.train.next_batch(100)
    sess.run(train_step,feed_dict={x : batch_xs, y_ : batch_ys})
    if i % 500 == 0:
        print(i)

   

correct_prediction = tf.equal(tf.argmax(y,1),tf.argmax(y_,1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction,"float"))
print(sess.run(accuracy,feed_dict={x:mnist.test.images,y_:mnist.test.labels}))
#print(tf.convert_to_tensor(mnist.test.images).get_shape())



