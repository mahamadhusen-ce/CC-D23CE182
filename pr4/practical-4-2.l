%{
#include <stdio.h>
%}

%%
charusat   { printf("university"); }
.          { printf("%s", yytext); } // Print other characters as is

%%

int main() {
    yylex();
    return 0;
}

int yywrap() { return 1; }
