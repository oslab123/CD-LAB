#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_ALPHABET 26

int n; // Number of states in the DFA
int finalStates[MAX_STATES], finalCount; // Final states and their count
int dfa[MAX_STATES][MAX_ALPHABET]; // DFA transition table
bool distinguishable[MAX_STATES][MAX_STATES]; // Distinguishable states matrix

// Initialize the distinguishable matrix
void initializeDistinguishable() {
    memset(distinguishable, false, sizeof(distinguishable));

    // Mark pairs (final, non-final) as distinguishable initially
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bool isIFinal = false, isJFinal = false;
            for (int k = 0; k < finalCount; k++) {
                if (finalStates[k] == i) isIFinal = true;
                if (finalStates[k] == j) isJFinal = true;
            }
            if (isIFinal != isJFinal) {
                distinguishable[i][j] = distinguishable[j][i] = true;
            }
        }
    }
}

// Minimize DFA using partition refinement
void minimizeDFA(int alphabetSize) {
    bool updated = true;
    while (updated) {
        updated = false;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (!distinguishable[i][j]) {
                    for (int k = 0; k < alphabetSize; k++) {
                        int a = dfa[i][k];
                        int b = dfa[j][k];
                        if (a >= 0 && a < n && b >= 0 && b < n && distinguishable[a][b]) {
                            distinguishable[i][j] = distinguishable[j][i] = true;
                            updated = true;
                            break;
                        }
                    }
                }
            }
        }
    }
}

// Print minimized DFA states and transitions
void printMinimizedDFA(int alphabetSize) {
    bool printed[MAX_STATES] = {false};
    int stateMapping[MAX_STATES];
    for (int i = 0; i < n; i++) stateMapping[i] = i;

    printf("Minimized DFA:\n");

    // Group equivalent states
    for (int i = 0; i < n; i++) {
        if (!printed[i]) {
            printf("Equivalent states: { ");
            for (int j = 0; j < n; j++) {
                if (!distinguishable[i][j]) {
                    printf("%d ", j);
                    printed[j] = true;
                    stateMapping[j] = i; // Map to the representative state
                }
            }
            printf("}\n");
        }
    }

    printf("Transitions in the minimized DFA:\n");
    for (int i = 0; i < n; i++) {
        if (stateMapping[i] == i) { // Print transitions for unique (representative) states only
            for (int k = 0; k < alphabetSize; k++) {
                int nextState = dfa[i][k];
                if (nextState >= 0 && nextState < n) {
                    nextState = stateMapping[nextState];
                    printf("From state %d on input %c: Go to state %d\n", i, 'a' + k, nextState);
                }
            }
        }
    }
}

int main() {
    int alphabetSize;
    printf("Enter the number of states in the DFA: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_STATES) {
        printf("Invalid number of states.\n");
        return 1;
    }

    printf("Enter the alphabet size (number of letters, e.g., 2 for a, b): ");
    if (scanf("%d", &alphabetSize) != 1 || alphabetSize <= 0 || alphabetSize > MAX_ALPHABET) {
        printf("Invalid alphabet size.\n");
        return 1;
    }

    printf("Enter the DFA transition table:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < alphabetSize; j++) {
            char inputChar = 'a' + j; // Represent alphabet letters
            printf("Transition from state %d on input %c: ", i, inputChar);
            if (scanf("%d", &dfa[i][j]) != 1 || dfa[i][j] < 0 || dfa[i][j] >= n) {
                printf("Invalid transition.\n");
                return 1;
            }
        }
    }

    printf("Enter the number of final states: ");
    if (scanf("%d", &finalCount) != 1 || finalCount < 0 || finalCount > n) {
        printf("Invalid number of final states.\n");
        return 1;
    }

    printf("Enter the final states:\n");
    for (int i = 0; i < finalCount; i++) {
        if (scanf("%d", &finalStates[i]) != 1 || finalStates[i] < 0 || finalStates[i] >= n) {
            printf("Invalid final state.\n");
            return 1;
        }
    }

    initializeDistinguishable();
    minimizeDFA(alphabetSize);
    printMinimizedDFA(alphabetSize);

    return 0;
}