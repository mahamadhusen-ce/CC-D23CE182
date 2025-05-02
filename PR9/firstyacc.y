%{
	#include<stdio.h>
	#include<stdlib.h> 
%}

%token a b i t e NL 

%% 
stmt: S NL {printf("\n-> Valid string!\n");exit(0);}
;
S: i E t S Sdash  
| 
a  
;
Sdash: e S 
| 
; 
E: b 
; 

%%
int yyerror(char *msg) 
{ 
	printf("\n-> Invalid string!!\n");  
	exit(0); 
} 
//driver code  
int main() 
{ 
	printf("Enter the string -> ");  
	yyparse(); 
	return 0; 
}
