%{
#include <stdio.h>
#include <stdlib.h>

void print_token(const char* type, const char* lexeme) {
    printf("%s: %s\n", type, lexeme);
}
%}

%%

"int"|"char"|"float"|"double"|"return"|"void"|"long"|"struct"  { print_token("Keyword", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*    { print_token("Identifier", yytext); }

[0-9]+(\.[0-9]+)?         { print_token("Constant", yytext); }

\"[^\"]*\"                { print_token("String", yytext); }
\'[^\']\'                 { print_token("String", yytext); }

[{}()\[\],;]              { print_token("Punctuation", yytext); }

"="|"+"|"-"|"*"|"/"|"%"|"=="|"!="|"<"|">"|"<="|">="|"&&"|"||"|"!" { print_token("Operator", yytext); }

"//".*                    { /* Ignore single-line comments */ }

"/*"([^*]|\*+[^*/])*\*+"/" { /* Ignore multi-line comments */ }

[ \t\n]+                  { /* Ignore whitespace */ }

.                         { printf("Lexical Error: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
