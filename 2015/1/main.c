#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILENAME "input.txt"


int main(int agrc, char *argv[]) {
	FILE *input_p = fopen(FILENAME, "r");

	if (!input_p) {
		puts("Can't read input file");
		return EXIT_FAILURE;
	}

	int floor = 0, position = 1;
	bool firstTimeBasement = false;
	int character;

	while ((character = fgetc(input_p)) != EOF) {
		switch (character) {
			case '(':
				floor++;
				break;

			case ')':
				floor--;
				break;

			default:
				puts("\nFile format corrupted. Should contain either \"(\" or \")\".");
				fclose(input_p);
				return EXIT_FAILURE;
		}

		if (floor < 0) {
			firstTimeBasement = true;
		}

		if (!firstTimeBasement) {
			position++;
		}
	}

	printf("Floor reached: %d\n", floor);
	printf("Reach basement 1st time at: %d\n", position);
	fclose(input_p);
	return EXIT_SUCCESS;
}
