#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "commons/types.h"
#include <stdbool.h>

#define DEFAULT_TABSTACK_CAPACITY 8

typedef enum SymbolType {
    SymbolType_Var,
    SymbolType_Arr,
    SymbolType_Func
}SymbolType;

//Symbol struct: used to represent variables and functions

//  General fields:
//      - char* name
//      - Vartype varType (for functions, serves as the return type)
//      - SymbolType symType
//  Array fields:
//      - int arrSize
//  Function fields:
//      - struct FuncParam* params (list of function parameters)
//  Traversal fields:
//      - struct Symbol* next (SymbolTable hash table)
//      - struct Symbol* next (SubTable hash table)
//      - struct SubTable* subTab (what SubTable does this belong to? used for operand/label names)

typedef struct Symbol {
    //General Fields
    char* name;
    VarType varType;
    SymbolType symType;
    char* fullName; //Workaround to for easy output without memory leaks
                    //Might keep permanently for debugging purposes

    //Array fields
    int arrSize;

    //Function fields
    struct FuncParam* params;

    //Traversal fields
    struct Symbol* next;
    struct SubTable* subTab;
}Symbol;

//FuncParam struct: used to represent the parameters of a function declaration
//  Fields:
//      - char* name
//      - VarType varType
//      - struct FuncParm* prev
//      - struct FuncParam* next
typedef struct FuncParam {
    Symbol* refSymbol;
    VarType varType;
    struct FuncParam* prev; //Arguments are popped from the stack in reverse order,
                            //2-way linked list simplifies assignment of args to param vars
    struct FuncParam* next;
} FuncParam;

//SymbolTable struct: Holds the data for all declared vars/funcs in the program
//                  Declared symbols are divided among SubTables, representing scopes
//  Fields:
//      - int tableSize
//      - SubTable** subTabs
//      - int numScopes
typedef struct SymbolTable {
    struct SubTable** subTabs;  // Array of pointers to symbols (hash table)
    int tableSize;
    int numScopes;

    //Stack of active sub-tables
    struct SubTable** tabStack;
    int tabStackCursor;
    int tabStackCapacity;
} SymbolTable;

//SubTable struct: Holds the data for all declared vars/funcs in a specific struct
//  Fields:
//      - Symbol** table
//      - char* scopeName
//      - int scopeID
//  Traversal Fields:
//      - struct SubTable* next;    //Hash table
//      - struct SubTable* parent;
typedef struct SubTable {
    //General Fields
    struct Symbol** table;
    int tableSize;
    char* scopeName; //Stores function name
    int scopeID;

    //Traversal fields
    struct SubTable* next;
    struct SubTable* parent;
} SubTable;

// Function prototypes
SymbolTable* createSymbolTable(int size);
void freeSymbolTable(SymbolTable* symTab);
void enterScope(SymbolTable* table);
void exitScope(SymbolTable* table);
Symbol* addSymbol(SymbolTable* symTab, const char* varName, const char* typeString);
Symbol* addArrSymbol(SymbolTable* symTab, const char* varName, const char* typeString, int size);
void addParameter(SymbolTable* symTab, Symbol* symbol, const char* name, VarType type);
Symbol* lookupSymbolInCurrentScope(SymbolTable* symTab, const char* varName);
FuncParam* getParamsTail(Symbol* symbol);
void printSymbolTable(SymbolTable* symTab);

//New functions
SubTable* createSubTable(SymbolTable* symTab, char* name);
void freeSubTable(SubTable* subTab);
void pushSubTable(SymbolTable* symTab, SubTable* subTab);
SubTable* popSubTable(SymbolTable* symTab);
SubTable* peekSubTable(SymbolTable* symTab);

Symbol* addFuncSymbol(SymbolTable* table, const char* name, const char* typeString);
void addSubTableSymbol(SymbolTable* symTab, Symbol* sym);

Symbol* lookupSymbolInSubTable(SubTable* subTab, const char* name);
Symbol* lookupSymbolInHierarchy(SubTable* subTab, char* symbolName);
SubTable* lookupSubTable(SymbolTable* symTab, char* scopeName);

void printSymbol(Symbol* sym);
void printSubTable(SubTable* subTab);

char* generateScopeName(char* inputName, int scopeID);
char* getFullSymbolName(Symbol* sym);

SubTable* enterNewScope(SymbolTable* table, char* scopeName);
void enterExistingScope(SymbolTable* table, char* scopeName);

#endif
