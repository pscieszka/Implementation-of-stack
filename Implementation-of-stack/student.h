#pragma once
enum kierunek
{
	INFORMATYKA,
	MATEMATYKA,
	FIZYKA
};

	struct student
	{
		char nazwisko[512];
		int wiek;
		kierunek kierunekStudiow;
	};

	void *studentInit(int wiek, char *str, kierunek kierunekStudiow);
	void studentFree(student* ob);
	void studentPrint(student* ob);
	int studentAge();

	


