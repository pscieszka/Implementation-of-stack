#pragma once

enum interface {
	PUSH,
	POP,
	FIND,
	CLEAR,
	SHOW,
	READ_STACK,
	SAVE_STACK,
	READ_ONE_STUDENT,
	SAVE_ONE_STUDENT,
	STOP
};

void menu();
void push();
void pop();
void find();
void show();
void clear();
void readStudent();
void saveStudent();



