%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int words = 0;
int chars = 0;
int lines = 1;

bool errorFound = false;
%}

%%

"int"               { yylval.sval = strdup(yytext); chars += strlen(yytext); return TYPE; }
"float"             { yylval.sval = strdup(yytext); chars += strlen(yytext); return TYPE; }
"char"              { yylval.sval = strdup(yytext); chars += strlen(yytext); return TYPE; }
"void"              { yylval.sval = strdup(yytext); chars += strlen(yytext); return TYPE; }

"array"             { chars += strlen(yytext); return ARRAY; }
"write"             { chars += strlen(yytext); return WRITE; }
"return"            { chars += strlen(yytext); return RETURN; }

"if"                { chars += strlen(yytext); return IF; }
"else"              { chars += strlen(yytext); return ELSE; }
"elif"              { chars += strlen(yytext); return ELIF; }

"while"             { chars += strlen(yytext); return WHILE; }
"break"             { chars += strlen(yytext); return BREAK; }

"true"              { chars += strlen(yytext); return CONST_TRUE; }
"false"             { chars += strlen(yytext); return CONST_FALSE; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval = strdup(yytext); chars += strlen(yytext); return ID; }
[0-9]+              { yylval.intVal = atoi(strdup(yytext)); chars += strlen(yytext); return INT_NUMBER; }
[0-9]+\.[0-9]+      { yylval.floatVal = atof(yytext); chars += strlen(yytext); return FLOAT_NUMBER; }
\'[\x00-\x7F]\'     { yylval.charVal = yytext[1] ; chars += strlen(yytext); return CHAR_VALUE; }

"+"                 { yylval.sval = strdup(yytext); chars += strlen(yytext); return PLUS; }
"-"                 { yylval.sval = strdup(yytext); chars += strlen(yytext); return MINUS; }
"*"                 { yylval.sval = strdup(yytext); chars += strlen(yytext); return MULTIPLY; }
"/"                 { yylval.sval = strdup(yytext); chars += strlen(yytext); return DIVIDE; }
"%"                 { yylval.sval = strdup(yytext); chars += strlen(yytext); return MOD; }
"="                 { yylval.sval = strdup(yytext); chars += strlen(yytext); return ASSIGN; }
";"                 { chars += strlen(yytext); return SEMI; }
","                 { chars += strlen(yytext); return COMMA; }

">="     { yylval.sval = strdup(yytext); return GREATER_EQUAL; }
"<="     { yylval.sval = strdup(yytext); return LESS_EQUAL; }
"=="     { yylval.sval = strdup(yytext); return EQUAL_EQUAL; }
"!="     { yylval.sval = strdup(yytext); return NOT_EQUAL; }
">"      { yylval.sval = strdup(yytext); return GREATER_THAN; }
"<"      { yylval.sval = strdup(yytext); return LESS_THAN; }

"!"       { yylval.sval = strdup(yytext); return NOT; }
"&&"      { yylval.sval = strdup(yytext); return AND; }
"||"      { yylval.sval = strdup(yytext); return OR; }

"["                 { chars += strlen(yytext); return LBRACKET; }
"]"                 { chars += strlen(yytext); return RBRACKET; }
"("                 { chars += strlen(yytext); return LPAREN; }
")"                 { chars += strlen(yytext); return RPAREN; }
"{"                 { chars += strlen(yytext); return LBRACE; }
"}"                 { chars += strlen(yytext); return RBRACE; }

[ \t\r]+            { /* Skip whitespace */ }
"//".*              { /* Skip comment */ }
[\n]                { lines++; chars = 0; }
.                   { printf("Unrecognized symbol '%s' at line %d:%d\n", yytext, lines, chars); errorFound = true; }

%%

int yywrap(void) { return 1; }

