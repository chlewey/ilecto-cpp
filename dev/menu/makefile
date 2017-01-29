
CC=g++
AR=ar
DEPS=menu.h ../main/interlecto.h ../main/interlecto.a
CFLAGS=-std=gnu++11 -fPIC -shared
OFLAGS=-std=gnu++11 -c
AFLAGS=rvs

all: menu.so

menu.so: menu.cc $(DEPS)
	$(CC) -o $@ $< ../main/interlecto.a $(CFLAGS)

%.o: %.cc $(DEPS)
	$(CC) -o $@ $< $(OFLAGS)
