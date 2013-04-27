#!/bin/bash

# Build .o files
g++ -g -Wall flyingObject.cc -c  
g++ -g -Wall functions/geometry.cc -c -o functions/geometry.o


# Build executables
g++ -g -Wall -lglut -lGL -lGLU -lglfw -lpthread flyingObject.o functions/geometry.o graphics_test.cc -o graphics_test

g++ -g -Wall -lglut -lGL -lGLU -lglfw -lpthread flyingObject.o functions/geometry.o client.cc -o client

g++ -g -Wall -lglut -lGL -lGLU -lglfw -lpthread flyingObject.o functions/geometry.o functions/test.cc -o functions/test
g++ -g -Wall -lglut -lGL -lGLU -lglfw -lpthread flyingObject.o functions/geometry.o test.cc -o test