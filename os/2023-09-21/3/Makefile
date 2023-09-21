PROGS = simple.exe static.exe shared.exe load.exe

help:
	@echo "usage"

all: $(PROGS)

simple.exe: main.o pprint.o
	gcc -o simple.exe main.o pprint.o

static.exe: main.o libpprint.a
	gcc -o static.exe main.o -static -L. -lpprint

libpprint.a: pprint.o
	ar cr libpprint.a pprint.o

shared.exe: main.o libpprint.so
	gcc -o shared.exe main.o -L. -lpprint -Wl,-rpath,'.'

libpprint.so: pprint.o
	gcc -o -fPIC libpprint.so pprint.o -shared

load.exe: load.o
	gcc -o load.exe lod.o -ldl

%.o:%.c
	gcc -c $< -o $@

clean:
	rm -vf *.0 *.so *.a *.exe *~
