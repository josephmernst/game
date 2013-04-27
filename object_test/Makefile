default:object_test
CC=g++
OBJS=Object.o main.o MainWindow.o Global.o Pyramid.o 
LIBS=-lglut -lGL -lGLU
CFLAGS=-g -Wall
object_test:$(OBJS) 
	$(CC) $(CFLAGS) -o object_test $(OBJS) $(LIBS)

%.o:%.cpp %.h
	$(CC) $(CFLAGS) $< -o $@ -c  

clean:
	-rm *.o object_test
