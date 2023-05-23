#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"
#include "stack.h"


static const  char* message_str_tab[] = {
	"ERROR: memory allocation error",     
	"WARNING: open file failed: check if file exists",
	"WARNING: file operations failed",
	"WARNING: read from file failed",
	"WARNING: stack push error",
};

void messageFun(enum messages mess)

{
	puts(message_str_tab[mess]);

	
	if (message_str_tab[mess][0] == 'E')
	{
		stackFree();
		system("pause");
	}

	return;
}