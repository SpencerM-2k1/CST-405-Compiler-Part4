#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "AST.h"

// Function to print indentation and branch lines
void printIndent(bool* drawVertical, int level) {
    for (int i = 0; i < level; i++) {
        if (drawVertical[i]) {
            printf("|   ");
        } else {
            printf("    ");
        }
    }
}

// Modified traverseAST function
void traverseAST(ASTNode* node, int level, bool* drawVertical, bool isLast) {
    if (!node) {
        return;
    }
    // Print indentation
    printIndent(drawVertical, level - 1);

    // Choose the appropriate branch symbol
    if (level > 0) {
        printf(isLast ? "└── " : "├── ");
    }

    int numChildren = 0;
    int childIndex = 0;

    // Display the node type and relevant information
    switch (node->type) {
        case NodeType_Program:
            printf("Program\n");

            // Count the number of children
            numChildren = 0;
            if (node->data.program.varDeclList) numChildren++;
            if (node->data.program.stmtList) numChildren++;

            childIndex = 0;
            drawVertical[level] = !isLast;
            if (node->data.program.varDeclList) {
                traverseAST(node->data.program.varDeclList, level + 1, drawVertical, ++childIndex == numChildren);
            }
            if (node->data.program.stmtList) {
                traverseAST(node->data.program.stmtList, level + 1, drawVertical, ++childIndex == numChildren);
            }
            break;

        case NodeType_DeclList:
            printf("DeclList\n");

            numChildren = 0;
            if (node->data.declList.decl) numChildren++;
            if (node->data.declList.next) numChildren++;

            childIndex = 0;
            drawVertical[level - 1] = !isLast;
            if (node->data.declList.decl) {
                traverseAST(node->data.declList.decl, level + 1, drawVertical, ++childIndex == numChildren);
            }
            if (node->data.declList.next) {
                traverseAST(node->data.declList.next, level + 1, drawVertical, ++childIndex == numChildren);
            }
            break;

        case NodeType_VarDeclList:
            printf("VarDeclList\n");

            numChildren = 0;
            if (node->data.varDeclList.varDecl) numChildren++;
            if (node->data.varDeclList.next) numChildren++;

            childIndex = 0;
            drawVertical[level - 1] = !isLast;
            if (node->data.varDeclList.varDecl) {
                traverseAST(node->data.varDeclList.varDecl, level + 1, drawVertical, ++childIndex == numChildren);
            }
            if (node->data.varDeclList.next) {
                traverseAST(node->data.varDeclList.next, level + 1, drawVertical, ++childIndex == numChildren);
            }
            break;

        case NodeType_VarDecl:
            printf("VarDecl: %s %s\n", node->data.varDecl.varType, node->data.varDecl.varName);
            break;

        case NodeType_ArrDecl:
            printf("ArrDecl: array %s %s[%d]\n", node->data.arrDecl.varType, node->data.arrDecl.varName, node->data.arrDecl.arrSize);
            break;

        case NodeType_FuncDecl:
            printf("FuncDecl: %s %s (SubTable: %p)\n", varTypeToString(node->data.funcDecl.returnType), node->data.funcDecl.name, node->data.funcDecl.funcSubTable);

            numChildren = 0;
            if (node->data.funcDecl.paramList) numChildren++;
            if (node->data.funcDecl.varDeclList) numChildren++;
            if (node->data.funcDecl.stmtList) numChildren++;

            childIndex = 0;
            drawVertical[level - 1] = !isLast;
            if (node->data.funcDecl.paramList) {
                traverseAST(node->data.funcDecl.paramList, level + 1, drawVertical, ++childIndex == numChildren);
            }
            if (node->data.funcDecl.varDeclList) {
                traverseAST(node->data.funcDecl.varDeclList, level + 1, drawVertical, ++childIndex == numChildren);
            }
            if (node->data.funcDecl.stmtList) {
                traverseAST(node->data.funcDecl.stmtList, level + 1, drawVertical, ++childIndex == numChildren);
            }
            break;

        case NodeType_ParamList:
            printf("ParamList\n");

            numChildren = 0;
            if (node->data.paramList.param) numChildren++;
            if (node->data.paramList.next) numChildren++;

            childIndex = 0;
            drawVertical[level - 1] = !isLast;
            if (node->data.paramList.param) {
                traverseAST(node->data.paramList.param, level + 1, drawVertical, ++childIndex == numChildren);
            }
            if (node->data.paramList.next) {
                traverseAST(node->data.paramList.next, level + 1, drawVertical, ++childIndex == numChildren);
            }
            break;

        case NodeType_Param:
            printf("Param: %s %s\n", varTypeToString(node->data.param.type), node->data.param.name);
            break;

        case NodeType_IntExpr:
            printf("IntExpr: %d\n", node->data.intExpr.number);
            break;

        case NodeType_FloatExpr:
            printf("FloatExpr: %f\n", node->data.floatExpr.number);
            break;

        case NodeType_CharExpr:
            printf("CharExpr: %c\n", node->data.charExpr.character);
            break;

        case NodeType_SimpleID:
            printf("SimpleID: %s\n", node->data.simpleID.name);
            break;

        case NodeType_ArrAccess:
            printf("ArrAccess: %s\n", node->data.arrAccess.name);
            traverseAST(node->data.arrAccess.indexExpr, level + 1, drawVertical, true);
            break;

        case NodeType_FuncCall:
            printf("FuncCall: %s()\n", node->data.funcCall.name);

            drawVertical[level - 1] = !isLast;
            if (node->data.funcCall.argList) {
                traverseAST(node->data.funcCall.argList, level + 1, drawVertical, true);
            }
            break;

        case NodeType_ArgList:
            printf("ArgList\n");

            numChildren = 0;
            if (node->data.argList.arg) numChildren++;
            if (node->data.argList.next) numChildren++;

            childIndex = 0;
            drawVertical[level - 1] = !isLast;
            if (node->data.argList.arg) {
                traverseAST(node->data.argList.arg, level + 1, drawVertical, ++childIndex == numChildren);
            }
            if (node->data.argList.next) {
                traverseAST(node->data.argList.next, level + 1, drawVertical, ++childIndex == numChildren);
            }
            break;

        case NodeType_Arg:
            printf("Arg\n");
            drawVertical[level - 1] = !isLast;
            traverseAST(node->data.arg.expr, level + 1, drawVertical, true);
            break;

        case NodeType_ReturnStmt:
            if (node->data.returnStmt.returnExpr) {
                printf("ReturnStmt\n");
                traverseAST(node->data.returnStmt.returnExpr, level + 1, drawVertical, true);
            } else {
                printf("ReturnStmt (empty)\n");
            }
            break;

        case NodeType_UnaryOp:
            printf("Expr (unary): %s\n", node->data.unaryOp.operator);
            traverseAST(node->data.unaryOp.expr, level + 1, drawVertical, true);
            break;

        case NodeType_BinOp:
            printf("Expr: %s\n", node->data.binOp.operator);
            drawVertical[level - 1] = !isLast;
            traverseAST(node->data.binOp.left, level + 1, drawVertical, false);
            traverseAST(node->data.binOp.right, level + 1, drawVertical, true);
            break;

        case NodeType_StmtList:
            numChildren = 0;
            if (node->data.stmtList.stmt) numChildren++;
            if (node->data.stmtList.stmtList) numChildren++;

            if (node->data.stmtList.stmt != NULL) {
                printf("StmtList\n");
                childIndex = 0;
                drawVertical[level - 1] = !isLast;
                if (node->data.stmtList.stmt) {
                    traverseAST(node->data.stmtList.stmt, level + 1, drawVertical, ++childIndex == numChildren);
                }
                if (node->data.stmtList.stmtList) {
                    traverseAST(node->data.stmtList.stmtList, level + 1, drawVertical, ++childIndex == numChildren);
                }
            } else {
                printf("StmtList - END\n");
            }
            break;

        case NodeType_AssignStmt:
            printf("AssignStmt: %s %s\n", node->data.assignStmt.varName, node->data.assignStmt.operator);

            drawVertical[level - 1] = !isLast;
            traverseAST(node->data.assignStmt.expr, level + 1, drawVertical, true);
            break;

        case NodeType_AssignArrStmt:
            printf("AssignArrStmt: %s[] %s\n", node->data.assignArrStmt.varName, node->data.assignArrStmt.operator);

            drawVertical[level - 1] = !isLast;
            traverseAST(node->data.assignArrStmt.indexExpr, level + 1, drawVertical, false);
            traverseAST(node->data.assignArrStmt.expr, level + 1, drawVertical, true);
            break;

        case NodeType_WriteStmt:
            printf("WriteStmt\n");
            drawVertical[level - 1] = !isLast;
            traverseAST(node->data.writeStmt.expr, level + 1, drawVertical, true);
            break;

        case NodeType_IfStmt:
            printf("IfStmt\n");

            numChildren = 2; // condition and thenStmt are always present
            if (node->data.ifStmt.elseStmt) numChildren++;

            childIndex = 0;
            drawVertical[level - 1] = !isLast;

            // Traverse condition
            // printf("Condition:\n");
            traverseAST(node->data.ifStmt.condition, level + 1, drawVertical, ++childIndex == numChildren);

            // Traverse thenStmt
            // printf("Then:\n");
            traverseAST(node->data.ifStmt.thenStmt, level + 1, drawVertical, ++childIndex == numChildren);

            // Traverse elseStmt if present
            if (node->data.ifStmt.elseStmt) {
                // printf("Else:\n");
                traverseAST(node->data.ifStmt.elseStmt, level + 1, drawVertical, ++childIndex == numChildren);
            }
            break;

        case NodeType_WhileStmt:
            printf("WhileStmt\n");


            drawVertical[level - 1] = !isLast;

            // Traverse condition
            // printf("Condition:\n");
            traverseAST(node->data.whileStmt.condition, level + 1, drawVertical, false);

            // Traverse block
            // printf("Block:\n");
            traverseAST(node->data.whileStmt.block, level + 1, drawVertical, true);
            break;

        case NodeType_BreakStmt:
            printf("BreakStmt\n");
            break;

        case NodeType_RelOp:
            printf("RelOp: %s\n", node->data.relOp.operator);
            drawVertical[level - 1] = !isLast;
            traverseAST(node->data.relOp.left, level + 1, drawVertical, false);
            traverseAST(node->data.relOp.right, level + 1, drawVertical, true);
            break;

        default:
            printf("Unknown Node Type (type: %d)\n", node->type);
            break;
    }
}

void freeAST(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NodeType_Program:
            freeAST(node->data.program.varDeclList);
            freeAST(node->data.program.stmtList);
            break;

        case NodeType_DeclList:
            freeAST(node->data.declList.decl);
            freeAST(node->data.declList.next);
            break;

        case NodeType_VarDeclList:
            freeAST(node->data.varDeclList.varDecl);
            freeAST(node->data.varDeclList.next);
            break;

        case NodeType_VarDecl:
            free(node->data.varDecl.varType);
            free(node->data.varDecl.varName);
            break;

        case NodeType_ArrDecl:
            free(node->data.arrDecl.varType);
            free(node->data.arrDecl.varName);
            break;

        case NodeType_FuncDecl:
            free(node->data.funcDecl.name);
            freeAST(node->data.funcDecl.paramList);
            freeAST(node->data.funcDecl.varDeclList);
            freeAST(node->data.funcDecl.stmtList);
            break;

        case NodeType_ParamList:
            freeAST(node->data.paramList.param);
            freeAST(node->data.paramList.next);
            break;

        case NodeType_Param:
            free(node->data.param.name);
            break;

        case NodeType_IntExpr:
            // No dynamic memory to free
            break;

        case NodeType_FloatExpr:
            // No dynamic memory to free
            break;
        
        case NodeType_CharExpr:
            // No dynamic memory to free
            break;

        case NodeType_SimpleID:
            free(node->data.simpleID.name);
            break;

        case NodeType_ArrAccess:
            free(node->data.arrAccess.name);
            freeAST(node->data.arrAccess.indexExpr);
            break;

        case NodeType_FuncCall:
            free(node->data.funcCall.name);
            freeAST(node->data.funcCall.argList);
            break;

        case NodeType_ArgList:
            freeAST(node->data.argList.arg);
            freeAST(node->data.argList.next);
            break;

        case NodeType_Arg:
            freeAST(node->data.arg.expr);
            break;

        case NodeType_ReturnStmt:
            freeAST(node->data.returnStmt.returnExpr);
            break;

        case NodeType_UnaryOp:
            free(node->data.unaryOp.operator);
            freeAST(node->data.unaryOp.expr);
            break;
        
        case NodeType_BinOp:
            free(node->data.binOp.operator);
            freeAST(node->data.binOp.left);
            freeAST(node->data.binOp.right);
            break;

        case NodeType_StmtList:
            freeAST(node->data.stmtList.stmt);
            freeAST(node->data.stmtList.stmtList);
            break;

        case NodeType_AssignStmt:
            free(node->data.assignStmt.operator);
            free(node->data.assignStmt.varName);
            freeAST(node->data.assignStmt.expr);
            break;

        case NodeType_AssignArrStmt:
            free(node->data.assignArrStmt.operator);
            free(node->data.assignArrStmt.varName);
            freeAST(node->data.assignArrStmt.indexExpr);
            freeAST(node->data.assignArrStmt.expr);
            break;

        case NodeType_WriteStmt:
            freeAST(node->data.writeStmt.expr);
            break;

        case NodeType_IfStmt:
            freeAST(node->data.ifStmt.condition);
            freeAST(node->data.ifStmt.thenStmt);
            freeAST(node->data.ifStmt.elseStmt);
            break;
        
        // Added case for NodeType_WriteStmt
        case NodeType_WhileStmt:
            freeAST(node->data.whileStmt.condition);
            freeAST(node->data.whileStmt.block);
            freeAST(node->data.whileStmt.blockSubTab);
            break;

        default:
            break;
    }

    free(node);
}

ASTNode* createNode(NodeType type) {
    ASTNode* newNode = (ASTNode*)malloc(sizeof(ASTNode));
    if (newNode == NULL) {
        // Handle memory allocation failure if needed
        return NULL;
    }

    newNode->type = type;

    // Initialize the node based on its type
    switch (type) {
        case NodeType_Program:
            newNode->data.program.varDeclList = NULL;
            newNode->data.program.stmtList = NULL;
            break;

        case NodeType_DeclList:
            newNode->data.declList.decl = NULL;
            newNode->data.declList.next = NULL;
            break;

        case NodeType_VarDeclList:
            newNode->data.varDeclList.varDecl = NULL;
            newNode->data.varDeclList.next = NULL;
            break;

        case NodeType_VarDecl:
            newNode->data.varDecl.varType = NULL;
            newNode->data.varDecl.varName = NULL;
            break;

        case NodeType_ArrDecl:
            newNode->data.arrDecl.arrSize = 0;
            newNode->data.arrDecl.varName = NULL;
            newNode->data.arrDecl.varType = NULL;
            break;

        case NodeType_FuncDecl:
            newNode->data.funcDecl.name = NULL;
            newNode->data.funcDecl.returnType = VarType_Error;
            newNode->data.funcDecl.paramList = NULL;
            newNode->data.funcDecl.varDeclList = NULL;
            newNode->data.funcDecl.stmtList = NULL;
            break;

        case NodeType_ParamList:
            newNode->data.paramList.param = NULL;
            newNode->data.paramList.next = NULL;
            break;

        case NodeType_Param:
            newNode->data.param.type = VarType_Error;
            newNode->data.param.name = NULL;
            break;

        case NodeType_IntExpr:
            newNode->data.intExpr.number = 0;
            break;

        case NodeType_FloatExpr:
            newNode->data.floatExpr.number = 0.0;
            break;
        
        case NodeType_CharExpr:
            newNode->data.charExpr.character = 'A';
            break;

        case NodeType_SimpleID:
            newNode->data.simpleID.name = NULL;
            break;

        case NodeType_ArrAccess:
            newNode->data.arrAccess.indexExpr = NULL;
            newNode->data.arrAccess.name = NULL;
            break;

        case NodeType_FuncCall:
            newNode->data.funcCall.name = NULL;
            newNode->data.funcCall.argList = NULL;
            newNode->data.funcCall.ignoreReturn = false;
            break;

        case NodeType_ArgList:
            newNode->data.argList.arg = NULL;
            newNode->data.argList.next = NULL;
            break;

        case NodeType_Arg:
            newNode->data.arg.expr = NULL;
            break;

        case NodeType_ReturnStmt:
            newNode->data.returnStmt.returnExpr = NULL;
            break;

        case NodeType_UnaryOp:
            newNode->data.unaryOp.operator = NULL;
            newNode->data.unaryOp.expr = NULL;
            break;

        case NodeType_BinOp:
            newNode->data.binOp.operator = NULL;
            newNode->data.binOp.left = NULL;
            newNode->data.binOp.right = NULL;
            break;

        case NodeType_StmtList:
            newNode->data.stmtList.stmt = NULL;
            newNode->data.stmtList.stmtList = NULL;
            break;

        case NodeType_AssignStmt:
            newNode->data.assignStmt.operator = NULL;
            newNode->data.assignStmt.varName = NULL;
            newNode->data.assignStmt.expr = NULL;
            break;

        case NodeType_AssignArrStmt:
            newNode->data.assignArrStmt.operator = NULL;
            newNode->data.assignArrStmt.varName = NULL;
            newNode->data.assignArrStmt.expr = NULL;
            newNode->data.assignArrStmt.indexExpr = NULL;
            break;

        case NodeType_WriteStmt:
            newNode->data.writeStmt.expr = NULL;
            break;

        case NodeType_IfStmt:
            newNode->data.ifStmt.condition = NULL;
            newNode->data.ifStmt.thenStmt = NULL;
            newNode->data.ifStmt.elseStmt = NULL;
            break;
        
        // Added initialization for NodeType_WriteStmt
        case NodeType_WhileStmt:
            newNode->data.whileStmt.condition = NULL;
            newNode->data.whileStmt.block = NULL;
            newNode->data.whileStmt.blockSubTab = NULL;
            break;
        
        //Dummy case to prevent unnecessary error (breakStmt has no member vars)
        case NodeType_BreakStmt:
            break;

        default:
            printf("DEBUG: Invalid NodeType\n");
            break;
    }

    return newNode;
}

