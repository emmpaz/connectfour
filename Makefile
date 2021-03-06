OBJS	= connectfour.o
SOURCE	= connectfour.cpp
HEADER	= connect.h
OUT	= connectfour
CC	 = g++
FLAGS	 = -g -c -Wall --std=c++11
LFLAGS	 = -lncurses

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

connectfour.o: connectfour.cpp
	$(CC) $(FLAGS) connectfour.cpp 


clean:
	rm -f $(OBJS) $(OUT)
