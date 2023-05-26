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

void stackSave( const char* filename) {
	FILE* file = fopen(filename, "wb");  

	if (file == NULL) {
		printf("Nie mo¿na otworzyæ pliku.\n");
		return;
	}

	stack* current = top;
	while (current != NULL) {
		student* studentData = (student*)current->dataPtr;

		fwrite(studentData->nazwisko, sizeof(char), studentData->len, file);
		fwrite(&(studentData->wiek), sizeof(int), 1, file);
		fwrite(&(studentData->kierunekStudiow), sizeof(kierunek), 1, file);
		fwrite(&(studentData->len), sizeof(size_t), 1, file);
		current = current->next;
	}

	fclose(file);  
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

	
	long fileSize = ftell(file);
	if (fileSize == -1) {
		messageFun(FILE_OPERATION_FAILED);
		fclose(file);
		return;
	}

	long long recordSize=0;
	
	student* stud = NULL;
	while (fileSize > 0) {
		size_t nameSize = 0;
		if (fseek(file, -(long long)sizeof(size_t), SEEK_CUR) != 0) { 
			messageFun(FILE_OPERATION_FAILED);
			fclose(file);
			free(stud);
			return;
		}
		//czytam od tylu pliku wielkosc ostatniego nazwiska
		if (fread(&nameSize, sizeof(size_t), 1, file) != 1) { 
			messageFun(READ_FROM_FILE_FAILED);
			fclose(file);
			free(stud);
			return;
		}
		// znajac dlugosc nazwiska moge policzyc ile zajmuje ostatni rekord
		long long recordSize = nameSize + sizeof(int) + sizeof(kierunek) + sizeof(size_t); 
		if (fseek(file, -recordSize, SEEK_CUR) != 0) {
			messageFun(FILE_OPERATION_FAILED);
			fclose(file);
			free(stud);
			return;
		}
		//alokuje pamiec dla nazwiska i struktury student, oraz znajac kolejnosc zapisu skladowych struktury 
		stud = (student*)malloc(sizeof(student));
		stud->nazwisko = (char*)malloc(nameSize + 1);
		if (stud == NULL || stud->nazwisko == NULL) {
			messageFun(ALLOC_ERROR);
			fclose(file);
			free(stud);
			return;
		}

		if (fread(stud->nazwisko, sizeof(char), nameSize, file) != nameSize) {
			messageFun(READ_FROM_FILE_FAILED);
			fclose(file);
			free(stud->nazwisko);
			free(stud);
			return;
		}

		stud->nazwisko[nameSize] = '\0';

		if (fread(&(stud->wiek), sizeof(int), 1, file) != 1) {
			messageFun(READ_FROM_FILE_FAILED);
			fclose(file);
			free(stud->nazwisko);
			free(stud);
			return;
		}

		if (fread(&(stud->kierunekStudiow), sizeof(kierunek), 1, file) != 1) {
			messageFun(READ_FROM_FILE_FAILED);
			fclose(file);
			free(stud->nazwisko);
			free(stud);
			return;
		}

		if (fread(&(stud->len), sizeof(size_t), 1, file) != 1) {
			messageFun(READ_FROM_FILE_FAILED);
			fclose(file);
			free(stud->nazwisko);
			free(stud);
			return;
		}
		if (fseek(file, -recordSize, SEEK_CUR) != 0) {
			messageFun(FILE_OPERATION_FAILED);
			fclose(file);
			free(stud);
			return;
		}
		stackPush(stud);
		fileSize -= recordSize;
	}

	fclose(file);
}






//stackPush(stud);

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

		//fseek(file, -2 * recordSize, SEEK_CUR);
		// Aktualizujemy liczby studentow do wczytania
		//fileSize -= recordSize;