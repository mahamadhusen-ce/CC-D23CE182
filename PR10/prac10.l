%{
#include "prac10.tab.h"

%}

%%

[0-9]+		     { yylval.fval = atoi(yytext); return NUMBER; }
[\t ]+               { /* Ignore whitespace */ }
[\n]                 { return 0; }  
[+\-*/^()]           { return yytext[0]; }
.                    { printf("Invalid character: %s\n", yytext); return 0; }

%%

int yywrap() {
    return 1;
}
