
FLAGS = -o

TARGET = main
OBJECTS = main.o My_Types.o CNN_for_origin.o CNN_for_speed_up.o

TARGET_STUDY = study
OBJ_STUDY = study.o My_Types.o CNN_for_origin.o

TARGET_RAND = CNN_for_speed_random
OBJ_RAND = rand.o My_Types.o CNN_for_origin.o CNN_for_speed_up.o

TARGET_SORT = CNN_for_speed_sort
OBJ_SORT = sort.o My_Types.o CNN_for_origin.o CNN_for_speed_up.o

TARGET_FIBO = CNN_for_speed_fibonacci
OBJ_FIBO = fibo.o My_Types.o CNN_for_origin.o CNN_for_speed_up.o



$(TARGET) : $(OBJECTS)
				$(CXX) $(FLAGS) $(TARGET) $(OBJECTS)

$(TARGET_STUDY) : $(OBJ_STUDY)
				$(CXX) -g $(FLAGS) $(TARGET_STUDY) $(OBJ_STUDY)

$(TARGET_RAND) : $(OBJ_RAND)
				$(CXX) -g $(FLAGS) $(TARGET_RAND) $(OBJ_RAND)

$(TARGET_SORT) : $(OBJ_SORT)
				$(CXX) -g $(FLAGS) $(TARGET_SORT) $(OBJ_SORT)

$(TARGET_FIBO) : $(OBJ_FIBO)
				$(CXX) -g $(FLAGS) $(TARGET_FIBO) $(OBJ_FIBO)





clean :
				rm *.o $(TARGET)

new :
				$(MAKE) clean
				$(MAKE)
