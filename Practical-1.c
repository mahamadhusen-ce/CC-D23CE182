#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool validateString(const char* str) {
	int i = 0;


	while (str[i] == 'a') {
		i++;
	}
	if (str[i] == 'b' && str[i + 1] == 'b' && str[i + 2] == '\0') {
		return true;
	}

	return false;
}

int main() {
	char input[100];

	printf("Enter a string: ");
	if (fgets(input, sizeof(input), stdin) == NULL) {
		printf("Invalid input.\n");
		return 1;
	}
	input[strcspn(input, "\n")] = '\0';
	if (validateString(input)) {
		printf("Valid String\n");
	} else {
		printf("Invalid String\n");
	}

	return 0;
}
