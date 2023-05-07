#include <stdio.h>
#include "student.h"

int main(){
	student s;
	char nazwisko[100];
	int wiek;
	kierunek kierunekStudiow;

	printf("Podaj nazwisko studenta: ");
	scanf_s("%s", nazwisko, 100);

	printf("Podaj wiek studenta: ");
	scanf_s("%d", &wiek);

	printf("Podaj kierunek studiow (0-Informatyka, 1-Matematyka, 2-Fizyka): ");
	scanf_s("%d", &kierunekStudiow);

	if (studentInit(&s, wiek, nazwisko, kierunekStudiow))
	{
		printf("Utworzono obiekt student:\n");
		studentPrint(&s);
		studentFree(&s);
	}
	else
	{
		printf("Nie uda³o siê utworzyc obiektu student\n");
	}

	return 0;
   
}


