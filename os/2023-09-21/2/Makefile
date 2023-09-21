CC=gcc


all: main.exe
	@echo "Usage:"
	@echo "main - just a program"
	@echo "myname - program with key"
main: main.c
	$(CC) main.c

myname: main.c
	$(CC) -DMY_NAME="\"Student\"" main.c
nodebug: debug.c
	$(CC) debug.c
debug: debug.c
	$(CC) -DDEBUG_MODE debug.c

hack:
	$(CC) -DMY_NAME="({char *msg; fprintf(stderr, \"hacked\\n\");msg=\"World\";})" main.c


clean:
	rm -vf *.o *.~ a.out
