import cv2
import numpy as np
import random
import matplotlib.pyplot as plt


class Mnist :
    data_train = []
    data_test = []
    label_train = []
    label_test = []

    train_point = 0 
    test_point = 0
    def __init__(self) :
        print("init")
        self.read()

    def __del__(self) :
        print("del")
    
    def read(self) :    
        self.data_train =  np.array(np.loadtxt(fname = "MY_MNIST/MNIST_data_train.txt",dtype="int32")).tolist()    
        self.data_test =  np.array(np.loadtxt(fname = "MY_MNIST/MNIST_data_test.txt",dtype="int32")).tolist()    
        self.label_train =  np.array(np.loadtxt(fname = "MY_MNIST/MNIST_label_train.txt",dtype="int32")).tolist()    
        self.label_test =  np.array(np.loadtxt(fname = "MY_MNIST/MNIST_label_test.txt",dtype="int32")).tolist()    

        print("read sueccess")
    
    def shuffle(self,seed) :
        R = random.Random(seed)
        R.shuffle(self.data_train)
        
        R.seed(seed)
        R.shuffle(self.data_test)

        R.seed(seed)
        R.shuffle(self.label_train)

        R.seed(seed)
        R.shuffle(self.label_test)
    
    def train_next_batch(self, size) :
        
        a = self.train_point

        train = []
        label = []

        self.train_point = self.train_point + size
        if self.train_point > 9000 :
            self.train_point = self.train_point- 9000 
            a = self.train_point - size
            for i in range(a, 0) :
                train.append(self.data_train[i][:])
                label.append(self.label_train[i][:]) 
 
            for i in range(0,self.train_point) :
                train.append(self.data_train[i][:])
                label.append(self.label_train[i][:])
        else :
            train = self.data_train[a : a + size][:]
            label = self.label_train[a : a + size][:]

        return train, label       
     
    def test_next_batch(self, size) :
        
        a = self.test_point

        train = []
        label = []

        self.test_point = self.test_point + size
        if self.test_point > 1000 :
            self.test_point = self.test_point- 1000 
            a = self.test_point - size
            for i in range(a, 0) :
                train.append(self.data_test[i][:])
                label.append(self.label_test[i][:]) 
 
            for i in range(0,self.test_point) :
                train.append(self.data_test[i][:])
                label.append(self.label_test[i][:])
        else :
            train = self.data_test[a : a + size][:]
            label = self.label_test[a : a + size][:]

        return train, label       
        
    def show_image(self,num) :
        
        f, a = plt.subplots(10)
        for i in range(0,10) :

            a[i].imshow(np.reshape(np.array(self.data_test[num+i][:]),(28,28)))
             
            print(self.label_test[num+i][:])
         
        
        f.show()
        
        
        plt.waitforbuttonpress()

def mk_img_to_txt() :
    data = []
    for i in range(0,10000) :
        fname = "MNIST/" + str(i) +".bmp"

        img = cv2.imread(fname,0)
    

        temp = []
        for y in range(0,28) :
            for x in range(0,28) :
                temp.append(img[y][x])
        data.append(temp)
    
    np.savetxt(fname="MNIST.txt",X=data,fmt="%d")

def mk_train_test_data() :
    
    data = np.loadtxt(fname = "MNIST.txt",dtype="int32")    
    
    data_train = []
    data_test = []
    label_train = []
    label_test = []
    

    for label in range(0, 10) : 
        t = [0,0,0,0,0,0,0,0,0,0]

        t[label] = t[label] + 1
 
        for i in range(0,900) :
            data_train.append(data[1000*label + i ][:])
            label_train.append(t)
        for i in range(0,100) :
            data_test.append(data[1000*label + 900 + i ][:])
            label_test.append(t)
   
    np.savetxt(fname="MNIST_label_train.txt",X=label_train,fmt="%d")
    np.savetxt(fname="MNIST_label_test.txt",X=label_test,fmt="%d")
    np.savetxt(fname="MNIST_data_train.txt",X=data_train,fmt="%d")
    np.savetxt(fname="MNIST_data_test.txt",X=data_test,fmt="%d")
    
    pass


if __name__ == "__main__" :
    print("My_Mnist")

   
    #cv2.imshow('origin',img)
    #cv2.waitKey(0)
    #cv2.destroyAllWindow()





