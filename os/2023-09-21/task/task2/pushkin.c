#include "pushkin.h"
#include <stdlib.h>
#include <string.h>

char* pushkin(char *text){
	char *end_pos = NULL;
	char *ret_str = NULL;
	if(text == NULL){
		end_pos = strchr(poem, 0x0a);
		ret_str = (char *)calloc(sizeof(char), end_pos - poem);
		strncpy(ret_str, poem, (end_pos - poem + 1) * sizeof(char));
		return ret_str;
	}

	char *end_cur_pos  = strchr(poem + strlen(text), 0x0a);
	ret_str = (char *)calloc(sizeof(char), end_cur_pos - poem + 1);
	strncpy(ret_str, poem, end_cur_pos - poem + 1);
	return ret_str;
}
