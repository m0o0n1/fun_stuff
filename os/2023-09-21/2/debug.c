#include <stdio.h>

#ifndef MY_NAME
#define MY_NAME "World"
#endif

#ifdef DEBUG_MODE
#define DEBUG(msg) fprintf(stderr, "[%s:%d] %s: %s\n",\
		__FILE__, __LINE__, __func__, (msg));
#else
#define DEBUG(msg)
#endif

int function(char *name){
	DEBUG("START");
	printf("Hello, %s\n", name);
	DEBUG("END");
}

int main(int argc, char**argv){
	DEBUG("START");
	function(MY_NAME);
	DEBUG("END");
	return 0;
}	
