#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "student.h"
#include "message.h"
#include "stack.h"
#include "interface.h"

int main() {
	stackInit(studentFree);

	int i = 0;
	while (true) {
		menu();
		if (scanf_s("%d", &i) == 1) { // sprawdzamy czy na wejsciu podany jest typ int
			switch (i) {
			case PUSH: push(); //dodanie elementu na szczyt stosu
				break;
			case POP: pop(); //wyrzucenie elementy z gory stosu oraz wypisanie go w stdout
				break;
			case FIND: find(); // wyszukiwanie studenta po nazwisku w stosie i wyswietlanie jego danych
				break;
			case CLEAR: clear(); // czyszczenie stosu
				break;
			case SHOW: show(); //wyswietlanie calego stosu
				break;
			case READ_STACK: readStack(); // odczytanie calego stosu, po odczytaniu obecne dane sie usuna 
				break;
			case SAVE_STACK: saveStack(); //wczytanie calego stosu do pliku
				break;
			case READ_ONE_STUDENT: readStudent(); // zapis jednego studenta do pliku , gdy zapiszemy studenta do pliku zostanie uzyta funkcja pop
				break;
			case SAVE_ONE_STUDENT: saveStudent(); // wczytanie jednego studenta z pliku do stosu, wczytywac dane studenta mozna bez  konca (obecny stos nie usuwa sie, w przeciwienstwie do save stack)
				break;
			case CLEAR_FILES: deleteFiles(); // usuwanie plikow z danymi
				break;
			case STOP: return 0;
			default:
				printf("Niepoprawny wybor\n");
			};
		}
		else {
			printf("Niepoprawny wybor\n");
		}
		while (getchar() != '\n');
	}

	return 0;
}
