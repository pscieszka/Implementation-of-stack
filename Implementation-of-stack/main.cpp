#include <stdio.h>
#include "student.h"
#include "message.h"

int main(){
	student s;
	char nazwisko[100];
	int wiek;
	kierunek kierunekStudiow;

	printf("Podaj nazwisko studenta: ");
	scanf_s("%s", nazwisko, 100);

	wiek = studentAge();

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
		printf("Nie udalo sie utworzyc obiektu student\n");
	}

	return 0;
   
}


