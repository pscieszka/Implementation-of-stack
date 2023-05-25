#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "student.h"
#include "message.h"
#include "stack.h"


freeData ptrFree;
stack* top = NULL;

void stackInit(freeData ptrFree2) {
	top = NULL;
	ptrFree = ptrFree2;
}
void stackFree() {
	stack* curr =top;
	stack* next = NULL;

	while (curr != NULL) {
		(*ptrFree)(curr->dataPtr);
		next = curr;
		curr = curr->next;
		free(next);
	}
	top = NULL;
}

stack* stackPush(void* ptr) {
	stack* curr = (stack*)malloc(sizeof(stack));
	if (!curr)
		return NULL;

	curr->dataPtr = ptr;
	
	curr->next = top;
	top = curr;

	return curr;
}

stack stackPop() {
	stack popped;
	popped.dataPtr = NULL;
	popped.next = NULL;


	stack* poppedNode = top;
	popped.dataPtr = poppedNode->dataPtr;

	top = top->next;
	poppedNode->next = NULL;
	free(poppedNode);


	return popped;
}

stack* stackTop() {
	return top;
}
void* stackSearch(void* searchData, compData ptrComp, int firstEntry) {
	static stack* ptr;
	stack* ptr2 = NULL;
	if (firstEntry) {
		ptr = top;
	}
	if (ptr == NULL) {
		return NULL;
	}
	while (ptr) {
		if (!(*ptrComp)(ptr->dataPtr, searchData)) {
			ptr = ptr->next;
		}
		else {
			ptr2 = ptr;
			ptr = ptr->next;
			return ptr2->dataPtr;
		}
	}
	return NULL;
	

}
void stackSave(const char* filename) {
	FILE* file;
	if (fopen_s(&file, filename, "wb") != 0)
	{
		messageFun(FILE_OPEN_FAILED);
		return;
	}

	stack* curr = top;
	while (curr != NULL) {
		struct student* stud = (struct student*)(curr->dataPtr);
		fwrite(stud, sizeof(struct student), 1, file);
		curr = curr->next;
	}

	fclose(file);
	stackFree();
}

void stackRead(const char* filename) {
	FILE* file;
	if (fopen_s(&file, filename, "rb") != 0) {
		messageFun(FILE_OPEN_FAILED);
		return;
	}

	
	if (fseek(file, 0, SEEK_END) != 0) {
		messageFun(FILE_OPERATION_FAILED);
		fclose(file);
		return;
	}

	//obliczanie wielkosc wielkosci pliku, wskaznik jest ustawiony na koniec pliku,a funkcja ftell podaje liczbe bajtow calego pliku
	long fileSize = ftell(file);
	if (fileSize == -1) {
		messageFun(FILE_OPERATION_FAILED);
		fclose(file);
		return;
	}

	//wielkosc jedngo rekordu jest rowna wielkosci struktury student, przesuwamy wskaznik w pliku o wielkosc jednej struktury w prawo
	int recordSize = sizeof(struct student);
	fseek(file, -recordSize, SEEK_END); 

	
	while (fileSize > 0) {
		struct student* stud = (struct student*)malloc(recordSize);
		if (stud == NULL) {
			messageFun(ALLOC_ERROR);
			fclose(file);
			return;
		}

		if (fread(stud, recordSize, 1, file) != 1) {
			messageFun(READ_FROM_FILE_FAILED);

			free(stud);
			fclose(file);
			return;
		}

		stackPush(stud);

		//wskaznik musi byc przesniuty o 2 wielkosci strukutry, poniewaz po wczytaniu studenta wskaznik przesuwa sie o recordSize w lewo,
		//wiec zeby odczytac nastepnego studenta musimy przesunac sie o 2*recordSize w prawo
		//np.
		// A B C D E     na poczatku  wskaznik jest na koncu D
		//       ^ 
		// A B C D E     wczytujemy E i wskaznik jest na koncu E
		//         ^
		// A B C D E     cofamy wskaznik o 2 pozycje zeby wczytac D
		//	   ^	
		//itd...

		fseek(file, -2 * recordSize, SEEK_CUR);
		// Aktualizujemy liczby studentow do wczytania
		fileSize -= recordSize;
	}

	fclose(file);
}
