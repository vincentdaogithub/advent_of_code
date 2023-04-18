#include <stdio.h>
#include <stdlib.h>

#define FILENAME "input.txt"


char *getFileInput() {
	FILE *input_p = fopen(FILENAME, "r");

	if (!input_p) {
		puts("Can't open file.");
		return NULL;
	}

	int c;
	char *input = (char*) calloc(1, sizeof(char));
	unsigned size = 0;

	while ((c = fgetc(input_p)) != EOF) {
		*(input + size++) = c;
		input = (char*) realloc(input, (size + 1) * sizeof(char));
	}

	*(input + size) = '\0';
	fclose(input_p);

	return input;
}

int getVisitedHouse(char *input) {
	int houseVisited = 1, coordinateX = 100, coordinateY = 100;
	int map[201][201] = {0};
	map[100][100] = 1;

	for (int i = 0; input[i] != '\0'; i++) {
		switch (input[i]) {
			case '<':
				coordinateX--;
				break;

			case '>':
				coordinateX++;
				break;

			case '^':
				coordinateY++;
				break;

			case 'v':
				coordinateY--;
				break;
		}

		if (!map[coordinateY][coordinateX]) {
			map[coordinateY][coordinateX]++;
			houseVisited++;
		}
	}

	return houseVisited;
}

int getVisitedHouseWithRobo(char *input) {
	int houseVisited = 1, santaX = 100, santaY = 100, roboX = 100, roboY = 100, isSantaTurn = 1;
	int map[201][201] = {0};
	map[100][100] = 1;

	for (int i = 0; input[i] != '\0'; i++) {
		switch (input[i]) {
			case '<':
				if (isSantaTurn) {
					santaX--;
				} else {
					roboX--;
				}

				break;

			case '>':
				if (isSantaTurn) {
					santaX++;
				} else {
					roboX++;
				}

				break;

			case '^':
				if (isSantaTurn) {
					santaY++;
				} else {
					roboY++;
				}

				break;

			case 'v':
				if (isSantaTurn) {
					santaY--;
				} else {
					roboY--;
				}

				break;
		}

		if (isSantaTurn && !map[santaY][santaX]) {
			map[santaY][santaX]++;
			houseVisited++;
		} else if (!isSantaTurn && !map[roboY][roboX]) {
			map[roboY][roboX]++;
			houseVisited++;
		}

		isSantaTurn = isSantaTurn ? 0 : 1;
	}

	return houseVisited;
}

void runTestPart1(char *input, int expectedResult) {
	int result = getVisitedHouse(input);
	printf("Input: %s\nResult: %d\nExpected: %d\nConclusion: %s\n\n", input, result, expectedResult, result == expectedResult ? "passed" : "failed");
}

void runTestPart2(char *input, int expectedResult) {
	int result = getVisitedHouseWithRobo(input);
	printf("Input: %s\nResult: %d\nExpected: %d\nConclusion: %s\n\n", input, result, expectedResult, result == expectedResult ? "passed" : "failed");
}

void testPart1() {
	char *test1 = ">";
	char *test2 = "^>v<";
	char *test3 = "^v^v^v^v^v";

	runTestPart1(test1, 2);
	runTestPart1(test2, 4);
	runTestPart1(test3, 2);
}

void testPart2() {
	char *test1 = "^v";
	char *test2 = "^>v<";
	char *test3 = "^v^v^v^v^v";

	runTestPart2(test1, 3);
	runTestPart2(test2, 3);
	runTestPart2(test3, 11);
}

int runPart1() {
	char *input = getFileInput();
	printf("House visited: %d\n", getVisitedHouse(input));
    return EXIT_SUCCESS;
}

int runPart2() {
	char *input = getFileInput();
	printf("House visited with robo: %d\n", getVisitedHouseWithRobo(input));
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
	puts("---------------------------------------------------");
	testPart1();
	runPart1();

	puts("---------------------------------------------------");
	testPart2();
	runPart2();
}
