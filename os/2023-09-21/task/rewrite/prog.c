#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef NOSHARED
	#include <errno.h>
	#include <dirent.h>
	#include <dlfcn.h>
	#include <sys/stat.h>
	#include <string.h>
#endif


#ifndef NOSHARED
	char *pushkin(char *);
#endif


#ifdef NOSHARED

char buffer[PATH_MAX];
void *handle = NULL;
char *(*pushkin)(char *) = NULL;

int find_lib(char *path){
	DIR* cur_dir;
	struct dirent* cur_dirent;
	if((cur_dir = opendir(path)) == NULL){
		printf("Error: %s\n", strerror(errno));
		return 1;
	}
	while((cur_dirent = readdir(cur_dir)) != NULL){
		char *file = (char *)calloc(sizeof(char), strlen(path) + strlen(cur_dirent->d_name + 1));
		sprintf(file, "%s/%s", path, cur_dirent->d_name);
		struct stat cur_file_stat;
		lstat(file, &cur_file_stat);
		if(S_ISDIR(cur_file_stat.st_mode)){
			if(strcmp(cur_dirent->d_name, ".") && strcmp(cur_dirent->d_name, "..")){
				find_lib(file);
			}
		} else if(S_ISREG(cur_file_stat.st_mode)){
			char *ext;
			if( (ext = strrchr(cur_dirent->d_name, '.')) != NULL){
				if(!strcmp(ext, ".so")){
					if( (handle = dlopen(file, RTLD_LAZY)) != NULL ){
						pushkin = dlsym(handle, "pushkin");
					}				
				}
			}
		}
	}
	return 0;
}

#endif


int main(int argc, char** argv){
	setlocale(LC_ALL, "Rus");	
#ifdef NOSHARED
	int i = find_lib(".");
	char* s = pushkin("У лукоморья дуб зеленый,\nЗлатая цепь на дубе том:\nИ днем и ночью кот ученый\n");
	if(handle == NULL || pushkin == NULL){
		printf("SORRY BB\n");
	}
	printf("%s", s);
#endif

#ifndef NOSHARED
	char* s = pushkin("У лукоморья дуб зеленый,\nЗлатая цепь на дубе том:\nИ днем и ночью кот ученый\n");
	printf("%s", s);
	free(s); s = NULL;
#endif	
	
	return 0;
}
