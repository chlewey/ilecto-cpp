
CC=g++
AR=ar
DEPS=interlecto.h ilecto_web.h ilecto_html.h ilecto_xml.h ilecto_json.h ilecto_str.h config.h
OBJS=ilecto_web.o ilecto_html.o ilecto_xml.o ilecto_json.o ilecto_str.o config.o
CFLAGS=-std=gnu++11
OFLAGS=-std=gnu++11 -c
AFLAGS=rvs

all: index.cgi api.cgi test.cgi

index.cgi: ilecto.cc $(DEPS) interlecto.a
	$(CC) -o $@ $< interlecto.a $(CFLAGS)

api.cgi: ilecto_api.cc $(DEPS) interlecto.a
	$(CC) -o $@ $< interlecto.a $(CFLAGS)

test.cgi: ilecto_test.cc $(DEPS) interlecto.a
	$(CC) -o $@ $< interlecto.a $(CFLAGS)

interlecto.a: $(OBJS)
	$(AR) $(AFLAGS) $@ $(OBJS)

%.o: %.cc $(DEPS)
	$(CC) -o $@ $< $(OFLAGS)
