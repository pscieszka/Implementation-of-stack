#pragma once
enum kierunek
{
	INFORMATYKA,
	MATEMATYKA,
	FIZYKA
};

	struct student
	{
		char* nazwisko;
		int wiek;
		kierunek kierunekStudiow;
	};

	bool studentInit(student* ob, int wiek, char* str, kierunek kierunekStudiow);
	void studentFree(student* ob);
	void studentPrint(student* ob);


