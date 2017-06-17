import tensorflow as tf
import numpy as np
import os
import math
import sys




if len(sys.argv) != 3 :
    print("USAGE : ",sys.argv[0]," [in_len] [file name]")
    sys.exit()

dname = sys.argv[2]
epoch = 50

in_size = int(sys.argv[1])
start_n = 100
last_n = 1600
mini_batch = 1

if os.path.exists(dname) != 1 :
    os.mkdir(dname)


data = np.loadtxt(fname = "Sunspot_train.txt")
tdata = np.loadtxt(fname = "Sunspot_test.txt")






my_seed = 21


x = tf.placeholder("float",[None,in_size])
W1 = tf.Variable(tf.random_normal(shape = [in_size, in_size*2], mean = 0,stddev = 1,seed = my_seed))
b1 = tf.Variable(tf.random_normal(shape = [in_size*2], mean = 0,stddev = 1,seed = my_seed))


W2 = tf.Variable(tf.random_normal(shape = [in_size*2, in_size*2], mean = 0,stddev = 1,seed = my_seed))
b2 = tf.Variable(tf.random_normal(shape = [in_size*2], mean = 0,stddev = 1,seed = my_seed))

W3 = tf.Variable(tf.random_normal(shape = [in_size*2, in_size*2], mean = 0,stddev = 1,seed = my_seed))
b3 = tf.Variable(tf.random_normal(shape = [in_size*2], mean = 0,stddev = 1,seed = my_seed))


W4 = tf.Variable(tf.random_normal(shape = [in_size*2, 1], mean = 0,stddev = 1,seed = my_seed))
b4 = tf.Variable(tf.random_normal(shape = [1], mean = 0,stddev = 1,seed = my_seed))



z2 = tf.matmul(x,W1) + b1
a2 = tf.nn.sigmoid(z2)

z3 = tf.matmul(a2,W2) + b2
a3 = tf.nn.sigmoid(z3)

z4 = tf.matmul(a3,W3) + b3
a4 = tf.nn.sigmoid(z4)

z5 = tf.matmul(a4,W4) + b4
a5 = tf.nn.sigmoid(z5)
y = a5



t = tf.placeholder("float",[None,1])

cost_function =tf.reduce_sum(tf.square(y - t)/mini_batch)

BP = tf.train.GradientDescentOptimizer(0.4).minimize(cost_function)



sess = tf.Session()
sess.run(tf.global_variables_initializer())


error = []
prediction_error = []
print("--------------")
for i in range(1,epoch) :
    temp = 0.0
    for j in range(start_n,last_n) :

        in_data = [data[j-in_size:j]/400.0+0.1]
        in_target =[(data[j:j+1]/400.0+0.1 )]
        
        _ , e = sess.run([BP, cost_function],feed_dict={x : in_data, t :in_target})
        temp = temp + e
        
    error.append(math.sqrt(temp/((last_n-start_n)*in_size)))
    print(i," ",math.sqrt(temp/((last_n-start_n)*in_size)))

    pre_error = 0.0
    for i in range(start_n, start_n + 50) :
        t_data = [tdata[i-in_size:i]/400.0 + 0.1]
 
        r = sess.run(y,feed_dict={x : t_data})
    
        pre_error = pre_error + math.pow(r- (tdata[i:i+1]/400.0 + 0.1),2)    


    pre_error = math.sqrt(pre_error/50)


    prediction_error.append(pre_error)



print("--------------")


weight1, bias1, weight2, bias2, weight3, bias3,weight4, bias4 = sess.run([W1,b1,W2,b2,W3,b3,W4,b4])

np.savetxt(fname=dname + "/error.txt",X=error,fmt="%f")
np.savetxt(fname=dname + "/test_error.txt",X=prediction_error,fmt="%f")



np.savetxt(fname=dname +"/W1.txt",X=weight1,fmt="%f")
np.savetxt(fname=dname +"/W2.txt",X=weight2,fmt="%f")
np.savetxt(fname=dname +"/W3.txt",X=weight3,fmt="%f")
np.savetxt(fname=dname +"/W4.txt",X=weight4,fmt="%f")



np.savetxt(fname=dname +"/b1.txt",X=bias1,fmt="%f")
np.savetxt(fname=dname +"/b2.txt",X=bias2,fmt="%f")
np.savetxt(fname=dname +"/b3.txt",X=bias3,fmt="%f")
np.savetxt(fname=dname +"/b4.txt",X=bias4,fmt="%f")




result = []
pre_error = 0.0
for i in range(start_n, start_n + 50) :
    t_data = [tdata[i-in_size:i]/400.0 + 0.1]
 
    r = sess.run(y,feed_dict={x : t_data})
    
    pre_error = pre_error + math.pow(r- (tdata[i:i+1]/400.0 + 0.1),2)    
    result.append(r)
       

result_error = math.sqrt(pre_error/50)

print("predict error : ", result_error)
np.savetxt(fname=dname +"/result.txt",X=result,fmt="%f")














