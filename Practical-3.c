#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TOKEN_LEN 100
#define MAX_SYMBOLS 100

typedef struct {
    char identifier[MAX_TOKEN_LEN];
} Symbol;

Symbol symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

int isKeyword(const char *word);
int isOperator(char ch);
int isPunctuation(char ch);
int isValidIdentifier(const char *word);
void addSymbol(const char *identifier);
void printSymbolTable();

int main() {
    char input[1000];
    printf("Enter the C source code:\n");
    fgets(input, sizeof(input), stdin);

    int i = 0, len = strlen(input);
    char token[MAX_TOKEN_LEN];
    int tokenIndex = 0;

    printf("\nTOKENS:\n");

    while (i < len) {
      
        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (isalpha(input[i]) || input[i] == '_') {
            tokenIndex = 0;
            while (isalnum(input[i]) || input[i] == '_') {
                token[tokenIndex++] = input[i++];
            }
            token[tokenIndex] = '\0';

            if (isKeyword(token)) {
                printf("Keyword: %s\n", token);
            } else if (isValidIdentifier(token)) {
                printf("Identifier: %s\n", token);
                addSymbol(token);
            } else {
                printf("LEXICAL ERROR: %s invalid lexeme\n", token);
            }
        }
       
        else if (isdigit(input[i])) {
            tokenIndex = 0;
            while (isalnum(input[i]) || input[i] == '.') {
                token[tokenIndex++] = input[i++];
            }
            token[tokenIndex] = '\0';

            if (isdigit(token[0]) && isalpha(token[strlen(token) - 1])) {
                printf("LEXICAL ERROR: %s invalid lexeme\n", token);
            } else {
                printf("Constant: %s\n", token);
            }
        }
     
        else if (isOperator(input[i])) {
            printf("Operator: %c\n", input[i]);
            i++;
        }
    
        else if (isPunctuation(input[i])) {
            printf("Punctuation: %c\n", input[i]);
            i++;
        }
       
        else if (input[i] == '\'' || input[i] == '"') {
            char quote = input[i++];
            tokenIndex = 0;
            while (input[i] != quote && input[i] != '\0') {
                token[tokenIndex++] = input[i++];
            }
            if (input[i] == quote) {
                token[tokenIndex++] = quote;
                i++;
                token[tokenIndex] = '\0';
                printf("String: %s\n", token);
            } else {
                printf("LEXICAL ERROR: Unterminated string\n");
            }
        }
     
        else if (input[i] == '/' && input[i + 1] == '/') {
            while (input[i] != '\n' && input[i] != '\0') {
                i++;
            }
        } else if (input[i] == '/' && input[i + 1] == '*') {
            i += 2;
            while (input[i] != '\0' && !(input[i] == '*' && input[i + 1] == '/')) {
                i++;
            }
            if (input[i] == '*') i += 2;
        }
        
        else {
            printf("LEXICAL ERROR: Invalid character '%c'\n", input[i]);
            i++;
        }
    }

    printf("\nSYMBOL TABLE ENTRIES:\n");
    printSymbolTable();

    return 0;
}

int isKeyword(const char *word) {
    const char *keywords[] = {"int", "char", "return", "if", "else", "while", "for"};
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=';
}

int isPunctuation(char ch) {
    return ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ';' || ch == ',';
}

int isValidIdentifier(const char *word) {
    if (isdigit(word[0])) {
        return 0;
    }
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isalnum(word[i]) && word[i] != '_') {
            return 0;
        }
    }
    return 1;
}

void addSymbol(const char *identifier) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].identifier, identifier) == 0) {
            return;
        }
    }
    strcpy(symbolTable[symbolCount++].identifier, identifier);
}

void printSymbolTable() {
    for (int i = 0; i < symbolCount; i++) {
        printf("%d) %s\n", i + 1, symbolTable[i].identifier);
    }
}
