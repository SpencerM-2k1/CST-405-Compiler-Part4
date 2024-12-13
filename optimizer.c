#include "optimizer.h"
#include "codeGenerator.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Optimize the TAC by applying constant folding, propagation, and dead code elimination.
TAC* optimizeTAC(TAC* head) {
    //Need to use global `tacHead` rather than the parameter because of seg fault errors when the head gets freed in some cases
    //Design-wise? I hate it. It will have to do for now.

    // constantFolding(&head);          // Simplify constant expressions
                                        // (Not really needed due to the structure of our TACs, const propagation handles this)
    constantPropagation(&tacHead);      // Propagate constants through the TAC
    copyPropagation(&tacHead);          // Replace variables with assigned values
    // deadCodeElimination(&head);      // Remove unused assignments
    return head;  // Return the optimized TAC list
}

// Perform constant propagation on TAC instructions.
void constantPropagation(TAC** head) {
    TAC* current = *head;
    while (current != NULL) {
        if (current->op != NULL && (strncmp(current->op, "+.", 2) == 0 || strncmp(current->op, "-.", 2) == 0)) {
            // Get the operator without the type suffix
            char op = current->op[0]; // '+' or '-'
            
            TAC* arg1Assignment = NULL;    // Stores the TAC which last assigned a result to arg1
            TAC* arg2Assignment = NULL;    // Stores the TAC which last assigned a result to arg2
            if (constantCheck(current, &arg1Assignment, &arg2Assignment))
            {
                // Convert constants to integers
                int constResult;
                if (op == '+') {
                    constResult = atoi(arg1Assignment->arg1) + atoi(arg2Assignment->arg1);
                } else if (op == '-') {
                    constResult = atoi(arg1Assignment->arg1) - atoi(arg2Assignment->arg1);
                }
                char resultStr[20];
                snprintf(resultStr, sizeof(resultStr), "%d", constResult);
                
                // Generate a new "assign.int" TAC
                TAC* replacementTAC = createTAC(current->result, resultStr, "assign.int", NULL);
                
                // Replace `current` with new TAC
                replaceTAC(&current, &replacementTAC);
                current = replacementTAC;
                // Remove arg1Assignment and arg2Assignment
                removeTAC(&arg1Assignment);
                removeTAC(&arg2Assignment);
            }
        }
        current = current->next;
    }
}

//I will be burned at the stake if a professional ever sees how nested this code used to be.   -Spencer
bool constantCheck(TAC* start, TAC** arg1Return, TAC** arg2Return)
{
    TAC* current = start->prev;
    while (current && !(*arg1Return && *arg2Return)) // While both args are not found yet
    {
        // Check if either arg is listed as the result of the current TAC
        if ((!*arg1Return) && (strcmp(start->arg1, current->result) == 0))
        {
            if (strncmp(current->op, "assign.", 7) == 0) {
                *arg1Return = current;
            } else {
                return false; // Last assignment was not a constant assignment
            }
        }
        if ((!*arg2Return) && (strcmp(start->arg2, current->result) == 0))
        {
            if (strncmp(current->op, "assign.", 7) == 0) {
                *arg2Return = current;
            } else {
                return false; // Last assignment was not a constant assignment
            }
        }
        current = current->prev;
    }
    return (*arg1Return && *arg2Return);
}

// Perform copy propagation on TAC instructions.
//      Specifically, if a load operation is encountered, any time the referenced variable is loaded,
//  remove the load operation and instead use the first temp variable loaded into
//      Stop once a store operation is encountered, as this will overwrite the original value of the var
void copyPropagation(TAC** head) {
    TAC* current = *head;

    while (current) {
        if ((current->op) && (strncmp(current->op, "load.", 5) == 0)) {
            printf("OPTIMIZER (copyPropagation): The following load operation was detected:\n");
            printTAC(current);
            replaceCopies(current);
        }
        current = current->next;
    }
}



//Replace all tempVar copies that occur after `start` TAC
//  Assumes `start` is a load instruction
void replaceCopies(TAC* start)
{
    TAC* current = start->next;
    while(current)
    {
        if ((current->result) && (strcmp(current->result, start->arg1) == 0)) {
            // Check if it's a store operation
            if (strncmp(current->op, "store.", 6) == 0) {
                return; // Stop; variable has been overwritten
            }
        }

        // A load operation for the same variable occurs before a store operation -- a copy is created
        if ((strncmp(current->op, "load.", 5) == 0) && (strcmp(start->arg1, current->arg1) == 0))
        {
            char* redundantVar = current->result; // ID of temp var to be replaced
            TAC* redundancyCursor = current->next;
            while(redundancyCursor)
            {
                if ((redundancyCursor->result) && (strcmp(redundancyCursor->result, start->arg1) == 0)) {
                    if (strncmp(redundancyCursor->op, "store.", 6) == 0) {
                        break; // Stop; variable has been overwritten
                    }
                }
                if (redundancyCursor->arg1 && strcmp(redundancyCursor->arg1, redundantVar) == 0) {
                    free(redundancyCursor->arg1);
                    redundancyCursor->arg1 = strdup(start->result);
                }
                if (redundancyCursor->arg2 && strcmp(redundancyCursor->arg2, redundantVar) == 0) {
                    free(redundancyCursor->arg2);
                    redundancyCursor->arg2 = strdup(start->result);
                }

                redundancyCursor = redundancyCursor->next;
            }
            return;
        }
        current = current->next;
    }
}

// Perform dead code elimination on TAC instructions.
// void deadCodeElimination(TAC** head) {
//     TAC* current = *head;
//     TAC* prev = NULL;

//     while (current != NULL) {
//         if (current->op != NULL && strcmp(current->op, "assign") == 0) {
//             // Check if the result is ever used
//             int isUsed = 0;
//             TAC* temp = current->next;
//             while (temp != NULL) {
//                 if ((temp->arg1 != NULL && strcmp(temp->arg1, current->result) == 0) ||
//                     (temp->arg2 != NULL && strcmp(temp->arg2, current->result) == 0)) {
//                     isUsed = 1;
//                     break;
//                 }
//                 temp = temp->next;
//             }

//             if (!isUsed) {
//                 // Remove the dead code (the assignment is not used)
//                 if (prev == NULL) {
//                     *head = current->next; // Move head forward
//                 } else {
//                     prev->next = current->next; // Skip the current TAC instruction
//                 }
//                 free(current->op);
//                 free(current->arg1);
//                 free(current->arg2);
//                 free(current->result);
//                 free(current);
//                 current = prev ? prev->next : *head;
//                 continue;
//             }
//         }
//         prev = current;
//         current = current->next;
//     }
// }

// Print optimized TAC to terminal and file
void printOptimizedTAC(const char* filename, TAC* head) {
    
    FILE* outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    // if (head->arg1) printf("arg1 = %s\n", head->arg1);
    // if (head->op) printf("op = %s\n", head->op);
    // if (head->arg2) printf("arg2 = %s\n", head->arg2);
    // if (head->result) printf("result = %s\n", head->result);

    TAC* current = head;
    while (current != NULL) {
        // printf("%s = %s %s %s\n", current->result ? current->result : "(null)", current->arg1 ? current->arg1 : "(null)", current->op ? current->op : "(null)", current->arg2 ? current->arg2 : "(null)"); 
        printf("%s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
        fprintf(outputFile, "%s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
        current = current->next;
    }

    printf("Optimized TAC written to %s\n", filename);
    fclose(outputFile);
}

