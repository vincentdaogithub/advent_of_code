#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "MD5.h"


int main(int argc, char const *argv[]) {
    char *testString = "They are deterministic";
    uint8_t *testInput = calloc(1, sizeof(uint8_t));
    int size = 0;

    for (int i = 0; testString[i] != '\0'; i++) {
        testInput[i] = testString[i];
        size++;
        testInput = realloc(testInput, (size + 1) * sizeof(uint8_t));
    }

    testInput[size++] = '\0';

    MD5 *test = initMD5();
    printf("Read message: %s\n", attachMessageMD5(test, testInput) == EXIT_SUCCESS ? "ok" : "failed");
    printf("Length after read: %llu\n", test->size);

    for (int i = 0; i < test->size; i++) {
        printf("%d\n", test->data_p[i]);
    }

    digest(test);

    return EXIT_SUCCESS;
}
