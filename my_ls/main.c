#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _POSIXSOURCE 1   // always define if you supposed to use POSIX api




char buf[PATH_MAX + 1];

int str_cmp(const void* a, const void* b)
{
    const char* aa = *(const char**)a;
    const char* bb = *(const char**)b;
    return strcmp(aa,bb);
}

main(argc, argv)
int argc; char** argv;
{
	if(argc < 2){
		printf("USAGE: %s <path>\n", *argv);
		exit(1);
	}
	DIR *dir;
	struct dirent *cur_dir;
	struct stat fs_stat;

	unsigned total_size = 0;
	lstat(argv[1], &fs_stat);
	if(S_ISDIR(fs_stat.st_mode)){
		dir = opendir(argv[1]);
		if(dir == NULL){
			printf("Error: %s\n", strerror(errno));
			exit(1);
		}
		printf("Directory %s\n", realpath(argv[1], buf));	
		char **list_dirs = NULL;
		size_t list_dirs_index = 0;
		while((cur_dir = readdir(dir)) != NULL){
			lstat(cur_dir->d_name, &fs_stat);
			list_dirs = (char **)realloc(list_dirs, (list_dirs_index + 1) * sizeof(char *));
			char *buf = (char *)malloc(sizeof(cur_dir->d_name));
			memcpy(buf, cur_dir->d_name, sizeof(cur_dir->d_name));
			list_dirs[list_dirs_index] = buf;
			buf = NULL;
			list_dirs_index++;
		}
		qsort(list_dirs, list_dirs_index, sizeof(*list_dirs), str_cmp);
		for(int i = 0; i < list_dirs_index; i++){
			lstat(list_dirs[i], &fs_stat);
			if(!strcmp(list_dirs[i], ".") || !strcmp(list_dirs[i], "..")){
				printf("\tSpecial %s\n", list_dirs[i]); 
			} else {
				printf("\t%u %s\n", fs_stat.st_size, list_dirs[i]);
				total_size += fs_stat.st_size;
			}
			free(list_dirs[i]);
			list_dirs[i] = NULL;
		}
		printf("\tTotal of %u in %u files\n", total_size, list_dirs_index);
		free(list_dirs);
		list_dirs = NULL;
		free(cur_dir);
		cur_dir = NULL;
		free(dir);
		dir = NULL;
		exit(0);
	} else if(S_ISREG(fs_stat.st_mode)){
		printf("File: %s with total size of %u bytes\n", realpath(argv[1], buf), fs_stat.st_size);
		exit(0);	
	} else {
		printf("I don't really know what kind of file it is %s\n", argv[1]);
		exit(1);
	}

}




