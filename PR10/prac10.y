%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Enable float values in yacc
void yyerror(const char *s);
int yylex();
%}

%union 
{
    int fval;
}

// Tokens
%token <fval> NUMBER
%token '+' '-' '*' '/' '^' '(' ')'

// Data type for non-terminals
%type <fval> E T F G L

// Operator precedence and associativity
%left '+' '-'
%left '*' '/'
%right '^'  // Right associative exponentiation
%left '(' ')'

%%

// Grammar rules with SDD (Semantic Actions)
L   : E  {printf("=%d\n",$$); return 0;}
     ;
E   : E '+' T   { $$ = $1 + $3; }
    | E '-' T   { $$ = $1 - $3; }
    | T         { $$ = $1; }
    ;

T   : T '*' F   { $$ = $1 * $3; }
    | T '/' F   { $$ = $1 / $3; }
    | F         { $$ = $1; }
    ;

F   : G '^' F   { $$ = pow($1, $3); }  // Exponentiation handled separately
    | G         { $$ = $1; }
    ;

G   : '(' E ')' { $$ = $2; }
    | NUMBER    { $$ = $1; }
    ;


%%

// Error handling
void yyerror(const char *s) {
    printf("Error: %s\n", s);
}

// Main function
int main() {
    printf("Enter an arithmetic expression: ");
    yyparse();
    return 0;
}
