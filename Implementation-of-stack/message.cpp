#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"
#include "stack.h"


static const  char* message_str_tab[] = {
	"E memory allocation error",     
	"W file warning, failed save or read",	 	
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