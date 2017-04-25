
FLAGS = -o

TARGET = main
OBJECTS = main.o MY_MLP.o My_Matrix.o

TARGET_TEST = test
OBJ_TEST = test.o MY_MLP.o My_Matrix.o

$(TARGET) : $(OBJECTS)
				$(CXX) $(FLAGS) $(TARGET) $(OBJECTS)

$(TARGET_TEST) : $(OBJ_TEST)
				$(CXX) -g $(FLAGS) $(TARGET_TEST) $(OBJ_TEST)


clean :
				rm *.o $(TARGET)

new :
				$(MAKE) clean
				$(MAKE)
