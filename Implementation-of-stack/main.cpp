#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "message.h"
#include "stack.h"
#include "interface.h"

int main(){
	stackInit(studentFree);
    
	int i=0;
	while (true) {
		menu();
		scanf_s("%d", &i);
		switch (i) {
		case PUSH: push();
			break;
		case POP: pop();
			break;
		case FIND: find();
			break;
		case CLEAR: clear();
			break;
		case SHOW: show();
			break;
		case READ_STACK: readStack();
			break;
		case SAVE_STACK: saveStack();
			break;
		case READ_ONE_STUDENT: readStudent();
			break;
		case SAVE_ONE_STUDENT:saveStudent();
			break;
		case STOP: return 0;
		default:
			printf("Niepoprawny wybor\n");
		};
	}
	

	return 0;
}


