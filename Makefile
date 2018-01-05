
EXENAME=stratego

CC=g++
CXXFLAGS=-ggdb -Wall -ansi -pedantic $(shell sdl-config --cflags)
LFLAGS=-lm $(shell sdl-config --libs) -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_net

SRCS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,%.o,$(SRCS))
DEPS:=$(patsubst %.cpp,%.d,$(SRCS))

$(EXENAME): $(DEPS) $(OBJS)
	$(CC) $(CXXFLAGS) -o $(EXENAME) $(OBJS) $(LFLAGS)

%.d: %.cpp
	$(CC) $(CXXFLAGS) -M $< > $@

#%.o: %.c 
#	$(CC) $(CFLAGS) -c -o $@ $<

#main.o: main.c common.h mystring.h process_room.h story_util.h
#	$(CC) $(CFLAGS) -c -o main.o main.c

clean:
	rm $(OBJS) $(DEPS)



-include $(DEPS)
