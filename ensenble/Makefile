
FLAGS = -O2 -o

TARGET = main
OBJECTS = main.o My_Types.o CNN_for_origin.o CNN_for_speed_up.o 

TARGET_STUDY = study
OBJ_STUDY = study.o My_Types.o CNN_for_origin.o





$(TARGET) : $(OBJECTS)
				$(CXX) $(FLAGS) $(TARGET) $(OBJECTS) -lpthread

$(TARGET_STUDY) : $(OBJ_STUDY)
				$(CXX) -g $(FLAGS) $(TARGET_STUDY) $(OBJ_STUDY) -lpthread



clean :
				rm *.o $(TARGET)

new :
				$(MAKE) clean
				$(MAKE)
