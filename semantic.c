#include "semantic.h"
#include "symbolTable.h"
#include "codeGenerator.h"
#include "operandStack.h"
#include "labelStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global head and tail of the TAC list
TAC* tacHead = NULL;
TAC* tacTail = NULL;

// Function TAC heads and tails
FuncTAC* funcTacHeads = NULL;
FuncTAC* funcTacTails = NULL;

// Current TAC being operated on
TAC** currentTacHead = NULL;
TAC** currentTacTail = NULL;
FuncTAC* currentFuncTAC = NULL;
bool inFunction = false;

// Reference to the symbol table
SymbolTable* symTabRef = NULL;

// Temporary variable counters
int tempIntCount = 0;
int tempFloatCount = 0;
int tempCharCount = 0;

// Counter for generating unique labels
int labelCount = 0;

// Add a global constant pool
typedef struct ConstantPoolEntry {
    char* value;                     // The string representation of the constant
    char* tempVar;                   // The temporary variable assigned to the constant
    VarType type;                    // The type of the constant
    struct ConstantPoolEntry* next;  // Pointer to the next entry
} ConstantPoolEntry;

ConstantPoolEntry* constantPool = NULL;

// Initialize Semantic Analyzer with the symbol table reference
void initSemantic(SymbolTable* symbolTable) {
    symTabRef = symbolTable;
    currentTacHead = &tacHead;
    currentTacTail = &tacTail;
}

// General function to append a TAC to the TAC list
void appendTAC(TAC** head, TAC** tail, TAC* newInstruction) {
    if (!*head) {
        // printf("appendTAC(): TAC is empty, creating new head\n");
        *head = newInstruction;
        *tail = newInstruction;
        newInstruction->prev = NULL;
        newInstruction->next = NULL;
    } else {
        // printf("appendTAC(): TAC exists, appending new TAC\n");
        (*tail)->next = newInstruction;
        newInstruction->prev = *tail;
        newInstruction->next = NULL;
        (*tail) = newInstruction;
    }
}

// General function to create TAC instructions
TAC* createTAC(char* result, char* arg1, char* op, char* arg2) {
    TAC* newTAC = (TAC*)malloc(sizeof(TAC));
    newTAC->result = result ? strdup(result) : NULL;
    newTAC->arg1 = arg1 ? strdup(arg1) : NULL;
    newTAC->op = op ? strdup(op) : NULL;
    newTAC->arg2 = arg2 ? strdup(arg2) : NULL;
    newTAC->next = newTAC->prev = NULL;
    return newTAC;
}

// Helper to generate a temporary variable based on type
char* createTempVar(VarType type) {
    char* tempVar = malloc(30);  // Allocate space for temp variable name
    if (type == VarType_Int) {
        snprintf(tempVar, 30, "i%d", tempIntCount++);
    } else if (type == VarType_Float) {
        snprintf(tempVar, 30, "f%d", tempFloatCount++);
    } else if (type == VarType_Char) {
        snprintf(tempVar, 30, "c%d", tempCharCount++);
    } else {
        fprintf(stderr, "Unsupported type for temporary variable (VarType: %s)\n", varTypeToString(type));
        exit(1);
    }
    return tempVar;
}

// Function to create unique labels
char* createLabel() {
    char buffer[20];
    snprintf(buffer, 20, "L%d", labelCount++);
    return strdup(buffer);
}

// General function to perform semantic analysis on an AST node
void semanticAnalysis(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NodeType_Program:
            printf("Performing semantic analysis on program\n");
            semanticAnalysis(node->data.program.varDeclList);
            semanticAnalysis(node->data.program.stmtList);
            break;

        case NodeType_DeclList:
            semanticAnalysis(node->data.declList.decl);
            semanticAnalysis(node->data.declList.next);
            break;

        case NodeType_VarDecl:
        case NodeType_ArrDecl:
            // Variable declarations are handled during parsing
            break;

        case NodeType_AssignStmt:
            semanticAnalysis(node->data.assignStmt.expr);
            generateTACForAssign(node);
            break;

        case NodeType_AssignArrStmt:
            semanticAnalysis(node->data.assignArrStmt.indexExpr);
            semanticAnalysis(node->data.assignArrStmt.expr);
            generateTACForAssignArr(node);
            break;

        case NodeType_ReturnStmt:
            semanticAnalysis(node->data.returnStmt.returnExpr);
            handleReturnStmt(node);
            break;

        case NodeType_UnaryOp:
            semanticAnalysis(node->data.unaryOp.expr);
            generateTACForExpr(node);
            break;

        case NodeType_BinOp:
            semanticAnalysis(node->data.binOp.left);
            semanticAnalysis(node->data.binOp.right);
            generateTACForExpr(node);
            break;

        case NodeType_RelOp:
            // Add this case to handle relational operators
            semanticAnalysis(node->data.relOp.left);
            semanticAnalysis(node->data.relOp.right);
            generateTACForExpr(node);
            break;

        case NodeType_WriteStmt:
            semanticAnalysis(node->data.writeStmt.expr);
            generateTACForWrite(node);
            break;

        case NodeType_IntExpr:
        case NodeType_FloatExpr:
        case NodeType_CharExpr:
        case NodeType_SimpleID:
            generateTACForExpr(node);
            break;

        case NodeType_ArrAccess:
            semanticAnalysis(node->data.arrAccess.indexExpr);
            generateTACForExpr(node);
            break;

        case NodeType_FuncDecl:
            handleFunctionDeclaration(node);
            break;

        case NodeType_ParamList:
            handleParameterList(node);
            break;

        case NodeType_Param:
            handleParameter(node);
            break;

        case NodeType_StmtList:
            semanticAnalysis(node->data.stmtList.stmt);
            semanticAnalysis(node->data.stmtList.stmtList);
            break;

        case NodeType_FuncCall:
            handleFunctionCall(node);
            break;

        case NodeType_ArgList:
            handleArgList(node);
            break;

        case NodeType_Arg:
            handleArg(node);
            break;

        case NodeType_VarDeclList:
            handleFuncVarDeclList(node);
            break;

        case NodeType_IfStmt:
            handleIfStatement(node);
            break;

        case NodeType_WhileStmt:
            handleWhileStatement(node);
            break;
        
        case NodeType_BreakStmt:
            handleBreakStatement(node);
            break;

        default:
            fprintf(stderr, "Unhandled Node Type in semantic analysis: %d\n", node->type);
            exit(1);
            break;
    }
}

// Handle function declarations
void handleFunctionDeclaration(ASTNode* node) {

    SubTable* currentSubTab = peekSubTable(symTabRef);

    Symbol* funcSymbol = lookupSymbolInHierarchy(currentSubTab, node->data.funcDecl.name);

    printf("node->data.funcDecl.funcSubTable: %p\n", node->data.funcDecl.funcSubTable);
    pushSubTable(symTabRef, node->data.funcDecl.funcSubTable);
    ASTNode* currentParamList = node->data.funcDecl.paramList;
    

    initFuncTAC(node->data.funcDecl.name, node->data.funcDecl.returnType);

    while (currentParamList) {
        ASTNode* currentParam = currentParamList->data.paramList.param;
        printf("        symTabRef: %p\n",symTabRef);
        addParameter(symTabRef, funcSymbol, currentParam->data.param.name, currentParam->data.param.type);
        currentParamList = currentParamList->data.paramList.next;
    }

    semanticAnalysis(node->data.funcDecl.paramList);
    semanticAnalysis(node->data.funcDecl.varDeclList);
    semanticAnalysis(node->data.funcDecl.stmtList);

    finalizeFuncTAC();
    popSubTable(symTabRef);
}

// Handle parameter lists
void handleParameterList(ASTNode* node) {
    if (!node) return;

    semanticAnalysis(node->data.paramList.param);
    handleParameterList(node->data.paramList.next);
}

// Handle parameters
void handleParameter(ASTNode* node) {
    //Empty, might remove later
}


// Handle function calls
void handleFunctionCall(ASTNode* node) {
    if (!lookupSymbolInHierarchy(peekSubTable(symTabRef), node->data.funcCall.name)) {
        fprintf(stderr, "Function '%s' not declared\n", node->data.funcCall.name);
        exit(1);
    }

    handleArgList(node->data.funcCall.argList);

    generateTACForFuncCall(node);
}

// Handle Return Statement
void handleReturnStmt(ASTNode* node)
{
    //Mark function as containing a return statement
    currentFuncTAC->returnsValue = true;

    //Check if we are in a function. If not, halt compilation
    //   ?: Should return outside of a function abort the program, similar to
    //      calling return in main in C?
    if (!inFunction)
    {
        printf("SEMANTIC: Return called outside of a function, halting...\n");
        exit(1);
    }

    //Check for return expression
    //      TODO: Throw an error if a return expression is specified in
    //          a void-returning function, or if no return expression is
    //          specified in a function with a return type.
    if (currentFuncTAC->returnType == VarType_Void)
    {
        //If void-returning function attempts to return a value, halt compiler
        if (node->data.returnStmt.returnExpr)
        {
            printf("SEMANTIC: Attempted to return a value from a void-returning function\n");
            exit(1);
        }
    }
    else
    {
        VarType returnExprType = getExprType(node->data.returnStmt.returnExpr);
        if (returnExprType != currentFuncTAC->returnType)
        {
            printf("SEMANTIC: Attempted to return %s from a %s-returning function\n", varTypeToString(returnExprType), varTypeToString(currentFuncTAC->returnType));
            exit(1);
        }
    }

    if (node->data.returnStmt.returnExpr)
    {
        // semanticAnalysis(node->data.returnStmt.returnExpr);
        Operand* returnOperand = popOperand();
        char* result;
        char* operator;
        
        switch (returnOperand->operandType)
        {
            case (VarType_Int):
                result = "returnInt";
                operator = "store.int";
                break;
            case (VarType_Float):
                result = "returnFloat";
                operator = "store.float";
                break;
            case (VarType_Char):
                result = "returnChar";
                operator = "store.char";
                break;
            default:
                printf("Invalid return type: %s\n", varTypeToString(returnOperand->operandType));
                break;
        }
        TAC* returnValueInstr = createTAC(  //Output return value
            result,
            returnOperand->operandID,
            operator,
            NULL            
        );
        appendTAC(currentTacHead, currentTacTail, returnValueInstr);
    }
    else
    {
        //empty for now
    }

    TAC* returnStmtInstr = createTAC(  //Exit function
        NULL,
        NULL,
        "return",
        NULL
    );
    appendTAC(currentTacHead, currentTacTail, returnStmtInstr);
}

// Handle a function call's argument list
void handleArgList(ASTNode* node) {
    if (!node) return;

    semanticAnalysis(node->data.argList.arg);
    handleParameterList(node->data.argList.next);
}

// Handle a function call's argument list
void handleArg(ASTNode* node) {
    //TODO: Handle Arguments here


    //The final value of an expression representing an argument should
    //be assigned to the parameter variable of the function corresponding
    //to the argument in question.
    semanticAnalysis(node->data.arg.expr);
}

// Handle parameter lists
void handleFuncVarDeclList(ASTNode* node) {
    if (!node) return;

    semanticAnalysis(node->data.varDeclList.varDecl);
    handleFuncVarDeclList(node->data.varDeclList.next);
}

// Handle variable declarations within functions
void handleFuncVarDecl(ASTNode* node) {
    // Example usage: Check if the variable is already declared in the current scope
    if (lookupSymbolInHierarchy(peekSubTable(symTabRef), node->data.varDecl.varName)) {
        fprintf(stderr, "Variable '%s' already declared in current scope\n", node->data.varDecl.varName);
        exit(1);
    }
}

void handleIfStatement(ASTNode* node) {
    if (!node) return;

    semanticAnalysis(node->data.ifStmt.condition);

    // Generate labels
    char* elseLabel = createLabel();
    char* endLabel = NULL;
    if (node->data.ifStmt.elseStmt) {
        endLabel = createLabel();
    }

    // Evaluate condition
    // generateTACForExpr(node->data.ifStmt.condition);
    Operand* conditionOperand = popOperand();

    // Generate TAC for conditional jump to else label
    TAC* ifGotoInstr = createTAC(
        elseLabel,
        conditionOperand->operandID,
        "ifFalse",
        NULL
    );
    appendTAC(currentTacHead, currentTacTail, ifGotoInstr);
    freeOperand(conditionOperand);

    // Semantic analysis of the 'then' statement/block
    semanticAnalysis(node->data.ifStmt.thenStmt);

    if (node->data.ifStmt.elseStmt) {
        // Generate unconditional jump to end label after 'then' block
        TAC* gotoEndInstr = createTAC(
            endLabel,
            NULL,
            "goto",
            NULL
        );
        appendTAC(currentTacHead, currentTacTail, gotoEndInstr);
    }

    // Place the else label
    TAC* elseLabelInstr = createTAC(
        elseLabel,
        NULL,
        "label",
        NULL
    );
    appendTAC(currentTacHead, currentTacTail, elseLabelInstr);

    // Semantic analysis of the 'else' statement/block (if it exists)
    if (node->data.ifStmt.elseStmt) {
        semanticAnalysis(node->data.ifStmt.elseStmt);

        // Place the end label
        TAC* endLabelInstr = createTAC(
            endLabel,
            NULL,
            "label",
            NULL
        );
        appendTAC(currentTacHead, currentTacTail, endLabelInstr);

        free(endLabel);
    }

    free(elseLabel);
}

void handleWhileStatement(ASTNode* node) {
    if (!node) return;

    // Generate labels
    char* startLabel = createLabel();
    char* endLabel = createLabel();

    // Start of loop
    TAC* startLabelInstr = createTAC(
        startLabel,
        NULL,
        "label",
        NULL
    );
    appendTAC(currentTacHead, currentTacTail, startLabelInstr);

    //Condition check
    semanticAnalysis(node->data.whileStmt.condition);

    // Evaluate condition
    // generateTACForExpr(node->data.ifStmt.condition);
    Operand* conditionOperand = popOperand();

    // Generate TAC for conditional jump to else label
    TAC* ifGotoInstr = createTAC(
        endLabel,
        conditionOperand->operandID,
        "ifFalse",
        NULL
    );
    appendTAC(currentTacHead, currentTacTail, ifGotoInstr);
    freeOperand(conditionOperand);

    // Semantic analysis of loop block
    //  Update label stack to allow for break statement jumps
    pushLabel(endLabel);
    semanticAnalysis(node->data.whileStmt.block);
    popLabel();

    // Generate unconditional jump to start label to attempt another iteration
    TAC* gotoStartInstr = createTAC(
        startLabel,
        NULL,
        "goto",
        NULL
    );
    appendTAC(currentTacHead, currentTacTail, gotoStartInstr);

    // End of loop
    TAC* endLabelInstr = createTAC(
        endLabel,
        NULL,
        "label",
        NULL
    );
    appendTAC(currentTacHead, currentTacTail, endLabelInstr);
}

void handleBreakStatement(ASTNode* node)
{
    char* endLabel = peekLabel();
    TAC* gotoEndInstr = createTAC(
        endLabel,
        NULL,
        "goto",
        NULL
    );
    appendTAC(currentTacHead, currentTacTail, gotoEndInstr);
}

char* getOrCreateConstant(char* value, VarType type) {
    ConstantPoolEntry* current = constantPool;
    while (current) {
        if (strcmp(current->value, value) == 0 && current->type == type) {
            return current->tempVar; // Reuse existing temp variable
        }
        current = current->next;
    }

    // Create a new entry in the constant pool
    char* tempVar = createTempVar(type);
    ConstantPoolEntry* newEntry = malloc(sizeof(ConstantPoolEntry));
    newEntry->value = strdup(value);
    newEntry->tempVar = tempVar;
    newEntry->type = type;
    newEntry->next = constantPool;
    constantPool = newEntry;

    // Create TAC to assign the constant to the temp variable
    char* op;
    switch (type) {
        case VarType_Int:
            op = "assign.int";
            break;
        case VarType_Float:
            op = "assign.float";
            break;
        case VarType_Char:
            op = "assign.char";
            break;
        default:
            fprintf(stderr, "Unsupported constant type\n");
            exit(1);
    }

    TAC* constAssign = createTAC(
        tempVar,
        value,
        op,
        NULL
    );
    appendTAC(currentTacHead, currentTacTail, constAssign);

    return tempVar;
}

// Generate TAC for expressions
TAC* generateTACForExpr(ASTNode* expr) {
    if (!expr) return NULL;

    TAC* instruction = NULL;
    TAC* convInstruction = NULL; // Only used if mixed-type operands are detected

    switch (expr->type) {
        case NodeType_UnaryOp: {
            // generateTACForExpr(expr->data.unaryOp.expr);
            // semanticAnalysis(expr->data.unaryOp.expr);

            Operand* argOperand = popOperand();
            
            char buffer[20];
            VarType resultType = argOperand->operandType;
            switch (argOperand->operandType)
            {
                case VarType_Int:
                    snprintf(buffer, 20, "%s.int", expr->data.unaryOp.operator);
                    break;
                case VarType_Float:
                    snprintf(buffer, 20, "%s.float", expr->data.unaryOp.operator);
                    break;
                case VarType_Char:
                    //No unary operators exist for Char
                    printf("SEMANTIC: Operator %s is incompatible with VarType_Char\n", expr->data.unaryOp.operator);
                    exit(EXIT_FAILURE);
                    break;
                default:
                    printf("SEMANTIC: Invalid VarType in generateTACForExpr (unary op)\n");
                    break;
            }

            instruction = createTAC(
                createTempVar(resultType),
                argOperand->operandID,
                buffer,
                NULL
            );
            
            pushOperand(createOperandStruct(instruction->result, resultType));
            appendTAC(currentTacHead, currentTacTail, instruction);
            break;
        }

        case NodeType_BinOp: {
            // The semantic analysis for operands should already be done
            // Generate TAC for left and right operands
            // generateTACForExpr(expr->data.binOp.left);
            // generateTACForExpr(expr->data.binOp.right);
            // semanticAnalysis(expr->data.binOp.left);
            // semanticAnalysis(expr->data.binOp.right);
            printf("    Type of left operand: %s\n", varTypeToString(getExprType(expr->data.binOp.left)));
            printf("    Type of right operand: %s\n", varTypeToString(getExprType(expr->data.binOp.right)));
            printf("    Operator: %s\n", expr->data.binOp.operator);
            Operand* arg2Operand = popOperand();
            Operand* arg1Operand = popOperand();

            char buffer[20];
            VarType resultType;

            // Check if operator is logical AND or OR
            if (strcmp(expr->data.binOp.operator, "&&") == 0 || strcmp(expr->data.binOp.operator, "||") == 0) {
                // Boolean operators
                snprintf(buffer, 20, "%s.bool", expr->data.binOp.operator);
                resultType = VarType_Int;

                instruction = createTAC(
                    createTempVar(resultType),
                    arg1Operand->operandID,
                    buffer,
                    arg2Operand->operandID
                );

                pushOperand(createOperandStruct(instruction->result, resultType));
                appendTAC(currentTacHead, currentTacTail, instruction);

            } else {
                // Arithmetic operators
                if (arg1Operand->operandType == VarType_Int && arg2Operand->operandType == VarType_Int) {
                    snprintf(buffer, 20, "%s.int", expr->data.binOp.operator);
                    resultType = VarType_Int;
                } else if (arg1Operand->operandType == VarType_Float || arg2Operand->operandType == VarType_Float) {
                    //Prevent invalid float operations
                    if (strcmp(expr->data.binOp.operator, "%") == 0)
                    {
                        printf("SEMANTIC: Modulus is unsupported for float values\n");
                        exit(1);
                    }
                    
                    snprintf(buffer, 20, "%s.float", expr->data.binOp.operator);
                    resultType = VarType_Float;

                    if (arg1Operand->operandType == VarType_Int) {
                        convInstruction = createTAC( // Type Conversion
                            createTempVar(VarType_Float),
                            arg1Operand->operandID,
                            "intToFloat",
                            NULL
                        );
                        appendTAC(currentTacHead, currentTacTail, convInstruction);
                        freeOperand(arg1Operand);
                        arg1Operand = createOperandStruct(convInstruction->result, VarType_Float);
                    }
                    if (arg2Operand->operandType == VarType_Int) {
                        convInstruction = createTAC( // Type Conversion
                            createTempVar(VarType_Float),
                            arg2Operand->operandID,
                            "intToFloat",
                            NULL
                        );
                        appendTAC(currentTacHead, currentTacTail, convInstruction);
                        freeOperand(arg2Operand);
                        arg2Operand = createOperandStruct(convInstruction->result, VarType_Float);
                    }
                } else {
                    printf("Unsupported operand types for binary operation\n");
                    exit(1);
                }

                instruction = createTAC(
                    createTempVar(resultType),
                    arg1Operand->operandID,
                    buffer,
                    arg2Operand->operandID
                );

                pushOperand(createOperandStruct(instruction->result, resultType));
                appendTAC(currentTacHead, currentTacTail, instruction);
            }

            freeOperand(arg1Operand);
            freeOperand(arg2Operand);
            break;
        }

        case NodeType_RelOp: {
            // Generate TAC for left and right operands
            // generateTACForExpr(expr->data.relOp.left);
            // generateTACForExpr(expr->data.relOp.right);

            Operand* arg2Operand = popOperand();
            Operand* arg1Operand = popOperand();

            char buffer[20];
            VarType resultType = VarType_Int; // Relational operations result in boolean (int) values

            // Check operand types and do type promotion if necessary
            if (arg1Operand->operandType == VarType_Int && arg2Operand->operandType == VarType_Int) {
                snprintf(buffer, 20, "%s.int", expr->data.relOp.operator);
            } else if (arg1Operand->operandType == VarType_Float || arg2Operand->operandType == VarType_Float) {
                snprintf(buffer, 20, "%s.float", expr->data.relOp.operator);

                if (arg1Operand->operandType == VarType_Int) {
                    convInstruction = createTAC( // Type Conversion
                        createTempVar(VarType_Float),
                        arg1Operand->operandID,
                        "intToFloat",
                        NULL
                    );
                    appendTAC(currentTacHead, currentTacTail, convInstruction);
                    freeOperand(arg1Operand);
                    arg1Operand = createOperandStruct(convInstruction->result, VarType_Float);
                }
                if (arg2Operand->operandType == VarType_Int) {
                    convInstruction = createTAC( // Type Conversion
                        createTempVar(VarType_Float),
                        arg2Operand->operandID,
                        "intToFloat",
                        NULL
                    );
                    appendTAC(currentTacHead, currentTacTail, convInstruction);
                    freeOperand(arg2Operand);
                    arg2Operand = createOperandStruct(convInstruction->result, VarType_Float);
                }
            } else if (arg1Operand->operandType == VarType_Char && arg2Operand->operandType == VarType_Char) {
                snprintf(buffer, 20, "%s.char", expr->data.relOp.operator);
            } else {
                printf("Unsupported operand types for relational operation\n");
                exit(1);
            }

            instruction = createTAC(
                createTempVar(resultType),
                arg1Operand->operandID,
                buffer,
                arg2Operand->operandID
            );

            pushOperand(createOperandStruct(instruction->result, resultType));
            appendTAC(currentTacHead, currentTacTail, instruction);

            freeOperand(arg1Operand);
            freeOperand(arg2Operand);
            break;
        }

        case NodeType_IntExpr: {
            char buffer[20];
            snprintf(buffer, 20, "%d", expr->data.intExpr.number);

            // Assign constant to a temp variable
            char* tempVar = createTempVar(VarType_Int);
            instruction = createTAC(
                tempVar,
                buffer,
                "assign.int",
                NULL
            );
            appendTAC(currentTacHead, currentTacTail, instruction);

            pushOperand(createOperandStruct(tempVar, VarType_Int));
            break;
        }

        case NodeType_FloatExpr: {
            char buffer[20];
            snprintf(buffer, 20, "%f", expr->data.floatExpr.number);

            // Assign constant to a temp variable
            char* tempVar = createTempVar(VarType_Float);
            instruction = createTAC(
                tempVar,
                buffer,
                "assign.float",
                NULL
            );
            appendTAC(currentTacHead, currentTacTail, instruction);

            pushOperand(createOperandStruct(tempVar, VarType_Float));
            break;
        }

        case NodeType_CharExpr: {
            char buffer[20];
            snprintf(buffer, 20, "%c", expr->data.charExpr.character);

            // Assign constant to a temp variable
            char* tempVar = createTempVar(VarType_Char);
            instruction = createTAC(
                tempVar,
                buffer,
                "assign.char",
                NULL
            );
            appendTAC(currentTacHead, currentTacTail, instruction);

            pushOperand(createOperandStruct(tempVar, VarType_Char));
            break;
        }

        case NodeType_SimpleID: {
            SubTable* currentSubTab = peekSubTable(symTabRef);
            Symbol* argSymbol = lookupSymbolInHierarchy(currentSubTab, expr->data.simpleID.name);
            if (!argSymbol) {
                printf("generateTACForExpr(): Variable '%s' not declared (Scope: %p)\n", expr->data.simpleID.name, peekSubTable(symTabRef));
                printSymbolTable(symTabRef);
                exit(1);
            }

            char* op;
            switch (argSymbol->varType) {
                case VarType_Int:
                    op = "load.int";
                    break;
                case VarType_Float:
                    op = "load.float";
                    break;
                case VarType_Char:
                    op = "load.char";
                    break;
                default:
                    printf("Invalid variable type: %s\n", varTypeToString(argSymbol->varType));
                    exit(1);
            }
            VarType resultType = argSymbol->varType;

            instruction = createTAC(
                createTempVar(resultType),
                argSymbol->fullName,
                op,
                NULL
            );

            pushOperand(createOperandStruct(instruction->result, resultType));
            printf("    Pushed new operand %s to the stack\n",instruction->result);
            appendTAC(currentTacHead, currentTacTail, instruction);
            break;
        }

        case NodeType_ArrAccess: {
            Symbol* arrSymbol = lookupSymbolInHierarchy(peekSubTable(symTabRef), expr->data.arrAccess.name);
            if (!arrSymbol) {
                fprintf(stderr, "Array '%s' not declared\n", expr->data.arrAccess.name);
                exit(1);
            }

            // Perform semantic analysis on index expression
            // generateTACForExpr(expr->data.arrAccess.indexExpr);
            Operand* indexOperand = popOperand();

            char* op;
            switch (arrSymbol->varType) {
                case VarType_Int:
                    op = "load.intIndex";
                    break;
                case VarType_Float:
                    op = "load.floatIndex";
                    break;
                case VarType_Char:
                    op = "load.charIndex";
                    break;
                default:
                    printf("Invalid array element type: %s\n", varTypeToString(arrSymbol->varType));
                    exit(1);
            }
            VarType resultType = arrSymbol->varType;

            instruction = createTAC(
                createTempVar(resultType),
                arrSymbol->fullName,
                op,
                indexOperand->operandID
            );

            pushOperand(createOperandStruct(instruction->result, resultType));
            appendTAC(currentTacHead, currentTacTail, instruction);

            freeOperand(indexOperand);
            break;
        }

        // case NodeType_FuncCall:
        //     // Handle function calls
        //     handleFunctionCall(expr);
        //     break;

        default:
            fprintf(stderr, "Unhandled expression type in generateTACForExpr: %d\n", expr->type);
            exit(1);
            break;
    }

    return instruction;
}


// Generate TACs for function call
void generateTACForFuncCall(ASTNode* funcCall) {
    //Copy all argument variables into function parameter variables
    Symbol* funcSymbol = lookupSymbolInHierarchy(peekSubTable(symTabRef), funcCall->data.funcCall.name);
    FuncParam* currentParam = getParamsTail(funcSymbol); //Arguments pop in reverse order-- get end of params list
    printf("paramsTail: %s %s\n", varTypeToString(currentParam->varType), currentParam->refSymbol->name);

    while (currentParam) {
        //Arguments are special expr nodes. Each argument should still be on the stack.
        Operand* argOperand = popOperand();
        printf("argOperand: %s %s\n", varTypeToString(argOperand->operandType), argOperand->operandID);
        printf("currentParam: %s %s\n", varTypeToString(currentParam->varType), currentParam->refSymbol->name);
        if (argOperand->operandType != currentParam->varType)
        {
            printf("SEMANTIC: Parameter-Argument type mismatch, halting...\n");
            exit(1);
        }

        char* operandString;
        switch (argOperand->operandType)
        {
            case (VarType_Int):
                operandString = "load.int";
                break;
            case (VarType_Float):
                operandString = "load.float";
                break;
            case (VarType_Char):
                operandString = "load.char";
                break;
            default:
                printf("SEMANTIC: Invalid argument type, halting...\n");
                exit(1);
                break;
        }

        TAC* argInstr = createTAC(
            currentParam->refSymbol->fullName,     //result
            argOperand->operandID,  //operand 1
            operandString,          //operator
            NULL                    //operand 2
        );
        // appendTAC(&tacHead, &tacTail, argInstr);
        appendTAC(currentTacHead, currentTacTail, argInstr);
        freeOperand(argOperand);
        currentParam = currentParam->prev; //Traverse backwards
    }

    //First, get the return variable's name
    char* result;
    switch(funcSymbol->varType)
    {
        case (VarType_Int):
            result = "returnInt";
            break;
        case (VarType_Float):
            result = "returnFloat";
            break;
        case (VarType_Char):
            result = "returnChar";
            break;
        case (VarType_Void):
            result = NULL;
            break;
        default:
            break;
    }

    //Get the name of the label, used here as an operand
    int labelLength = snprintf(NULL, 0, "%s_func", funcCall->data.funcCall.name); //Get length of const sum so we can allocate appropriate string length
    char* labelName = malloc(labelLength + 1);
    snprintf(labelName, labelLength + 1, "%s_func", funcCall->data.funcCall.name);
    // char* labelName = currentFuncTAC->funcName;

    //Create a return operand and push it to the stack (if return is non-void)
    if (funcSymbol->varType != VarType_Void) 
    {
        pushOperand(createOperandStruct(result, funcSymbol->varType));
    }
    
    //Create and append TAC
    TAC* functionCallTAC = createTAC(
        result,
        labelName,
        "functionCall",
        NULL
    );
    appendTAC(currentTacHead, currentTacTail, functionCallTAC);
}

// Generate TAC for variable assignment
TAC* generateTACForAssign(ASTNode* assignStmt) {
    // Process the right-hand side expression
    // generateTACForExpr(assignStmt->data.assignStmt.expr);
    Operand* rhsOperand = popOperand();

    // Set up any conversions necessary if there is a type mismatch
    SubTable* currentSubTab = peekSubTable(symTabRef);
    Symbol* resultSym = lookupSymbolInHierarchy(currentSubTab, assignStmt->data.assignStmt.varName);
    if (!resultSym) {
        printf("generateTACForAssign(): Variable '%s' not declared (Scope: %p)\n", assignStmt->data.assignStmt.varName, peekSubTable(symTabRef));
        printSymbolTable(symTabRef);
        exit(1);
    }
    VarType resultType = resultSym->varType;

    if ((rhsOperand->operandType == VarType_Int) && (resultType == VarType_Float)) {
        TAC* convInstruction = createTAC(createTempVar(VarType_Float), rhsOperand->operandID, "intToFloat", NULL); // Type Conversion
        appendTAC(currentTacHead, currentTacTail, convInstruction);
        freeOperand(rhsOperand);
        rhsOperand = createOperandStruct(convInstruction->result, VarType_Float);
    } else if ((rhsOperand->operandType == VarType_Float) && (resultType == VarType_Int)) {
        TAC* convInstruction = createTAC(createTempVar(VarType_Int), rhsOperand->operandID, "floatToInt", NULL); // Type Conversion
        appendTAC(currentTacHead, currentTacTail, convInstruction);
        freeOperand(rhsOperand);
        rhsOperand = createOperandStruct(convInstruction->result, VarType_Int);
    }

    char* operatorString;
    switch (resultType) {
        case VarType_Int:
            operatorString = "store.int";
            break;
        case VarType_Float:
            operatorString = "store.float";
            break;
        case VarType_Char:
            operatorString = "store.char";
            break;
        default:
            break;
    }

   // Generate TAC
    TAC* instruction = createTAC(
        resultSym->fullName,
        rhsOperand->operandID,
        operatorString,
        NULL
    );

    appendTAC(currentTacHead, currentTacTail, instruction);
    freeOperand(rhsOperand);

    printf("Completed assign statement for %s\n",instruction->result);

    return instruction;
}


// Generate TAC for array assignment
TAC* generateTACForAssignArr(ASTNode* assignArrStmt) {
    Operand* rhsOperand = popOperand();
    Operand* indexOperand = popOperand();

    //Set up any conversions necessary if there is a type mismatch
    Symbol* resultSym = lookupSymbolInHierarchy(peekSubTable(symTabRef), assignArrStmt->data.assignArrStmt.varName);
    VarType resultType = resultSym->varType;
    if ((rhsOperand->operandType == VarType_Int) && (resultType == VarType_Float))
    {
        TAC* convInstruction = createTAC(  //Type Conversion
            createTempVar(VarType_Float),
            rhsOperand->operandID,
            "intToFloat",
            NULL
        );
        appendTAC(currentTacHead, currentTacTail, convInstruction);
        freeOperand(rhsOperand);
        rhsOperand = createOperandStruct(convInstruction->result, VarType_Float);
    }
    else if ((rhsOperand->operandType == VarType_Float) && (resultType == VarType_Int))
    {
        TAC* convInstruction = createTAC(  //Type Conversion
            createTempVar(VarType_Int),
            rhsOperand->operandID,
            "floatToInt", NULL
        );
        appendTAC(currentTacHead, currentTacTail, convInstruction);
        freeOperand(rhsOperand);
        rhsOperand = createOperandStruct(convInstruction->result, VarType_Int);
    }

    char* operatorString;
    switch (rhsOperand->operandType)
    {
        case (VarType_Int):
            operatorString = "store.intIndex";
            break;
        case (VarType_Float):
            operatorString = "store.floatIndex";
            break;
        case (VarType_Char):
            operatorString = "store.charIndex";
            break;
        default:
            break;
    }

    TAC* instruction = createTAC(
        resultSym->fullName,
        rhsOperand->operandID,
        operatorString,
        indexOperand->operandID
    );

    // appendTAC(&tacHead, &tacTail, instruction);
    appendTAC(currentTacHead, currentTacTail, instruction);
    freeOperand(rhsOperand);
    freeOperand(indexOperand);

    return instruction;
}

// Generate TAC for write statements
TAC* generateTACForWrite(ASTNode* expr) {

    // Generate TAC for the expression to be written
    // generateTACForExpr(expr->data.writeStmt.expr);

    // Get the result of the most recent expr evaluation
    Operand* writeOperand = popOperand();

    char* writeOp;
    switch (writeOperand->operandType) {
        case VarType_Int:
            writeOp = "write.int";
            break;
        case VarType_Float:
            writeOp = "write.float";
            break;
        case VarType_Char:
            writeOp = "write.char";
            break;
        default:
            printf("Invalid expr type in write expr: %s\n", varTypeToString(writeOperand->operandType));
            break;
    }

    // Create TAC for write instruction
    TAC* writeInstr = createTAC(
        NULL,
        writeOperand->operandID,
        writeOp,
        NULL
    );

    appendTAC(currentTacHead, currentTacTail, writeInstr);

    freeOperand(writeOperand);

    return writeInstr;
}


// Function to retrieve expression type based on ASTNode
VarType getExprType(ASTNode* expr) {
    switch (expr->type) {
        case NodeType_IntExpr:
            return VarType_Int;

        case NodeType_FloatExpr:
            return VarType_Float;

        case NodeType_CharExpr:
            return VarType_Char;

        case NodeType_SimpleID: {
            Symbol* varSymbol = lookupSymbolInHierarchy(peekSubTable(symTabRef), expr->data.simpleID.name);
            if (!varSymbol) {
                printf("getExprType(): Variable '%s' not declared (Scope: %p)\n", expr->data.simpleID.name, peekSubTable(symTabRef));
                printSymbolTable(symTabRef);
                exit(1);
            }
            return varSymbol->varType;
        }

        case NodeType_ArrAccess: {
            Symbol* arrSymbol = lookupSymbolInHierarchy(peekSubTable(symTabRef), expr->data.arrAccess.name);
            if (!arrSymbol) {
                fprintf(stderr, "Array '%s' not declared\n", expr->data.arrAccess.name);
                exit(1);
            }
            return arrSymbol->varType;
        }

        case NodeType_UnaryOp:
            return determineUnaryOpType(expr);

        case NodeType_BinOp:
            return determineBinOpType(expr);

        case NodeType_RelOp:
            return VarType_Int; // Relational operators result in boolean (int) values

        case NodeType_FuncCall: {
            Symbol* funcReturnType = lookupSymbolInHierarchy(peekSubTable(symTabRef), expr->data.funcCall.name);
            if (!funcReturnType) {
                fprintf(stderr, "Function '%s' not declared\n", expr->data.funcCall.name);
                exit(1);
            }
            return funcReturnType->varType;
        }

        default:
            fprintf(stderr, "Invalid node type in getExprType: %d\n", expr->type);
            exit(1);
    }
}

// Determine type for binary operations
VarType determineUnaryOpType(ASTNode* expr) {
    return getExprType(expr->data.unaryOp.expr);
}

// Determine type for binary operations
VarType determineBinOpType(ASTNode* expr) {
    VarType leftType = getExprType(expr->data.binOp.left);
    VarType rightType = getExprType(expr->data.binOp.right);

    if (leftType == VarType_Error || rightType == VarType_Error) {
        return VarType_Error;
    }

    if (strcmp(expr->data.binOp.operator, "&&") == 0 || strcmp(expr->data.binOp.operator, "||") == 0) {
        // Logical operators result in boolean (int) values
        return VarType_Int;
    }

    if (leftType == VarType_Float || rightType == VarType_Float) {
        return VarType_Float;
    }

    return VarType_Int;
}


// Get the count of temporary integer variables
int getTempIntCount() {
    return tempIntCount;
}

// Get the count of temporary float variables
int getTempFloatCount() {
    return tempFloatCount;
}

// Get the count of temporary char variables
int getTempCharCount() {
    return tempCharCount;
}

// Print TAC to the console
void printTAC(TAC* tac) {
    if (!tac) return;
    printf("%s = %s %s %s\n", tac->result ? tac->result : "(null)",
           tac->arg1 ? tac->arg1 : "(null)",
           tac->op ? tac->op : "(null)",
           tac->arg2 ? tac->arg2 : "(null)");
}

// Print TAC to a file
void printTACToFile(const char* filename, TAC* tac) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    TAC* current = tac;
    while (current) {
        fprintf(file, "%s = %s %s %s\n", current->result ? current->result : "(null)",
                current->arg1 ? current->arg1 : "(null)",
                current->op ? current->op : "(null)",
                current->arg2 ? current->arg2 : "(null)");
        current = current->next;
    }
    fclose(file);
    printf("TAC written to %s\n", filename);
}

// Print Function TACs to a file
void printFuncTACsToFile() {
    int functionNum = 0;
    FuncTAC* currentFunc = funcTacHeads; //Get the start of all func TACs

    while(currentFunc) {
        //Allocate space for filename, and print the name to the allocated buffer
        int filenameLength = snprintf(NULL, 0, "output/FunctionTAC%d.ir", functionNum); //Get length of const sum so we can allocate appropriate string length
	    char* filename = malloc(filenameLength + 1);
        snprintf(filename, filenameLength + 1, "output/FunctionTAC%d.ir", functionNum);
        //Create file with generated name
        FILE* file = fopen(filename, "w");
        if (!file) {
            perror("Failed to open file");
            return;
        }
        //Iterate through each TAC in the current function TAC list
        TAC* currentTAC = currentFunc->func;
        printf("==Function %d TAC==\n", functionNum);
        // printf("currentTAC->next: %d\n", currentTAC->next);
        while (currentTAC) {
            fprintf(file, "%s = %s %s %s\n", currentTAC->result ? currentTAC->result : "(null)",
                    currentTAC->arg1 ? currentTAC->arg1 : "(null)",
                    currentTAC->op ? currentTAC->op : "(null)",
                    currentTAC->arg2 ? currentTAC->arg2 : "(null)");
            printTAC(currentTAC);
            currentTAC = currentTAC->next;
        }
        fclose(file);
        printf("Function TAC written to %s\n", filename);

        //Go to the next function, if it exists
        currentFunc = currentFunc->nextFunc;
        functionNum++;
    }
}

// Destroy a TAC and re-link list
void removeTAC(TAC** del) {
    if (!*del) return;

    if (tacHead == (*del)) {
        tacHead = (*del)->next;
        if (tacHead) tacHead->prev = NULL;
    } else {
        (*del)->prev->next = (*del)->next;
    }
    if (tacTail == (*del)) {
        tacTail = (*del)->prev;
        if (tacTail) tacTail->next = NULL;
    } else {
        (*del)->next->prev = (*del)->prev;
    }
    freeTAC(del);
}

// Free the memory of a TAC
void freeTAC(TAC** del) {
    if (!*del) return;
    if ((*del)->arg1) free((*del)->arg1);
    if ((*del)->arg2) free((*del)->arg2);
    if ((*del)->op) free((*del)->op);
    if ((*del)->result) free((*del)->result);
    free(*del);
    *del = NULL;
}

// Replace a TAC in the list
void replaceTAC(TAC** oldTAC, TAC** newTAC) {
    if (!*oldTAC || !*newTAC) return;

    if (tacHead == (*oldTAC)) {
        tacHead = (*newTAC);
    } else {
        (*oldTAC)->prev->next = (*newTAC);
    }
    if (tacTail == (*oldTAC)) {
        tacTail = (*newTAC);
    } else {
        (*oldTAC)->next->prev = (*newTAC);
    }

    (*newTAC)->prev = (*oldTAC)->prev;
    (*newTAC)->next = (*oldTAC)->next;

    freeTAC(oldTAC);
}

void initFuncTAC(char* funcName, VarType returnType) {
    //  It shouldn't be possible for this to run while already in a function TAC
    // Should that ever change, insert a check to see if we're in global scope
    // at the start.

    //Generate the label name of the function
    int labelLength = snprintf(NULL, 0, "%s_func", funcName); //Get length of const sum so we can allocate appropriate string length
    char* labelName = malloc(labelLength + 1);
    snprintf(labelName, labelLength + 1, "%s_func", funcName);

    //Create new FuncTAC struct for head
    FuncTAC* newFuncTacHead = malloc(sizeof(FuncTAC));
    newFuncTacHead->func = NULL;
    newFuncTacHead->nextFunc = NULL;
    newFuncTacHead->funcName = labelName;
    newFuncTacHead->returnType = returnType;
    newFuncTacHead->returnsValue = false;
    
    //Create new FuncTAC struct for head
    FuncTAC* newFuncTacTail = malloc(sizeof(FuncTAC));
    newFuncTacTail->func = NULL;
    newFuncTacTail->nextFunc = NULL;
    newFuncTacTail->funcName = labelName;
    newFuncTacTail->returnType = returnType;
    // newFuncTacTail->returnType = false; //Should be unused

    // Append to existing lists
    //  TODO: Might start tracking the tail of the FuncTAC lists. Doing so would
    //      reduce the time complexity of the following tail insertion from O(n)
    //      down to O(1).
    if (funcTacHeads) {
        FuncTAC** currentHead = &funcTacHeads;  //Cursor at start of linked lists
        FuncTAC** currentTail = &funcTacTails;
        while ((*currentHead)->nextFunc) {
            currentHead = &((*currentHead)->nextFunc);  //Traverse to end of linked lists
            currentTail = &((*currentTail)->nextFunc);
        }
        (*currentHead)->nextFunc = newFuncTacHead;  //Insert new TAC at end of lists
        (*currentTail)->nextFunc = newFuncTacTail;
    }
    else
    {
        //First function TAC generated, set up linked lists
        funcTacHeads = newFuncTacHead;
        funcTacTails = newFuncTacTail;
    }

    // Set up the new TAC to be modified by other functions
    currentTacHead = &(newFuncTacHead->func); 
    currentTacTail = &(newFuncTacTail->func); 
    
    // Used for easy access to function name
    currentFuncTAC = newFuncTacHead;

    //Every functionTAC should start with "funcStart"
    //  This operation signals MIPS to push the address in $ra to the stack
    //  This is crucial for returning after a function call
    TAC* startInstr = createTAC(
        NULL,
        NULL,
        "funcStart",
        NULL
    );
    appendTAC(currentTacHead, currentTacTail, startInstr);

    inFunction = true;
}

void finalizeFuncTAC() {
    //If non-void function hasn't returned a value, throw an error
    if ((currentFuncTAC->returnType != VarType_Void) && (!currentFuncTAC->returnsValue))
    {
        printf("SEMANTIC: Non-void function %s has no return statement! Halting...\n", currentFuncTAC->funcName);
        exit(1);
    }
    
    //Every functionTAC should end with "return"
    //  This operation signals MIPS to pop a return address from the stack and jump to it
    TAC* returnInstr = createTAC(
        NULL,
        NULL,
        "return",
        NULL
    );
    appendTAC(currentTacHead, currentTacTail, returnInstr);

    currentTacHead = &tacHead;
    currentTacTail = &tacTail;
    currentFuncTAC = NULL;
    inFunction = false;
}
