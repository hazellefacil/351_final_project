OBJS    = accel.o 
SOURCE    = accel.c
HEADER    = accel.o

OUTDIR = $(HOME)/cmpt433/public/myApps
CROSS_TOOL = arm-linux-gnueabihf-
CC_CPP = $(CROSS_TOOL)g++
CC = $(CROSS_TOOL)gcc
FLAGS = -Wall -g -c -D _POSIX_C_SOURCE=200809L -Werror -pthread 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)  accel -lm


clean:
	find . -type f | xargs touch
	rm -f $(OBJS) $(OUT)