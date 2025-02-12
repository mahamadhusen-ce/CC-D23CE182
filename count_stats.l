%{
#include <stdio.h>

int char_count = 0, word_count = 0, line_count = 0;
%}

%%
\n      { line_count++; char_count++; }    // Count new line as line and character
[^\n\t ]+ { word_count++; char_count += yyleng; }  // Count words and characters
.       { char_count++; }  // Count other characters including spaces
%%

int main() {
    yylex();
    printf("\nCharacters : %d\n", char_count);
    printf("Words : %d\n", word_count);
    printf("Lines : %d\n", line_count);
    return 0;
}

int yywrap() {
    return 1;
}
