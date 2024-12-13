#include "labelStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* labelStack[LABEL_STACK_SIZE];
int labelCursor = 0;

void pushLabel(char* label) {
    if (labelCursor < LABEL_STACK_SIZE) //If stack is not full
    {
        labelStack[labelCursor] = label;
        labelCursor++;
        printLabelStack(); //DEBUG
    }
    else
    {
        fprintf(stderr, "LABEL_STACK: Stack overflow! Halting compiler...\n");
        exit(1);
    }
}

char* popLabel() {
    if (labelCursor > 0) //If stack is not empty
    {
        char* returnLabel;
        labelCursor--;
        returnLabel = labelStack[labelCursor];
        printLabelStack(); //DEBUG
        return returnLabel;
    }
    else
    {
        fprintf(stderr, "LABEL_STACK: Stack underflow! Halting compiler...\n");
        exit(1);
    }
}

char* peekLabel() {
    if (labelCursor > 0) //If stack is not empty
    {
        return labelStack[labelCursor - 1];
    }
    else
    {
        fprintf(stderr, "LABEL_STACK: No labels on stack! Halting compiler...\n");
        exit(1);
    }
}

void printLabelStack() {
    printf("    ===LABEL STACK===\n");
    for (int i = 0; i < labelCursor; i++)
    {
        printf("     - %s\n", labelStack[i]);
    }
    printf("    ===END OF LABEL STACK===\n");
}