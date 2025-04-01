#include <stdio.h>
#include <stdbool.h>

// Function to validate the string using finite automata
bool validateString(int num_states, int num_symbols, char symbols[], int transitions[num_states][num_symbols], int start_state, int accept_states[], int num_accept_states, char input[]) {
    int current_state = start_state;

    for (int i = 0; input[i] != '\0'; i++) {
        char symbol = input[i];
        int symbol_index = -1;

        // Find the index of the symbol in the input symbols
        for (int j = 0; j < num_symbols; j++) {
            if (symbols[j] == symbol) {
                symbol_index = j;
                break;
            }
        }

        if (symbol_index == -1) {
            return false; // Invalid symbol
        }

        // Transition to the next state
        current_state = transitions[current_state][symbol_index];
        if (current_state == -1) {
            return false; // Invalid transition
        }
    }

    // Check if the final state is an accepting state
    for (int i = 0; i < num_accept_states; i++) {
        if (current_state == accept_states[i]) {
            return true;
        }
    }

    return false;
}

int main() {
    int num_symbols, num_states, start_state, num_accept_states;
    char symbols[10], input[100];

    // Input number of symbols and symbols
    printf("Number of input symbols: ");
    scanf("%d", &num_symbols);
    printf("Input symbols (space-separated): ");
    for (int i = 0; i < num_symbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    // Input number of states and transitions
    printf("Enter number of states: ");
    scanf("%d", &num_states);
    int transitions[num_states][num_symbols];

    // Initialize transitions with -1 (no transition)
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_symbols; j++) {
            transitions[i][j] = -1;
        }
    }

    printf("Enter transition table (format: state input_symbol next_state):\n");
    int state, next_state;
    char symbol;
    while (1) {
        printf("Enter transition (or type -1 to stop): ");
        scanf("%d", &state);
        if (state == -1) break;
        scanf(" %c %d", &symbol, &next_state);

        // Find index of the input symbol
        int symbol_index = -1;
        for (int i = 0; i < num_symbols; i++) {
            if (symbols[i] == symbol) {
                symbol_index = i;
                break;
            }
        }

        if (symbol_index != -1) {
            transitions[state][symbol_index] = next_state;
        }
    }

    // Input start state
    printf("Initial state: ");
    scanf("%d", &start_state);

    // Input accepting states
    printf("Number of accepting states: ");
    scanf("%d", &num_accept_states);
    int accept_states[num_accept_states];
    printf("Accepting states (space-separated): ");
    for (int i = 0; i < num_accept_states; i++) {
        scanf("%d", &accept_states[i]);
    }

    // Input string to validate
    printf("Input string: ");
    scanf("%s", input);

    // Validate the string
    if (validateString(num_states, num_symbols, symbols, transitions, start_state, accept_states, num_accept_states, input)) {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }

    return 0;
}
