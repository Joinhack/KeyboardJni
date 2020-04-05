CC:=gcc
CFLAGS=-I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -fPIC
TARGET=libkeyboard.so

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(TARGET): keyboard.o
	$(CC) -shared -o $@ $<

all: libkeyboard.so

clean:
	rm $(TARGET) *.o
