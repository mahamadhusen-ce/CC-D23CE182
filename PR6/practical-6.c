// E → TE'
// E' → +TE' | ^
// T → FT'
// T' → *FT'
// F → ( E ) | digit


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char input[100];
int pos = 0; 

void E();
void E_();
void T();
void T_();
void F();

void error() {
    printf("Invalid string\n");
    exit(0);
}


void match(char expected) {
    if (input[pos] == expected) {
        pos++;
    } else {
        error();
    }
}


void E() {
    T();
    E_();
}

void E_() {
    if (input[pos] == '+') {
        match('+');
        T();
        E_();
    }
}

void T() {
    F();
    T_();
}

void T_() {
    if (input[pos] == '*') {
        match('*');
        F();
        T_();
    }
}

void F() {
    if (isdigit(input[pos])) {
        match(input[pos]);  
    } else if (input[pos] == '(') {
        match('(');
        E();
        match(')');
    } else {
        error();
    }
}

int main() {
    printf("Enter input string: ");
    scanf("%s", input);

    E(); 

    if (input[pos] == '\0') {  
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }

    return 0;
}

