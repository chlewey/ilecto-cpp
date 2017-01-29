
CC=g++
AR=ar
DEPS=area.h interlecto.h interlecto.a
OBJS=ilecto_html.o ilecto_main.o utils.o
CFLAGS=-std=gnu++11 -fPIC -shared
OFLAGS=-std=gnu++11 -c
AFLAGS=rvs

all: area.so

%.so: %.cc $(DEPS)
	$(CC) -o $@ $< interlecto.a $(CFLAGS)

%.o: %.cc $(DEPS)
	$(CC) -o $@ $< $(OFLAGS)
