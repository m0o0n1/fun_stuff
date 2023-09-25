CC=gcc
LDFLAGS:=-fPIC
NAME=prog
TYPE=

help: 
	@echo "This module can be compiled with the keys <noshared> and <build>"
	@echo "The main difference between them is that the first one will search all the files and subdirs in current directory to find an .so file and load it at runtime"
	@echo "The <build> option will build it in one directory and link at compilation time xd"
	@echo "The usage of program: ./prog.exe"
	@echo "The input you need to store in s variable"
	@echo "make <[build | noshared | help]>"

build: $(NAME).o libpushkin.so
	$(CC) -o $(NAME).exe $(NAME).o -L. -lpushkin -Wl,-rpath,'.'

# SO THIS COMPILES A LIBRARY
libpushkin.so: pushkin.o
	$(CC) -shared -o libpushkin.so pushkin.o

# COMPILE ALL THE *.c FILES ага
%.o:%.c
	$(CC) $(LDFLAGS) $(TYPE) -c $< -o $@

# JUST RUN THIS BRO
run: $(NAME).exe
	./$(NAME).exe

# IF COMPILE WITHOUT LINKING TO SHARED LIBRARY SET THE PREPROCESSOR FLAG
noshared: TYPE = -DNOSHARED
noshared: $(NAME).o
	$(CC) -o $(NAME).exe $(NAME).o $(TYPE)

# CLEAN GARBAGE BUT
clean:
	rm -vf *.o *.~
