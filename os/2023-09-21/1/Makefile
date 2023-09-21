CC=gcc
CFLAGS:=-Wall
LDFLAGS=
LD=$(CC)

PYTHON:=$(shell which python)

all: main.exe

echo:
	echo "${PYTHON}"

noecho:
	@echo "${PYTHON}"

main.exe: main.o
	@echo "[LD] $@"
	@$(LD) -o main.exe main.o $(LDFLAGS)

%.0:%.c
	@echo "[CC] $@"
	@$(CC) $(CFLAGS) -c $< -o $@

python: main.py
	@echo "[EXE] python script"
	@$(PYTHON) main.py

clean:
	@echo "Clean directory"
	@rm -vf *.o *.exe *~
