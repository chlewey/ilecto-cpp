
CC=g++
AR=ar
DEPS=user.h ../main/interlecto.h ../main/interlecto.a
CFLAGS=-std=gnu++11 -fPIC -shared
OFLAGS=-std=gnu++11 -c
AFLAGS=rvs

all: user.so

user.so: user.cc $(DEPS)
	$(CC) -o $@ $< ../main/interlecto.a $(CFLAGS)

%.o: %.cc $(DEPS)
	$(CC) -o $@ $< $(OFLAGS)
