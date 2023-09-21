#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char**argv){
	void* handle;
	void (*pprint)(char);

	handle = dlopen("./libpprint.so", RTLD_LAZY);
	if( NULL == handle){ print("ERR"); return -1; }
	
	pprint = (void (*)(char*))dlsym(handle, pprint);
	if (NULL != pprint){ pprint("adawdadw\n");}
	else { printf("err\n"); return -2; }
	dlclose(handle);

	return (NULL == pprint) ? -1 : 0;
}
