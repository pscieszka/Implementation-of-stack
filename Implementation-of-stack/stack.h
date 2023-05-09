#pragma once
#include "student.h"

struct stack
{
   student ob;
   struct stack *ptr; 
};

struct stack* push(struct stack* top, struct student s);
struct stack* pop(struct stack* top);


