#pragma once

#pragma warning (disable : 4996)

enum messages
{
	ALLOC_ERROR,
	FILE_OPEN_FAILED,
	FILE_OPERATION_FAILED,
	READ_FROM_FILE_FAILED,
	PUSH_ERROR
	
};

void messageFun(enum messages mess);

