%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "AST.h"
#include "symbolTable.h"
#include "semantic.h"
#include "codeGenerator.h"
#include "optimizer.h"
#include "commons/types.h"

#define TABLE_SIZE 100
#define MAX_ID_LENGTH 10
#define VAR_SUFFIX_LENGTH 4

bool drawVertical[100] = { false }; // Adjust size as needed

extern int yylex();   // Declare yylex, the lexer function
extern int yyparse(); // Declare yyparse, the parser function
extern FILE* yyin;    // Declare yyin, the file pointer for the input file
extern int yylineno;  // Declare yylineno, the line number counter
extern TAC* tacHead;  // Declare the head of the linked list of TAC entries

void yyerror(const char* s);

extern int chars;
extern int lines;

ASTNode* root = NULL;
SymbolTable* symTab = NULL;
Symbol* symbol = NULL;

char* currentFunction = NULL; 	// Name of current function-- used for scope
								// NULL when not in a function
%}

%union {
    char* sval;
    int intVal;
    float floatVal;
	char charVal;
    struct ASTNode* ast;
}

%token <sval> TYPE
%token <sval> ID
%token SEMI
%token <sval> ASSIGN
%token <intVal> INT_NUMBER
%token <floatVal> FLOAT_NUMBER
%token <charVal> CHAR_VALUE
%token CONST_TRUE CONST_FALSE
%token WRITE
%token ARRAY
%token RETURN
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET COMMA

%token IF ELSE ELIF
%token WHILE BREAK
%left <sval> NOT AND OR
%nonassoc <sval> GREATER_THAN LESS_THAN EQUAL_EQUAL NOT_EQUAL GREATER_EQUAL LESS_EQUAL 

%left <sval> PLUS MINUS
%left <sval> MULTIPLY DIVIDE MOD

%type <ast> Program VarDecl VarDeclInit VarDeclList DeclList Stmt StmtList Expr
%type <ast> FuncDecl ParamList Param FuncCall ArgList Arg ReturnStmt
%type <ast> IfStmt ElifList Block
%type <ast> WhileStmt BreakStmt

%start Program

%%

Program: DeclList StmtList
    {
        printf("The PARSER has started\n");
        root = createNode(NodeType_Program);
        root->data.program.varDeclList = $1;
        root->data.program.stmtList = $2;
    }
;

DeclList:
    /* empty */
    {
        $$ = NULL;
    }
    | VarDecl DeclList
    {
        printf("PARSER: Recognized declaration list (variable entry)\n");
        $$ = createNode(NodeType_DeclList);
        $$->data.declList.decl = $1;
        $$->data.declList.next = $2;
    }
    | VarDeclInit DeclList
    {
        printf("PARSER: Recognized declaration list (variable entry with initialization)\n");
        $$ = createNode(NodeType_DeclList);
        $$->data.declList.decl = $1;
        $$->data.declList.next = $2;
    }
    | FuncDecl DeclList
    {
        printf("PARSER: Recognized declaration list (function entry)\n");
        $$ = createNode(NodeType_DeclList);
        $$->data.declList.decl = $1;
        $$->data.declList.next = $2;
    }
;

VarDeclList:
    /* empty */
    {
        $$ = NULL;
    }
    | VarDecl VarDeclList
    {
        printf("PARSER: Recognized function-scoped variable declaration list\n");
        $$ = createNode(NodeType_VarDeclList);
        $$->data.varDeclList.varDecl = $1;
        $$->data.varDeclList.next = $2;
    }
;

VarDecl:
    TYPE ID SEMI
    {
        printf("PARSER: Recognized variable declaration: %s\n", $2);
        printf("PARSER: Printing symbol table\n");
        printSymbolTable(symTab);
        printf("PARSER: Checking if variable has already been declared\n");

        char* varName = strdup($2);
        printf("Name with suffix: %s\n", varName);

        symbol = lookupSymbolInCurrentScope(symTab, varName);

        if (symbol != NULL)
        {
            printf("PARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n", $2, yylineno);
            exit(0);
        }
        else
        {
            $$ = createNode(NodeType_VarDecl);
            $$->data.varDecl.varType = strdup($1);
            $$->data.varDecl.varName = strdup(varName);

            addSymbol(symTab, varName, $1);
            printSymbolTable(symTab);
        }
    }
    /* | TYPE ID ASSIGN Expr SEMI
    {
        printf("PARSER: Recognized variable declaration with initialization: %s\n", $2);

        // Check if variable has already been declared
        char* varName = strdup($2);
        symbol = lookupSymbolInCurrentScope(symTab, varName);

        if (symbol != NULL)
        {
            printf("PARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n", $2, yylineno);
            exit(0);
        }
        else
        {
            // Declare the variable
            ASTNode* varDeclNode = createNode(NodeType_VarDecl);
            varDeclNode->data.varDecl.varType = strdup($1);
            varDeclNode->data.varDecl.varName = strdup(varName);

            addSymbol(symTab, varName, $1);
            printSymbolTable(symTab);

            // Create an assignment statement for initialization
            ASTNode* assignStmtNode = createNode(NodeType_AssignStmt);
            assignStmtNode->data.assignStmt.varName = strdup(varName);
            assignStmtNode->data.assignStmt.operator = strdup($3);
            assignStmtNode->data.assignStmt.expr = $4;

            // Combine declaration and assignment into a VarDeclInit node
            ASTNode* varDeclInitNode = createNode(NodeType_VarDeclInit);
            varDeclInitNode->data.varDeclInit.varDecl = varDeclNode;
            varDeclInitNode->data.varDeclInit.assignStmt = assignStmtNode;

            $$ = varDeclInitNode;
        }
    } */
    | ARRAY TYPE ID LBRACKET INT_NUMBER RBRACKET SEMI
    {
        printf("PARSER: Printing symbol table\n");
        printSymbolTable(symTab);
        printf("PARSER: Checking if variable has already been declared\n");

        char* varName = strdup($3);
        printf("Name with suffix: %s\n", varName);

        symbol = lookupSymbolInCurrentScope(symTab, varName);

        if (symbol != NULL)
        {
            printf("PARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n", $3, yylineno);
            exit(0);
        }
        else
        {
            $$ = createNode(NodeType_ArrDecl);
            $$->data.arrDecl.varType = strdup($2);
            $$->data.arrDecl.varName = strdup(varName);
            $$->data.arrDecl.arrSize = $5;

            addArrSymbol(symTab, varName, $2, $5);
            printSymbolTable(symTab);
        }
    }
;


VarDeclInit:
    TYPE ID ASSIGN Expr SEMI
    {
        // printf("PARSER: Recognized variable declaration with initialization: %s\n", $2);

        // // Check if variable has already been declared
        // char* varName = strdup($2);
        // symbol = lookupSymbolInCurrentScope(symTab, varName);

        // if (symbol != NULL)
        // {
        //     printf("PARSER: Variable %s at line %d has already been declared - COMPILATION HALTED\n", $2, yylineno);
        //     exit(0);
        // }
        // else
        // {
        //     // Declare the variable
        //     ASTNode* varDeclNode = createNode(NodeType_VarDecl);
        //     varDeclNode->data.varDecl.varType = strdup($1);
        //     varDeclNode->data.varDecl.varName = strdup(varName);

        //     addSymbol(symTab, varName, $1);
        //     printSymbolTable(symTab);

        //     // Create an assignment statement for initialization
        //     ASTNode* assignStmtNode = createNode(NodeType_AssignStmt);
        //     assignStmtNode->data.assignStmt.varName = strdup(varName);
        //     assignStmtNode->data.assignStmt.operator = strdup($3);
        //     assignStmtNode->data.assignStmt.expr = $4;

        //     // Combine declaration and assignment into a VarDeclInit node
        //     $$ = createNode(NodeType_VarDeclInit);
        //     $$->data.varDeclInit.varDecl = varDeclNode;
        //     $$->data.varDeclInit.assignStmt = assignStmtNode;
        // }
    }
;


FuncDecl:
    TYPE ID
    {
        $<ast>$ = createNode(NodeType_FuncDecl); //Partially generate a node to be passed to end rule
        
        currentFunction = $2;
        
        // Check for redeclaration
        if (lookupSymbolInHierarchy(peekSubTable(symTab), $2)) {
            fprintf(stderr, "PARSER: Function '%s' already declared\n", $2);
            exit(1);
        }
        Symbol* sym = addFuncSymbol(symTab, $2, $1);
        $<ast>$->data.funcDecl.name = strdup(sym->name);
        SubTable* newSubTab = enterNewScope(symTab, $2);
        $<ast>$->data.funcDecl.funcSubTable = newSubTab;
    }
    LPAREN ParamList RPAREN LBRACE VarDeclList StmtList RBRACE
    {
        $$ = $<ast>3; //Retrieve incomplete ASTNode from midrule
        $$->data.funcDecl.returnType = stringToVarType($1);
        printf("PARSER: Recognized function declaration: %s\n", $2);

        // addSymbol(symTab, $$->data.funcDecl.name, $1);

        $$->data.funcDecl.paramList = $5;       // Correct
        $$->data.funcDecl.varDeclList = $8;     // Adjusted from $7 to $8
        $$->data.funcDecl.stmtList = $9;        // Adjusted from $8 to $9

        currentFunction = NULL;

        //New implementation
        // $$ = createNode(NodeType_FuncDecl);
        // printf("PARSER: Recognized function declaration: %s\n", $2);
        // addFuncSymbol(symTab, $$->data.funcDecl.name, $1);

        exitScope(symTab);
    }
;

ParamList:
    /* empty */
    {
        $$ = NULL;
    }
    | Param
    {
        $$ = createNode(NodeType_ParamList);
        $$->data.paramList.param = $1;
        $$->data.paramList.next = NULL;
    }
    | Param COMMA ParamList
    {
        $$ = createNode(NodeType_ParamList);
        $$->data.paramList.param = $1;
        $$->data.paramList.next = $3;
    }
;

Param:
    TYPE ID
    {
        $$ = createNode(NodeType_Param);
        $$->data.param.type = stringToVarType($1);

        $$->data.param.name = strdup($2);
        // Check if the parameter is already declared (though unlikely)
        if (lookupSymbolInCurrentScope(symTab, $2)) {
            fprintf(stderr, "Parameter '%s' already declared in current scope\n", $2);
            exit(1);
        }
        addSymbol(symTab, $$->data.param.name, $1);
    }
;

StmtList:
    /* empty */
    {
        $$ = NULL;
    }
    | Stmt StmtList
    {
        printf("PARSER: Recognized statement list\n");
        $$ = createNode(NodeType_StmtList);
        $$->data.stmtList.stmt = $1;
        $$->data.stmtList.stmtList = $2;
    }
;

Stmt:
    ID ASSIGN Expr SEMI
    {
        printf("PARSER: Recognized assignment statement\n");
        $$ = createNode(NodeType_AssignStmt);
        char* varName = $1;

        $$->data.assignStmt.varName = strdup(varName);
        $$->data.assignStmt.operator = strdup($2);
        $$->data.assignStmt.expr = $3;
    }
    | ID LBRACKET Expr RBRACKET ASSIGN Expr SEMI
    {
        printf("PARSER: Recognized array assignment statement\n");
        $$ = createNode(NodeType_AssignArrStmt);
        char* varName = strdup($1);

        $$->data.assignArrStmt.varName = strdup(varName);
        $$->data.assignArrStmt.operator = strdup($5);
        $$->data.assignArrStmt.expr = $6;
        $$->data.assignArrStmt.indexExpr = $3;
    }
    | VarDeclInit
    {
        // Since VarDeclInit contains both declaration and assignment
        $$ = $1;
    }
    | WRITE Expr SEMI
    {
        printf("PARSER: Recognized write statement\n");
        $$ = createNode(NodeType_WriteStmt);
        $$->data.writeStmt.expr = $2;
    }
    | FuncCall SEMI
    {
        $$ = $1;
    }
    | ReturnStmt SEMI
    {
        $$ = $1;
    }
    | IfStmt
    {
        $$ = $1;
    }
    | WhileStmt
    {
        $$ = $1;
    }
    | BreakStmt
    {
        $$ = $1;
    }
;

IfStmt:
    IF LPAREN Expr RPAREN Block
    {
        printf("PARSER: Recognized 'if' statement\n");
        $$ = createNode(NodeType_IfStmt);
        $$->data.ifStmt.condition = $3;
        $$->data.ifStmt.thenStmt = $5;
        $$->data.ifStmt.elseStmt = NULL;
    }
    | IF LPAREN Expr RPAREN Block ELSE Block
    {
        printf("PARSER: Recognized 'if-else' statement\n");
        $$ = createNode(NodeType_IfStmt);
        $$->data.ifStmt.condition = $3;
        $$->data.ifStmt.thenStmt = $5;
        $$->data.ifStmt.elseStmt = $7;
    }
    | IF LPAREN Expr RPAREN Block ElifList
    {
        printf("PARSER: Recognized 'if-elif' statement\n");
        $$ = createNode(NodeType_IfStmt);
        $$->data.ifStmt.condition = $3;
        $$->data.ifStmt.thenStmt = $5;
        $$->data.ifStmt.elseStmt = $6;  // ElifList is assigned to elseStmt
    }
;

ElifList:
    ELIF LPAREN Expr RPAREN Block
    {
        printf("PARSER: Recognized 'elif' statement\n");
        $$ = createNode(NodeType_IfStmt);
        $$->data.ifStmt.condition = $3;
        $$->data.ifStmt.elseStmt = NULL;
        $$->data.ifStmt.thenStmt = $5;
    }
    | ELIF LPAREN Expr RPAREN Block ElifList
    {
        printf("PARSER: Recognized 'elif' with additional 'elif' or 'else'\n");
        $$ = createNode(NodeType_IfStmt);
        $$->data.ifStmt.condition = $3;
        $$->data.ifStmt.thenStmt = $5;
        $$->data.ifStmt.elseStmt = $6;  // ElifList is assigned to elseStmt
    }
    | ELSE Block
    {
        printf("PARSER: Recognized 'else' statement\n");
        $$ = $2; // Directly assign the else Block
    }
;

Block:
    LBRACE VarDeclList StmtList RBRACE
    {
        // Scope creation/exit is handled by FuncDecl/If/etc.
        //  This is because scope creation requires unique data
        //  based on the type of scope (e.g. name). Unfortunate.
        $$ = $2;             
        $$ = $3;             
    }
    | Stmt
    {
        $$ = $1;  // Single statements do not introduce a new scope
    }
;

WhileStmt:
    WHILE LPAREN Expr RPAREN Block
    {
        printf("PARSER: Recognized 'while' statement\n");
        $$ = createNode(NodeType_WhileStmt);
        $$->data.whileStmt.condition = $3;
        $$->data.whileStmt.block = $5;
    }
;

BreakStmt:
    BREAK SEMI
    {
        printf("PARSER: Recognized 'break' statement\n");
        $$ = createNode(NodeType_BreakStmt);
    }
;

Expr:
    MINUS Expr
    {
        $$ = createNode(NodeType_UnaryOp);
        $$->data.unaryOp.expr = $2;
        $$->data.unaryOp.operator = strdup("neg"); //Best to use a unique operator; '-' is used for binOp subtraction
    }
    | NOT Expr
    {
        $$ = createNode(NodeType_UnaryOp);
        $$->data.unaryOp.expr = $2;
        $$->data.unaryOp.operator = strdup($1);
    }
    | Expr PLUS Expr
    {
        printf("PARSER: Recognized addition expression\n");
        $$ = createNode(NodeType_BinOp);
        $$->data.binOp.left = $1;
        $$->data.binOp.right = $3;
        $$->data.binOp.operator = strdup($2);
    }
    | Expr MINUS Expr
    {
        printf("PARSER: Recognized subtraction expression\n");
        $$ = createNode(NodeType_BinOp);
        $$->data.binOp.left = $1;
        $$->data.binOp.right = $3;
        $$->data.binOp.operator = strdup($2);
    }
    | Expr MULTIPLY Expr
    {
        printf("PARSER: Recognized multiplication expression\n");
        $$ = createNode(NodeType_BinOp);
        $$->data.binOp.left = $1;
        $$->data.binOp.right = $3;
        $$->data.binOp.operator = strdup($2);
    }
    | Expr DIVIDE Expr
    {
        printf("PARSER: Recognized division expression\n");
        $$ = createNode(NodeType_BinOp);
        $$->data.binOp.left = $1;
        $$->data.binOp.right = $3;
        $$->data.binOp.operator = strdup($2);
    }
    | Expr MOD Expr
    {
        printf("PARSER: Recognized modulus expression\n");
        $$ = createNode(NodeType_BinOp);
        $$->data.binOp.left = $1;
        $$->data.binOp.right = $3;
        $$->data.binOp.operator = strdup($2);
    }
    | Expr AND Expr
    {
        printf("PARSER: Recognized inequality expression\n");
        $$ = createNode(NodeType_RelOp);
        $$->data.binOp.left = $1;
        $$->data.binOp.right = $3;
        $$->data.binOp.operator = strdup($2);
    }
    | Expr OR Expr
    {
        printf("PARSER: Recognized inequality expression\n");
        $$ = createNode(NodeType_RelOp);
        $$->data.binOp.left = $1;
        $$->data.binOp.right = $3;
        $$->data.binOp.operator = strdup($2);
    }
    | Expr GREATER_THAN Expr
    {
        printf("PARSER: Recognized greater-than expression\n");
        $$ = createNode(NodeType_RelOp);
        $$->data.binOp.left = $1;
        $$->data.binOp.right = $3;
        $$->data.binOp.operator = strdup($2);
    }
    | Expr LESS_THAN Expr
    {
        printf("PARSER: Recognized less-than expression\n");
        $$ = createNode(NodeType_RelOp);
        $$->data.binOp.left = $1;
        $$->data.binOp.right = $3;
        $$->data.binOp.operator = strdup($2);
    }
    | Expr GREATER_EQUAL Expr
    {
        printf("PARSER: Recognized greater-than-or-equal expression\n");
        $$ = createNode(NodeType_RelOp);
        $$->data.binOp.left = $1;
        $$->data.binOp.right = $3;
        $$->data.binOp.operator = strdup($2);
    }
    | Expr LESS_EQUAL Expr
    {
        printf("PARSER: Recognized less-than-or-equal expression\n");
        $$ = createNode(NodeType_RelOp);
        $$->data.binOp.left = $1;
        $$->data.binOp.right = $3;
        $$->data.binOp.operator = strdup($2);
    }
    | Expr EQUAL_EQUAL Expr
    {
        printf("PARSER: Recognized equality expression\n");
        $$ = createNode(NodeType_RelOp);
        $$->data.binOp.left = $1;
        $$->data.binOp.right = $3;
        $$->data.binOp.operator = strdup($2);
    }
    | Expr NOT_EQUAL Expr
    {
        printf("PARSER: Recognized inequality expression\n");
        $$ = createNode(NodeType_RelOp);
        $$->data.binOp.left = $1;
        $$->data.binOp.right = $3;
        $$->data.binOp.operator = strdup($2);
    }
    | ID
    {
        printf("PARSER: Recognized identifier\n");
        $$ = createNode(NodeType_SimpleID);
        char* varName = $1;
        $$->data.simpleID.name = varName;
    }
    | ID LBRACKET Expr RBRACKET
    {
        printf("PARSER: Recognized array access\n");
        $$ = createNode(NodeType_ArrAccess);
        char* varName = strdup($1);
        $$->data.arrAccess.name = varName;
        $$->data.arrAccess.indexExpr = $3;
    }
    | INT_NUMBER
    {
        printf("PARSER: Recognized int number\n");
        $$ = createNode(NodeType_IntExpr);
        $$->data.intExpr.number = $1;
    }
    | FLOAT_NUMBER
    {
        printf("PARSER: Recognized float number\n");
        $$ = createNode(NodeType_FloatExpr);
        $$->data.floatExpr.number = $1;
    }
    | CHAR_VALUE { 
        printf("PARSER: Recognized character\n");
        $$ = createNode(NodeType_CharExpr);
        $$->data.charExpr.character = $1;
        // Set other fields as necessary
    }
    | CONST_TRUE {
        printf("PARSER: Recognized boolean constant\n");
        $$ = createNode(NodeType_IntExpr);
        $$->data.intExpr.number = 1;    //Boolean stored as an integer (non-zero = true)
    }
    | CONST_FALSE {
        printf("PARSER: Recognized boolean constant\n");
        $$ = createNode(NodeType_IntExpr);
        $$->data.intExpr.number = 0;    //Boolean stored as an integer (0 = false)
    }
    | FuncCall
    {
        $$ = $1;
    }
    | LPAREN Expr RPAREN
    {
        $$ = $2;
    }
;

FuncCall:
    ID LPAREN ArgList RPAREN
    {
        $$ = createNode(NodeType_FuncCall);
        $$->data.funcCall.name = strdup($1);
        $$->data.funcCall.argList = $3;
    }
;

ArgList:
    /* empty */
    {
        $$ = NULL;
    }
    | Arg
    {
        $$ = createNode(NodeType_ArgList);
        $$->data.argList.arg = $1;
        $$->data.argList.next = NULL;
    }
    | Arg COMMA ArgList
    {
        $$ = createNode(NodeType_ArgList);
        $$->data.argList.arg = $1;
        $$->data.argList.next = $3;
    }
;

Arg:
    Expr
    {
        $$ = createNode(NodeType_Arg);
        $$->data.arg.expr = $1;
    }
;

ReturnStmt:
    RETURN
    {
        $$ = createNode(NodeType_ReturnStmt);
        $$->data.returnStmt.returnExpr = NULL;
    }
    | RETURN Expr
    {
        $$ = createNode(NodeType_ReturnStmt);
        $$->data.returnStmt.returnExpr = $2;
    }



;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at (line %d:%d)\n", s, lines, chars);
}

int main(int argc, char **argv) {
    ++argv, --argc;  /* Skip over program name */
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;

        // Record start time
    clock_t start_time = clock();

    // Call the main compilation function
    /* compile(argv[1]); */

    // Initialize symbol table
    symTab = createSymbolTable(TABLE_SIZE);
    if (symTab == NULL) {
        // Handle error
        return EXIT_FAILURE;
    }

    int parseCode = yyparse();
    if (parseCode == 0)
    {
        // Successfully parsed
        printf("Parsing successful!\n");
        traverseAST(root, 0, drawVertical, false);
        // Print symbol table for debugging
        printSymbolTable(symTab);
        // Semantic analysis
        printf("\n=== SEMANTIC ANALYSIS ===\n\n");
        initSemantic(symTab);
        semanticAnalysis(root);
        printf("\n=== TAC GENERATION ===\n");
        printTACToFile("output/TAC.ir", tacHead);
        printFuncTACsToFile();

        // Code generation
        printf("\n=== CODE GENERATION ===\n");
        initCodeGenerator("output/output.asm");
        generateMIPS(tacHead, symTab);
        finalizeCodeGenerator("output/output.asm");

        freeAST(root);
        freeSymbolTable(symTab);

        // Record end time
        clock_t end_time = clock();

        // Calculate and display elapsed time
        double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Compilation time: %.4f seconds\n", elapsed_time);
    }
    else
        printf("Parsing failed. (error code: %d)\n", parseCode);

    return 0;
}

