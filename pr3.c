//practical 3
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_LENGTH 50

typedef struct {
    char type[MAX_LENGTH];
    char value[MAX_LENGTH];
} Token;

Token tokens[MAX_TOKENS];
int token_count = 0;
char symbol_table[MAX_TOKENS][MAX_LENGTH];
int symbol_count = 0;

const char *keywords[] = {"int", "char", "return", "void", "struct", "long", "float", "scanf", "printf"};
const char operators[] = "+-*/=%";
const char punctuations[] = "(){};,[]";

int is_keyword(const char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_operator(char ch) {
    return strchr(operators, ch) != NULL;
}

int is_punctuation(char ch) {
    return strchr(punctuations, ch) != NULL;
}

void add_to_symbol_table(const char *identifier) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i], identifier) == 0) {
            return;
        }
    }
    strcpy(symbol_table[symbol_count++], identifier);
}

void add_token(const char *type, const char *value) {
    strcpy(tokens[token_count].type, type);
    strcpy(tokens[token_count].value, value);
    token_count++;
}

void process_source_code(const char *source_code) {
    char buffer[MAX_LENGTH];
    int i = 0, j = 0;

    while (source_code[i] != '\0') {
        if (isspace(source_code[i])) {
            i++;
            continue;
        }

        if (isalpha(source_code[i]) || source_code[i] == '_') {
            j = 0;
            while (isalnum(source_code[i]) || source_code[i] == '_') {
                buffer[j++] = source_code[i++];
            }
            buffer[j] = '\0';

            if (is_keyword(buffer)) {
                add_token("Keyword", buffer);
            } else {
                add_token("Identifier", buffer);
                add_to_symbol_table(buffer);
            }
        } else if (isdigit(source_code[i])) {
            j = 0;
            while (isdigit(source_code[i])) {
                buffer[j++] = source_code[i++];
            }
            buffer[j] = '\0';
            add_token("Constant", buffer);
        } else if (source_code[i] == '"' || source_code[i] == '\'') {
            char quote = source_code[i++];
            j = 0;
            buffer[j++] = quote;
            while (source_code[i] != quote && source_code[i] != '\0') {
                buffer[j++] = source_code[i++];
            }
            if (source_code[i] == quote) {
                buffer[j++] = source_code[i++];
                buffer[j] = '\0';
                add_token("String", buffer);
            } else {
                add_token("Error", "Unterminated string");
            }
        } else if (is_operator(source_code[i])) {
            buffer[0] = source_code[i++];
            buffer[1] = '\0';
            add_token("Operator", buffer);
        } else if (is_punctuation(source_code[i])) {
            buffer[0] = source_code[i++];
            buffer[1] = '\0';
            add_token("Punctuation", buffer);
        } else {
            buffer[0] = source_code[i++];
            buffer[1] = '\0';
            add_token("Error", buffer);
        }
    }
}

void print_tokens() {
    printf("TOKENS\n");
    for (int i = 0; i < token_count; i++) {
        printf("%s: %s\n", tokens[i].type, tokens[i].value);
    }
}

void print_symbol_table() {
    printf("\nSYMBOL TABLE ENTRIES\n");
    for (int i = 0; i < symbol_count; i++) {
        printf("%d) %s\n", i + 1, symbol_table[i]);
    }
}

int main() {
    char source_code[1000];

    printf("Enter the C source code (end with an empty line):\n");
    char line[MAX_LENGTH];
    source_code[0] = '\0';

    while (fgets(line, MAX_LENGTH, stdin)) {
        if (strcmp(line, "\n") == 0) {
            break;
        }
        strcat(source_code, line);
    }

    process_source_code(source_code);
    print_tokens();
    print_symbol_table();

    return 0;
}  
