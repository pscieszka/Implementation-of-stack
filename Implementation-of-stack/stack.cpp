#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "student.h"
#include "stack.h"
/*

void stack_init(Stack* stack) {
    stack->top = NULL;
}

void stack_free(Stack* stack) {
    while (stack->top != NULL) {
        Node* node = stack->top;
        stack->top = stack->top->next;
        free(node->data.nazwisko);
        free(node);
    }
}

void stack_push(Stack* stack, student data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data.nazwisko = (char*)malloc((strlen(data.nazwisko) + 1) * sizeof(char));
    strcpy_s(newNode->data.nazwisko,strlen(data.nazwisko)+1, data.nazwisko);
    newNode->data.wiek = data.wiek;
    newNode->data.kierunekStudiow = data.kierunekStudiow;
    newNode->next = stack->top;
    stack->top = newNode;
}

student stack_pop(Stack* stack) {
    student emptyStudent;
    emptyStudent.nazwisko = NULL;
    emptyStudent.wiek = 0;
    emptyStudent.kierunekStudiow = INFORMATYKA;

    if (stack->top == NULL) {
        return emptyStudent;
    }
    Node* topNode = stack->top;
    student data = topNode->data;
    stack->top = stack->top->next;
    free(topNode->data.nazwisko);
    free(topNode);
    return data;
}*/