%{
#include <stdio.h>
%}

%%

[0-9]+      { printf("%s\n", yytext); }  // Match numbers and print each on a new line
.           { }  

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
