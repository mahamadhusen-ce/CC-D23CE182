#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

char productions[MAX][MAX] = {
    "S=ABC|D",
    "A=a|#",
    "B=b|#",
    "C=(S)|c",
    "D=AC"
};

char first[MAX][MAX], follow[MAX][MAX];
int n = 5;

void addToSet(char set[], char val) {
    if (strchr(set, val) == NULL) {
        int len = strlen(set);
        set[len] = val;
        set[len + 1] = '\0';
    }
}

void computeFirst() {
    for (int i = 0; i < n; i++) {
        char nonTerminal = productions[i][0];
        for (int j = 2; productions[i][j] != '\0'; j++) {
            if (productions[i][j] == '|') continue;
            if (productions[i][j] >= 'a' && productions[i][j] <= 'z' || productions[i][j] == '(' || productions[i][j] == ')') {
                addToSet(first[nonTerminal - 'A'], productions[i][j]);
                break;
            } else {
                int k;
                for (k = 0; k < n; k++) {
                    if (productions[k][0] == productions[i][j]) break;
                }
                if (strchr(first[productions[k][0] - 'A'], '#') == NULL)
                    strcat(first[nonTerminal - 'A'], first[productions[k][0] - 'A']);
            }
        }
    }
}

void computeFollow() {
    follow['S' - 'A'][0] = '$';
    follow['S' - 'A'][1] = '\0';
    
    for (int i = 0; i < n; i++) {
        char nonTerminal = productions[i][0];
        for (int j = 2; productions[i][j] != '\0'; j++) {
            if (productions[i][j] >= 'A' && productions[i][j] <= 'Z') {
                if (productions[i][j + 1] >= 'a' && productions[i][j + 1] <= 'z' || productions[i][j + 1] == '(' || productions[i][j + 1] == ')') {
                    addToSet(follow[productions[i][j] - 'A'], productions[i][j + 1]);
                } else {
                    strcat(follow[productions[i][j] - 'A'], first[productions[i][j + 1] - 'A']);
                    if (strchr(first[productions[i][j + 1] - 'A'], '#')) {
                        strcat(follow[productions[i][j] - 'A'], follow[nonTerminal - 'A']);
                    }
                }
            }
        }
    }
}

void printSets() {
    for (int i = 0; i < n; i++) {
        char nonTerminal = productions[i][0];
        printf("First(%c) = { %s }\n", nonTerminal, first[nonTerminal - 'A']);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        char nonTerminal = productions[i][0];
        printf("Follow(%c) = { %s }\n", nonTerminal, follow[nonTerminal - 'A']);
    }
}

int main() {
    computeFirst();
    computeFollow();
    printSets();
    return 0;
}
