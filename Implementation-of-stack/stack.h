#pragma once
#include "student.h"

typedef struct Node {
    student data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

void stack_init(Stack* stack);
void stack_free(Stack* stack);
void stack_push(Stack* stack, student data);
student stack_pop(Stack* stack);
student stack_peek(const Stack* stack);
bool stack_contains(const Stack* stack, student data);
void stack_save_to_file(const Stack* stack, const char* filename);
void stack_load_from_file(Stack* stack, const char* filename);