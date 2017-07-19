import math
import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt

from tensorflow.python.framework import ops

def new_activation(x) :
    if x > 0 :
        r = math.log(x + 1)
    else :
        r = -math.log(1 - x)
    return r

def d_new_activation(x) :
    if x > 0 :
        r = 1/(x + 1)
    else :
        r = 1/(1 - x)
    return r


np_new_activation = np.vectorize(new_activation)    
np_d_new_activation = np.vectorize(d_new_activation)


np_d_new_activation_32 = lambda x : np_d_new_activation(x).astype(np.float32)

def tf_d_new_activation(x,name=None) :
    with ops.op_scope([x], name, "d_new_activation") as name :
        y = tf.py_func(np_d_new_activation_32,
                        [x],
                        [tf.float32],
                        name = name,
                        stateful = False)
        return y[0]


def py_func(func, inp, Tout, stateful = True, name = None, grad = None) :
    
    rnd_name = 'PyFuncGrad' + str(np.random.randint(0,1E+8))
    
    tf.RegisterGradient(rnd_name)(grad)
    g = tf.get_default_graph()
    with g.gradient_override_map({"PyFunc" : rnd_name}) :
        return tf.py_func(func,inp, Tout, stateful = stateful, name=name)


def new_activationgrad(op,grad) :
    x = op.inputs[0]

    n_gr = tf_d_new_activation(x)
    return grad * n_gr

np_new_activation_32 = lambda x : np_new_activation(x).astype(np.float32)

def tf_new_activation(x,name=None) :
    with ops.op_scope([x], name, "new_activation") as name :
        y = py_func(np_new_activation_32,
                        [x],
                        [tf.float32],
                        name = name,
                        grad = new_activationgrad)
        return y[0]


if __name__ == "__main__" :
    print("new_activation.py")
    
    x = np.arange(-5,5,0.01)
    
    y = np_new_activation(x)
    y1 = np_d_new_activation(x)
    
    plt.figure(1)
    plt.plot(x,y)
    
    plt.figure(2)
    plt.plot(x,y1)
    
    #plt.show()


    with tf.Session() as sess :
        x = tf.constant([-0.2, 0.7, 1.2, 1.7])
        y = tf_new_activation(x)
    
        tf.global_variables_initializer().run()


        print(x.eval(),y.eval(),tf.gradients(y,[x])[0].eval())

    plt.show()
