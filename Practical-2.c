#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100

bool validateString(int transitions[MAX_STATES][MAX_SYMBOLS], int num_states, int num_symbols, 
                    int start_state, int accept_states[], int num_accept_states, 
                    const char *input, char symbols[]) {
    int current_state = start_state;
    
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        int symbol_index = -1;

        for (int j = 0; j < num_symbols; j++) {
            if (symbols[j] == c) {
                symbol_index = j;
                break;
            }
        }

        if (symbol_index == -1) {
            return false;
        }

        current_state = transitions[current_state][symbol_index];
    }

    for (int i = 0; i < num_accept_states; i++) {
        if (current_state == accept_states[i]) {
            return true;
        }
    }
    
    return false;
}

int main() {
    int num_symbols, num_states, start_state, num_accept_states;
    char symbols[MAX_SYMBOLS];
    int transitions[MAX_STATES][MAX_SYMBOLS];
    int accept_states[MAX_STATES];
    char input[100];

    printf("Enter the number of input symbols: ");
    scanf("%d", &num_symbols);
    printf("Enter the input symbols: ");
    for (int i = 0; i < num_symbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    printf("Enter the number of states: ");
    scanf("%d", &num_states);

    printf("Enter the transition table:\n");
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_symbols; j++) {
            printf("State %d to %c -> ", i + 1, symbols[j]);
            scanf("%d", &transitions[i][j]);
            transitions[i][j]--;
        }
    }

    printf("Enter the initial state: ");
    scanf("%d", &start_state);
    start_state--;

    printf("Enter the number of accepting states: ");
    scanf("%d", &num_accept_states);
    printf("Enter the accepting states: ");
    for (int i = 0; i < num_accept_states; i++) {
        scanf("%d", &accept_states[i]);
        accept_states[i]--;
    }

    printf("Enter the input string: ");
    scanf("%s", input);

    if (validateString(transitions, num_states, num_symbols, start_state, 
                       accept_states, num_accept_states, input, symbols)) {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }

    return 0;
}
