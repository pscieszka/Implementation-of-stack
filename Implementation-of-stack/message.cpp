#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"


static const  char* message_str_tab[] = {
	"E memory allocation error",     //MEM_ERROR
	"W field of study not found",	 //FIELD_OF_STUDY_ERROR		
};

void messageFun(enum messages mess)

{
	puts(message_str_tab[mess]);

	
	if (message_str_tab[mess][0] == 'E')
	{
		//deloc
		system("pause");
	}

	return;
}