%option noyywrap
%{
	#include<stdio.h>
	#include "firstyacc.tab.h" 
%}

%%
[i] {return i;}
[t] {return t;} 
[a] {return a;} 
[b] {return b;} 
[e] {return e;} 
\n {return NL;} 
. {return yytext[0];} 
%%
int yywrap1() 
{ 
return 1; 
}