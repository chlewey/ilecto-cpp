
CC=g++
AR=ar
MODS=ilecto_web ilecto_html ilecto_xml ilecto_json ilecto_str ilecto_db ilecto_mysql config
DEPS=interlecto.h $(MODS:=.h)
OBJS=$(MODS:=.o)
CFLAGS=-std=gnu++11
OFLAGS=-std=gnu++11 -c
AFLAGS=rvs

all: index.cgi api.cgi test.cgi install.cgi try.cgi

index.cgi: ilecto.cc $(DEPS) interlecto.a
	$(CC) -o $@ $< interlecto.a $(CFLAGS)

api.cgi: ilecto_api.cc $(DEPS) interlecto.a
	$(CC) -o $@ $< interlecto.a $(CFLAGS)

test.cgi: ilecto_test.cc $(DEPS) interlecto.a
	$(CC) -o $@ $< interlecto.a $(CFLAGS)

install.cgi: ilecto_inst.cc $(DEPS) interlecto.a
	$(CC) -o $@ $< interlecto.a $(CFLAGS)

try.cgi: try.cc
	$(CC) -o $@ $< $(CFLAGS)

il: ilecto_il.h
	$(CC) -o il.o $< $(CFLAGS)

#ilecto_app.a: interlecto.a
#	ln -sf $< $@

#ilecto_ext.a: interlecto.a
#	ln -sf $< $@

interlecto.a: $(OBJS)
	$(AR) $(AFLAGS) $@ $(OBJS)

%.o: %.cc $(DEPS)
	$(CC) -o $@ $< $(OFLAGS)

clean:
	rm *.o *.a *.cgi
