#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "MD5.h"


/**
 * @brief Initiate a MD5 object and return its pointer.
 *
 * @return MD5* The MD5 object's pointer, NULL if the object failed to be created.
 */
MD5 *initMD5(void) {
    MD5 *obj = calloc(1, sizeof(MD5));

    if (obj == NULL) {
        return NULL;
    }

    obj->size = 0;

    printf("Init size: %llu\n", obj->size);

    if (!(obj->data_p = calloc(1, sizeof(uint8_t)))) {
        free(obj);
        return NULL;
    }

    return obj;
}


int appendMessage(MD5 *md5, uint8_t c) {
    md5->size++;

    if (!(md5->data_p = realloc(md5->data_p, md5->size * sizeof(uint8_t)))) {
        return EXIT_FAILURE;
    }

    md5->data_p[md5->size - 1] = c;
    return EXIT_SUCCESS;
}


/**
 * @brief Get the message as input and assign to object MD5. The message should be string and in ASCII.
 * Max message length is 2^64 (not including null character).
 *
 * @param md5 The MD5 object.
 * @param message The string input.
 * @return int EXIT_SUCCESS if read successfully, EXIT_FAILURE otherwise.
 */
int getMessage(MD5 *md5, uint8_t *message) {
    uint64_t messageLength = 0;

    for (uint32_t i = 0; message[i] != '\0'; i++) {
        messageLength++;
        appendMessage(md5, message[i]);
    }

    int paddingSize = 64 - (md5->size % 64);

    appendMessage(md5, 0x80);

    if (paddingSize > 8) {
        for (int i = paddingSize - 1; i > 8; i--) {
            appendMessage(md5, 0x00);
        }
    } else {
        for (int i = paddingSize - 1 + (64 - 8); i > 0; i--) {
			appendMessage(md5, 0x00);
        }
    }

    for (int i = 7; i > 0; i--) {
		appendMessage(md5, (messageLength >> (i * 8)) & 0xFF);
    }

	appendMessage(md5, messageLength & 0xFF);
    return EXIT_SUCCESS;
}
