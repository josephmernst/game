LIBS=-lglut -lGL -lGLU

default: graphics_test client

graphics_test:graphics_test.cc
	g++ $(LIBS) graphics_test.cc -o graphics_test

client:client.cc joystick/joystick.o
	g++ $(LIBS) client.cc joystick/joystick.o -o client -lpthread

joy_test:joystick/joystick.o
	g++ $(LIBS) joy_test.cc joystick/joystick.o -o joy_test -lpthread

joystick/joystick.o:joystick/joystick.cc joystick/joystick.h
	g++ $(LIBS) -c joystick/joystick.cc -o joystick/joystick.o
clean:
	-rm graphic_test client joystick/joystick.o