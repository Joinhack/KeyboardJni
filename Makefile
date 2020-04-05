
CC:=gcc
CFLAGS=-I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux

%.o: %.c
	$(CC) $(CFLAGS) -c $<

libkeyboard.so: keyboard.o
	$(CC) -shared -o $@ $<

all: libkeyboard.so
