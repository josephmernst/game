LIBS=-lglut -lGL -lGLU -lglfw -lpthread
CFLAGS=-g -Wall
APPS=graphics_test client joy_test functions/test test
OBJS=joystick/joystick.o flyingObject.o
default: $(APPS)

test:test.cc $(OBJS)
	g++ $(CFLAGS) $(LIBS) $(OBJS) test.cc -o test

graphics_test:graphics_test.cc $(OBJS)
	g++ $(CFLAGS) $(LIBS) $(OBJS) graphics_test.cc -o graphics_test

client:client.cc $(OBJS)
	g++ $(CFLAGS) $(LIBS) $(OBJS) client.cc -o client

joy_test:$(OBJS)
	g++ $(CFLAGS) $(LIBS) $(OBJS) joy_test.cc  -o joy_test -lpthread


joystick/%.o:joystick/%.cc joystick/%.h
	g++ $(CFLAGS) $< -c -o $@
functions/%.o:functions/%.cc functions/%.h
%.o:%.cc %.h
	g++ $(CFLAGS) $< -c  
functions/test: functions/test.cc $(OBJS)
	g++ $(CFLAGS) $(LIBS) $(OBJS) functions/test.cc -o functions/test
clean:
	-rm $(APPS) $(OBJS)