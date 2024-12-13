#ifndef LABEL_STACK_H
#define LABEL_STACK_H

#define LABEL_STACK_SIZE 100

extern char* labelStack[];
extern int labelCursor;

void pushLabel(char* label);
char* popLabel();
char* peekLabel();
void printLabelStack();

#endif