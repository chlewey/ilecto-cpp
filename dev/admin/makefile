
CC=g++
AR=ar
DEPS=admin.h ../main/interlecto.h ../main/interlecto.a
CFLAGS=-std=gnu++11 -fPIC -shared
OFLAGS=-std=gnu++11 -c
AFLAGS=rvs

all: admin.so

admin.so: admin.cc $(DEPS)
	$(CC) -o $@ $< ../main/interlecto.a $(CFLAGS)

%.o: %.cc $(DEPS)
	$(CC) -o $@ $< $(OFLAGS)
