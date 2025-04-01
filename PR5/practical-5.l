%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_token(const char *type, const char *value) {
    printf("%s: %s\n", type, value);
}
%}

KEYWORD    (auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)
IDENTIFIER  [a-zA-Z_][a-zA-Z0-9_]*
CONSTANT   [0-9]+(\.[0-9]+)?
STRING     \"([^\"\n]*)\"|\'([^\'\n]*)\'
PUNCTUATION [(){};,]
OPERATOR   (\+|\-|\*|\/|=|==|!=|<=|>=|<|>)
COMMENT    (\/\/[^\n]*|\/\*([^*]|\*+[^\/])*\*+\/)

%%

{KEYWORD}        { print_token("Keyword", yytext); }
{IDENTIFIER}     { print_token("Identifier", yytext); }
{CONSTANT}       { print_token("Constant", yytext); }
{STRING}         { print_token("String", yytext); }
{PUNCTUATION}    { print_token("Punctuation", yytext); }
{OPERATOR}       { print_token("Operator", yytext); }
{COMMENT}        { /* Ignore comments */ }
[ \t\n]          { /* Ignore white spaces */ }
.                { printf("Lexical Error: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
