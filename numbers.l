%{
#include <stdio.h>
%}

%%
[0-9]+   { printf("%s\n", yytext); }  // Match and print numbers
.|\n      { }  // Ignore other characters
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
