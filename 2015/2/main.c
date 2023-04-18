#include <stdio.h>
#include <stdlib.h>

#define FILENAME "input.txt"
#define MAX_BUFFER 20


int main(int agrc, char *agrv[]) {
    FILE *input_p = fopen(FILENAME, "r");

    if (!input_p) {
		puts("Can't open file.");
		return EXIT_FAILURE;
    }

    char line[MAX_BUFFER];
    int totalArea = 0, totalRibbonLength = 0;

    while (fgets(line, MAX_BUFFER, input_p)) {
		int length, width, height;
		int status = sscanf(line, "%dx%dx%d", &length, &width, &height);

		if (status != 3) {
			puts("File corrupted.");
			fclose(input_p);
			return EXIT_FAILURE;
		}

		int firstMin = (length < width) ? length : width;
		int secondMin;

		if (firstMin == length) {
			secondMin = (width < height) ? width : height;
		} else {
			secondMin = (length < height) ? length : height;
		}

		int minArea = firstMin * secondMin;
		totalArea += 2 * length * width + 2 * length * height + 2 * width * height + minArea;
		totalRibbonLength += length * width * height + firstMin * 2 + secondMin * 2;
    }

    fclose(input_p);
    printf("Total area: %d\n", totalArea);
    printf("Total ribbon length: %d\n", totalRibbonLength);
    return EXIT_SUCCESS;
}
