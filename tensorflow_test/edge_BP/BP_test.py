import tensorflow as tf
import numpy as np
import cv2



x_ = tf.placeholder("float",[None,25])


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





z2 = tf.matmul(x_,W1) + b1
a2 = tf.nn.sigmoid(z2)

z3 = tf.matmul(a2,W2) + b2
a3 = tf.nn.sigmoid(z3)

z4 = tf.matmul(a3,W3) + b3
a4 = tf.nn.sigmoid(z4)
y_ = a4




sess = tf.Session()
sess.run(tf.global_variables_initializer())


img = cv2.imread("image/London.jpg",0)
edges = cv2.Canny(img,100,200)
dst = cv2.imread("image/London.jpg",0)


height, width =img.shape

mask = 2


for y in range(mask, height-mask):
    for x in range(mask,width - mask):
        ttt = []
        temp = []
        for yy in range(-1*mask,mask+1):
            for xx in range(-1*mask,mask+1):
                temp.append(img[y + yy][x + xx]/255.0)
        ttt.append(temp)

        r = sess.run(y_,feed_dict={x_ : ttt})
        dst[y][x] = r*255
cv2.imshow('origin',img)
cv2.imshow('canny',edges)
cv2.imshow('BP',dst)
cv2.waitKey(0)
cv2.destroyAllWindow()



