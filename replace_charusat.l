%{
#include <stdio.h>
#include <string.h>
%}

%%
[Cc]harusat    { printf("university"); }  // Match and replace "charusat" (case-insensitive)
.|\n           { printf("%s", yytext); }  // Print other characters as they are
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
