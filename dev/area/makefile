
CC=g++
AR=ar
DEPS=area.h ../main/interlecto.h ../main/interlecto.a
CFLAGS=-std=gnu++11 -fPIC -shared
OFLAGS=-std=gnu++11 -c
AFLAGS=rvs

all: area.so

area.so: area.cc $(DEPS)
	$(CC) -o $@ $< ../main/interlecto.a $(CFLAGS)

%.o: %.cc $(DEPS)
	$(CC) -o $@ $< $(OFLAGS)
