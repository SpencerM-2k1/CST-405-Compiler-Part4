#include "symbolTable.h"
#include "commons/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hash function for symbol table (simple mod hash)
unsigned int hash(const char* str, int tableSize) {
    unsigned int hashval = 0;
    while (*str != '\0') {
        hashval = (hashval << 5) + *str++;  // Left shift and add char value
    }
    return hashval % tableSize;
}

// Create a new symbol table
SymbolTable* createSymbolTable(int size) {
    SymbolTable* newTable = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (!newTable) {
        perror("Failed to create symbol table");
        exit(EXIT_FAILURE);
    }
    
    //New implementation
    //  Set up SubTable hash map
    newTable->tableSize = size; //Keep this even when ->table is removed
                                // It is used to set SubTable size
    newTable->numScopes = 0;
    newTable->subTabs = (SubTable*)malloc(sizeof(SubTable) * newTable->tableSize);
    for (int i = 0; i < newTable->tableSize; i++) {
        newTable->subTabs[i] = NULL;
    }


    newTable->tabStackCapacity = DEFAULT_TABSTACK_CAPACITY;
    newTable->tabStack = (SubTable**)malloc(sizeof(SubTable*) * newTable->tabStackCapacity);
    newTable->tabStackCursor = 0;

    SubTable* mainSubTab = createSubTable(newTable, "main");
    pushSubTable(newTable, mainSubTab);

    return newTable;
}

// Create a SubTable and link it to the provided SymbolTable
SubTable* createSubTable(SymbolTable* symTab, char* name) {
    //Allocate memory
    SubTable* newSubTable = (SubTable*)malloc(sizeof(SubTable));
    if (!newSubTable) {
        perror("Failed to create symbol table");
        exit(EXIT_FAILURE);
    }
    newSubTable->table = (Symbol**)malloc(sizeof(Symbol*) * symTab->tableSize);
    if (!newSubTable->table) {
        perror("Failed to allocate memory for symbol table");
        free(newSubTable);
        exit(EXIT_FAILURE);
    }

    //Initialize table
    newSubTable->tableSize = symTab->tableSize;
    for (int i = 0; i < newSubTable->tableSize; i++) {
        newSubTable->table[i] = NULL;
    }

    //Set scope identifiers
    newSubTable->scopeID = symTab->numScopes;
    newSubTable->scopeName = generateScopeName(name, newSubTable->scopeID);

    //Insert into symTab's hash map
    int hashval = hash(newSubTable->scopeName, symTab->tableSize);
    newSubTable->next = symTab->subTabs[hashval];
    symTab->subTabs[hashval] = newSubTable;
    // printf("newSubTable->scopeName: %s\n", newSubTable->scopeName);
    // printf("hashval: %d\n", hashval);
    // printf("symTab->subTabs[hashval]->scopeName: %s\n", symTab->subTabs[hashval]->scopeName);

    //Set parent
    if (symTab->tabStackCursor > 0)
    {
        newSubTable->parent = symTab->tabStack[symTab->tabStackCursor - 1];
    }
    else
    {
        newSubTable->parent = NULL;
    }

    symTab->numScopes++;

    return newSubTable;
}

// Free the memory for the symbol table
void freeSymbolTable(SymbolTable* symTab) {
    //Free deprecated symbol table
    //  Do not free indices. They will be freed when SubTables are freed.

    //Free SubTables
    for (int i = 0; i < symTab->tableSize; i++) {
        SubTable* subTab = symTab->subTabs[i];
        while (subTab) {
            SubTable* nextSubTab = subTab->next;
            freeSubTable(subTab);
            subTab = nextSubTab;
        }
    }
    free(symTab->subTabs);
    free(symTab->tabStack); //Don't free indicies in stack, will cause a double free error
    free(symTab);
}

// Free the memory of a SubTable
void freeSubTable(SubTable* subTab) {
    //Free deprecated symbol table
    for (int i = 0; i < subTab->tableSize; i++) {
        Symbol* sym = subTab->table[i];
        while (sym) {
            Symbol* nextSym = sym->next;
            free(sym->name);
            // Free parameters if it's a function symbol
            if (sym->params) {
                FuncParam* param = sym->params;
                while (param) {
                    FuncParam* nextParam = param->next;
                    // free(param->name);
                    free(param);
                    param = nextParam;
                }
            }
            free(sym);
            sym = nextSym;
        }
    }
    free(subTab->table);
    free(subTab->scopeName);
    free(subTab);
}

// Enter a new scope
// void enterScope(SymbolTable* table) {
//     char* scopeName = "placeholder";
//     SubTable* newSubTab = createSubTable(table, scopeName);
//     pushSubTable(table, newSubTab);
//     printf("Pushed SubTable: (ID: %d, name: %s)\n", newSubTab->scopeID, newSubTab->scopeName);
// }

void enterExistingScope(SymbolTable* table, char* scopeName)
{
    SubTable* subTab = lookupSubTable(table, scopeName);
    if (!subTab)
    {
        printf("SYMBOL_TABLE: Existing scope with name \"%s\" could not be found.\n",scopeName);
        exit(EXIT_FAILURE);
    }
}

    //New version (includes name field)
    // Enter a new scope
    // Returns an address to the subTable. Use this to store the SubTable's scopeName, if needed.
    SubTable* enterNewScope(SymbolTable* table, char* scopeName) {
        SubTable* newSubTab = createSubTable(table, scopeName);
        pushSubTable(table, newSubTab);

        return newSubTab;
    }

// Exit the current scope
void exitScope(SymbolTable* table) {
    SubTable* poppedTable = popSubTable(table);
    if (poppedTable == NULL)
    printf("Popped SubTable: (ID: %d, name: %s)\n", poppedTable->scopeID, poppedTable->scopeName);
}

// Add a symbol to the symbol table
Symbol* addSymbol(SymbolTable* table, const char* name, const char* typeString) {
    if (lookupSymbolInCurrentScope(table, name)) {
        printf("Error: Symbol '%s' already exists in the current scope.\n", name);
        return NULL;  // Return NULL to indicate failure
    }

    VarType type;
    if ((strcmp(typeString, "int") == 0) || (strcmp(typeString, "VarType_Int") == 0)) {
        type = VarType_Int;
    } else if ((strcmp(typeString, "float") == 0)  || (strcmp(typeString, "VarType_Float") == 0)) {
        type = VarType_Float;
    } else if ((strcmp(typeString, "char") == 0)  || (strcmp(typeString, "VarType_Char") == 0)) {
        type = VarType_Char;
    } else if ((strcmp(typeString, "void") == 0)  || (strcmp(typeString, "VarType_Void") == 0)) {
        printf("ERROR: VarType_Void is only recognized for function. Halting compilation...");
        exit(1);
    } else {
        printf("ERROR: VarType %s not recognized. Halting compilation...\n", typeString);
        printf("Offending symbol: %s\n", name);
        exit(1);
    }

    Symbol* newSymbol = (Symbol*)malloc(sizeof(Symbol));
    newSymbol->name = strdup(name);
    printf("newSymbol->name: %s\n", newSymbol->name);
    newSymbol->varType = type;
    
    //Assign SymbolType
    newSymbol->symType = SymbolType_Var;

    // Array elements are unused
    newSymbol->arrSize = 0;

    // Function parameters are unused for non-functions
    newSymbol->params = NULL;

    addSubTableSymbol(table, newSymbol);

    return newSymbol;  // Allows the created symbol to be immediately accessed if necessary
}

// Add an array symbol to the symbol table
Symbol* addArrSymbol(SymbolTable* table, const char* name, const char* typeString, int size) {
    if (size <= 0) {
        printf("ERROR: Array size must be greater than zero.\n");
        exit(1);
    }
    if (lookupSymbolInCurrentScope(table, name)) {
        printf("Error: Symbol '%s' already exists in the current scope.\n", name);
        return NULL;
    }

    VarType type;
    if (strcmp(typeString, "int") == 0) {
        type = VarType_Int;
    } else if (strcmp(typeString, "float") == 0) {
        type = VarType_Float;
    } else if ((strcmp(typeString, "char") == 0)  || (strcmp(typeString, "VarType_Char") == 0)) {
        type = VarType_Char;
    } else if ((strcmp(typeString, "void") == 0)  || (strcmp(typeString, "VarType_Void") == 0)) {
        printf("ERROR: VarType_Void is only recognized for function. Halting compilation...");
        exit(1);
    } else {
        printf("ERROR: VarType not recognized. Halting compilation...");
        exit(1);
    }

    Symbol* newSymbol = (Symbol*)malloc(sizeof(Symbol));
    newSymbol->name = strdup(name);
    printf("newSymbol->name: %s\n", newSymbol->name);
    newSymbol->varType = type;

    //Assign SymbolType
    newSymbol->symType = SymbolType_Arr;

    // Set array elements
    newSymbol->arrSize = size;

    // Arrays are always non-functions
    newSymbol->params = NULL;


    addSubTableSymbol(table, newSymbol);

    return newSymbol;
}

// Add an array symbol to the symbol table
Symbol* addFuncSymbol(SymbolTable* table, const char* name, const char* typeString) {
    if (lookupSymbolInCurrentScope(table, name)) {
        printf("Error: Symbol '%s' already exists in the current scope.\n", name);
        return NULL;  // Return NULL to indicate failure
    }

    VarType type;
    if ((strcmp(typeString, "int") == 0) || (strcmp(typeString, "VarType_Int") == 0)) {
        type = VarType_Int;
    } else if ((strcmp(typeString, "float") == 0)  || (strcmp(typeString, "VarType_Float") == 0)) {
        type = VarType_Float;
    } else if ((strcmp(typeString, "char") == 0)  || (strcmp(typeString, "VarType_Char") == 0)) {
        type = VarType_Char;
    } else if ((strcmp(typeString, "void") == 0)  || (strcmp(typeString, "VarType_Void") == 0)) {
        type = VarType_Void;
    } else {
        printf("ERROR: VarType %s not recognized. Halting compilation...\n", typeString);
        printf("Offending symbol: %s\n", name);
        exit(1);
    }

    Symbol* newSymbol = (Symbol*)malloc(sizeof(Symbol));
    newSymbol->name = strdup(name);
    printf("newSymbol->name: %s\n", newSymbol->name);
    newSymbol->varType = type;

    //Assign SymbolType
    newSymbol->symType = SymbolType_Func;

    // Array elements are unused
    newSymbol->arrSize = 0;

    // Function parameters will be filled out later
    newSymbol->params = NULL;


    // return newSymbol;  // Allows the created symbol to be immediately accessed if necessary
    addSubTableSymbol(table, newSymbol);

    return newSymbol;
}

// Add a parameter to a function symbol
void addParameter(SymbolTable* symTab, Symbol* symbol, const char* name, VarType type) {
    symbol->symType = SymbolType_Func;
    
    FuncParam* newParam = malloc(sizeof(FuncParam));
    // newParam->name = strdup(name);
    SubTable* subTab = peekSubTable(symTab);
    newParam->refSymbol = lookupSymbolInSubTable(subTab, name);
    if (!newParam->refSymbol)
    {
        printf("Number of tables in stack: %d\n", symTab->tabStackCursor);
        printf("SYMBOL_TABLE: Failed to find symbol reference for parameter %s in scope %p\n", name, symTab->subTabs[symTab->tabStackCursor - 1]);
        exit(EXIT_FAILURE);
    }
    newParam->varType = type;
    newParam->next = NULL;
    printf("newParam->type: %s\n", varTypeToString(newParam->varType));

    printf("SYMBOL_TABLE: Adding parameter %s %s to function %s\n", varTypeToString(type), name, symbol->name);

    if (!symbol->params) {  // Insert into empty linked list
        newParam->prev = NULL;
        symbol->params = newParam;
    } else {  // Insert into existing linked list
        FuncParam* current = symbol->params;
        while (current->next) {
            current = current->next;  // Traverse to next param until end of list
        }
        newParam->prev = current;
        current->next = newParam;  // Insert newParam at the end
    }
}

// Add symbol to SubTable
void addSubTableSymbol(SymbolTable* symTab, Symbol* sym)
{

    //Get top of SubTable stack
    SubTable* subTab = symTab->tabStack[symTab->tabStackCursor - 1];
    
    //Add symbol to SubTable's hashTable
    unsigned int hashval = hash(sym->name, subTab->tableSize);
    sym->next = subTab->table[hashval];
    subTab->table[hashval] = sym;

    //Add SubTable pointer to symbol for easy reference
    sym->subTab = subTab;

    //Get full name (MIPS var name) of symbol and store it
    sym->fullName = getFullSymbolName(sym);
}

// Lookup a symbol in the current scope only
Symbol* lookupSymbolInCurrentScope(SymbolTable* table, const char* name) {
    // New Code
    int cursorPosition = table->tabStackCursor - 1;
    SubTable* currentSubTab = table->tabStack[cursorPosition];
    
    // currentSubTab = table->tabStack[cursorPosition];
    unsigned int hashval = hash(name, currentSubTab->tableSize);

    for (Symbol* sym = currentSubTab->table[hashval]; sym != NULL; sym = sym->next) {
        printf("    Comparing \"%s\" and \"%s\"", name, sym->name);
        if (strcmp(name, sym->name) == 0) {
            return sym;
        }
    }

    return NULL;
}

// Lookup a symbol in a specific SubTable (no hierarchy)
Symbol* lookupSymbolInSubTable(SubTable* subTab, const char* name)
{
    unsigned int hashval = hash(name, subTab->tableSize);

    for (Symbol* sym = subTab->table[hashval]; sym != NULL; sym = sym->next) {
        printf("    Comparing \"%s\" and \"%s\"", name, sym->name);
        if (strcmp(name, sym->name) == 0) {
            return sym;
        }
    }

    return NULL;
}

// Look up a symbol in a specific SubTable, as well as in all parent SubTable in its hierarchy
Symbol* lookupSymbolInHierarchy(SubTable* subTab, char* symbolName)
{
    // printf("subTab: %p\n", subTab);

    for (SubTable* currentSubTab = subTab; currentSubTab != NULL; currentSubTab = currentSubTab->parent)
    {
        unsigned int hashval = hash(symbolName, currentSubTab->tableSize);

        for (Symbol* sym = currentSubTab->table[hashval]; sym != NULL; sym = sym->next) {
            if (strcmp(symbolName, sym->name) == 0) {
                return sym;
            }
        }
    }
    return NULL;
}

//Get the end of a params linked list
FuncParam* getParamsTail(Symbol* symbol) {
    if (symbol->params) {
        FuncParam* paramsTail = symbol->params;
        while (paramsTail->next) {
            paramsTail = paramsTail->next;
        }
        return paramsTail;
    }
    return NULL;
}

// Print info for a Symbol
void printSymbol(Symbol* sym)
{
    switch(sym->varType)
    {
        case (SymbolType_Var):
            printf("    Name: %s, Type: %s, FullName: %s, Address: %p\n", sym->name, varTypeToString(sym->varType), sym->fullName, sym);
            break;
        case (SymbolType_Arr):
            printf("    Name: %s, Type: %s[%d], FullName: %s, Address: %p\n", sym->name, varTypeToString(sym->varType), sym->arrSize, sym->fullName, sym);
            break;
        case (SymbolType_Func):
            printf("    Name: %s, Type: %s, FullName: %s, Address: %p\n", sym->name, varTypeToString(sym->varType), sym->fullName, sym);
            break;
        default:
            printf("Unknown SymbolType.\n");
            break;
    }
}

// Print the symbol table contents
void printSymbolTable(SymbolTable* table) {
    printf("===Symbol Table (Addr: %p):===\n", table);

    for (int i = 0; i < table->tableSize; i++) {
        SubTable* subTab = table->subTabs[i];
        while (subTab != NULL)
        {
            printSubTable(subTab);
            subTab = subTab->next;
        }
    }
}

// Print contents of a SubTable
void printSubTable(SubTable* subTab) {
    printf("SubTable (ID: %d, Name: %s):\n", subTab->scopeID, subTab->scopeName);
    printf("└── (Pointer: %p, Parent Pointer: %p):\n", subTab, subTab->parent);
    for (int i = 0; i < subTab->tableSize; i++) {
        Symbol* sym = subTab->table[i];
        while (sym != NULL) {
            printSymbol(sym);
            sym = sym->next;
        }
    }
}

//Push SubTable to tabStack
void pushSubTable(SymbolTable* symTab, SubTable* subTab)
{
    if (symTab->tabStackCursor > symTab->tabStackCapacity)
    {
        //TODO: Instead of halting the compiler, resize array
        fprintf(stderr, "SYMBOL_TABLE: Stack overflow! Halting compiler...");
        exit(EXIT_FAILURE);
    }
    symTab->tabStack[symTab->tabStackCursor] = subTab;
    printf("Pushed SubTable at index %d: (ID: %d, name: %s, address: %p)\n", symTab->tabStackCursor, subTab->scopeID, subTab->scopeName, subTab);
    printf("    Index %d: (ID: %d, name: %s, address: %p)\n", symTab->tabStackCursor, symTab->tabStack[symTab->tabStackCursor]->scopeID, symTab->tabStack[symTab->tabStackCursor]->scopeName, symTab->tabStack[symTab->tabStackCursor]);
    symTab->tabStackCursor++;
}

//Pop SubTable from tabStack
SubTable* popSubTable(SymbolTable* symTab)
{
    symTab->tabStackCursor--;
    if (symTab->tabStackCursor < 0)
    {
        fprintf(stderr, "SYMBOL_TABLE: Stack overflow! Halting compiler...");
        exit(EXIT_FAILURE);
    }
    SubTable* poppedSubTab = symTab->tabStack[symTab->tabStackCursor];
    symTab->tabStack[symTab->tabStackCursor] = NULL;
    
    return poppedSubTab;
}

//Retrieve the top SubTable on the stack
SubTable* peekSubTable(SymbolTable* symTab)
{
    return symTab->tabStack[symTab->tabStackCursor - 1];
}

//Lookup SubTable
//  Used to prevent duplicate SubTable name, may prove necessary in semantic phase
SubTable* lookupSubTable(SymbolTable* symTab, char* scopeName)
{
    unsigned int hashval = hash(scopeName, symTab->tableSize);
    // printf("scopeName: %s\n", scopeName);
    // printf("hashval: %d\n", hashval);

    for (SubTable* subTab = symTab->subTabs[hashval]; subTab != NULL; subTab = subTab->next) {
        // printf("strcmp(\"%s\", \"%s\"): %d\n", scopeName, subTab->scopeName, strcmp(scopeName, subTab->scopeName));
        if (strcmp(scopeName, subTab->scopeName) == 0) {
            return subTab;
        }
    }
    return NULL;
}

//Generate scope name
//  Uses scopeID to generate a unique scope name
//  Prevents duplicate scope names in the case of if statements
//  Does not prevent duplicate function names-- those are caught by addSymbol()
char* generateScopeName(char* inputName, int scopeID)
{
    int outputNameLength = snprintf(NULL, 0, "%s_%d", inputName, scopeID); //Get length of const sum so we can allocate appropriate string length
	char* outputName = malloc(outputNameLength + 1);
    snprintf(outputName, outputNameLength + 1, "%s_%d", inputName, scopeID);

    return outputName;
}

//Generate a unique symbol identifier for use in TACs and MIPS code.
//  Uses scope name to differentiate global/local variables
char* getFullSymbolName(Symbol* sym)
{
    int outputNameLength;
    char* outputName;
    char* suffix;
    switch (sym->symType)
    {
        case (SymbolType_Var):
            suffix = "_var";
            break;
        case (SymbolType_Arr):
            suffix = "_arr";
            break;
        case (SymbolType_Func):
            suffix = "_func";
            break;
    }
    outputNameLength = snprintf(NULL, 0, "%s.%s%s", sym->subTab->scopeName, sym->name, suffix); //Get length of const sum so we can allocate appropriate string length
    outputName = malloc(outputNameLength + 1);
    snprintf(outputName, outputNameLength + 1, "%s.%s%s", sym->subTab->scopeName, sym->name, suffix);

    return outputName;
}

//Test case

// Add the following rule to the makefile for easy access
// # SymbolTable test
// #	Requires uncommenting main in symbolTable.c
// #	Remember to re-comment main when you're done!
// symbol:
// 	$(CC) $(CFLAGS) -o symbolTest symbolTable.c commons/types.c
// 	gdb --args symbolTest

//      Pseudocode for example
// int x;
// float z;
//
// void testFunc() {
//  int x;
//  
//  if (cond) {
//      int y;
//  }
// }

// int main(int argc, char **argv) {
//     SymbolTable* table = createSymbolTable(30);
//     SubTable* mainSubTab = lookupSubTable(table, "main_0");
    
//     Symbol* symbol1 = addSymbol(table, "x", "int");
//     char* symbol1_name = symbol1->name;
//     Symbol* symbol4 = addSymbol(table, "z", "float");
//     char* symbol4_name = symbol1->name;

//     addFuncSymbol(table, "testFunc", "void");
//     SubTable* subTab1 = enterNewScope(table, "testFunc");
    
//     Symbol* symbol2 = addSymbol(table, "x", "int");
//     if (!symbol2) printf("VARIABLE IS NULL!\n");
//     char* symbol2_name = symbol2->name;
    
//     SubTable* subTab2 = enterNewScope(table, "if");

//     Symbol* symbol3 = addSymbol(table, "y", "float");
//     char* symbol3_name = symbol3->name;

//     exitScope(table);
//     exitScope(table);
    
//     printf("\n");
//     printSymbolTable(table);
    
//     printf("\n");
//     printf("x in %s: %p\n", mainSubTab->scopeName, lookupSymbolInHierarchy(mainSubTab, "x"));
//     printf("y in %s: %p\n", mainSubTab->scopeName, lookupSymbolInHierarchy(mainSubTab, "y"));
//     printf("z in %s: %p\n", mainSubTab->scopeName, lookupSymbolInHierarchy(mainSubTab, "z"));
//     printf("x in %s: %p\n", subTab1->scopeName, lookupSymbolInHierarchy(subTab1, "x"));
//     printf("y in %s: %p\n", subTab1->scopeName, lookupSymbolInHierarchy(subTab1, "y"));
//     printf("z in %s: %p\n", subTab1->scopeName, lookupSymbolInHierarchy(subTab1, "z"));
//     printf("x in %s: %p\n", subTab2->scopeName, lookupSymbolInHierarchy(subTab2, "x"));
//     printf("y in %s: %p\n", subTab2->scopeName, lookupSymbolInHierarchy(subTab2, "y"));
//     printf("z in %s: %p\n", subTab2->scopeName, lookupSymbolInHierarchy(subTab2, "z"));
     
//     freeSymbolTable(table);
// }