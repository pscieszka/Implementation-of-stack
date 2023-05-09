#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "student.h"
#include "stack.h"

struct stack* push(struct stack* top, struct student s)
{
    struct stack* newTop = (struct stack*)malloc(sizeof(struct stack));
    newTop->ob.nazwisko = (char*)malloc((strlen(s.nazwisko) + 1) * sizeof(char));
    strcpy(newTop->ob.nazwisko, s.nazwisko);
    newTop->ob.wiek = s.wiek;
    newTop->ob.kierunekStudiow = s.kierunekStudiow;
    newTop->ptr = top;
    return newTop;
}

struct stack* pop(struct stack* top)
{
    if (top == NULL) {
        printf("Stos jest pusty\n");
        return NULL;
    }
    struct stack* newTop = top->ptr;
    free(top->ob.nazwisko);
    free(top);
    return newTop;
}
