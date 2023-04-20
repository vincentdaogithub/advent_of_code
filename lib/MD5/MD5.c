#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "MD5.h"


// magic numbers
#define A_MD5 0x67452301
#define B_MD5 0xefcdab89
#define C_MD5 0x98badcfe
#define D_MD5 0x10325476


// s-value (shift value)

// shift for 1st round
const int S1[4] = { 7, 12, 17, 22 };

// shift for 2nd round
const int S2[4] = { 5, 9, 14, 20 };

// shift for 3rd round
const int S3[4] = { 4, 11, 16, 23};

// shift for 4th round
const int S4[4] = { 6, 10, 15, 21};

/**
 * @brief Circular shift shiftAmount bits to the left.
 * 
 * @param bitsToShift 32-bit value to shift.
 * @param shiftAmount Amount of bits to shift.
 * @return uint32_t - The shifted bit.
 */
uint32_t rotateLeft(uint32_t bitsToShift, int shiftAmount) {
    return ((bitsToShift << shiftAmount) | (bitsToShift >> (sizeof(uint32_t) - shiftAmount)));
}


// k-value
uint32_t K_TABLE[64];

/**
 * @brief Initiate the k-value table, which takes the form of 2^32 * abs(sin(i + 1)) for each i-th element
 * of the table.
 *
 */
void initKTable(void) {
    for (int i = 1; i <= 64; i++) {
        double sinResult = sin(i);
        sinResult = sinResult < 0 ? -sinResult : sinResult;
        K_TABLE[i] = 4294967296 * sinResult;
    }
}


// set of 4-predefined functions for MD5 algorithm
uint32_t F(uint32_t X, uint32_t Y, uint32_t Z) {
    return ((X & Y) | (~X & Z)) ;
}

uint32_t G(uint32_t X, uint32_t Y, uint32_t Z) {
    return ((X & Z) | (Y & ~Z));
}

uint32_t H(uint32_t X, uint32_t Y, uint32_t Z) {
    return (X ^ Y ^ Z);
}

uint32_t I(uint32_t X, uint32_t Y, uint32_t Z) {
    return (Y ^ (X | ~Z));
}


/**
 * @brief Representing 512-bit block from the input data. Each will have 16 32-bits "words" to 
 * work with.
 * 
 */
typedef struct Block {
    uint32_t words[16];
} Block;


/**
 * @brief Initiate a MD5 object and return its pointer.
 *
 * @return MD5* The MD5 object's pointer, NULL if the object failed to be created.
 */
MD5 *initMD5(void) {
    initKTable();
    MD5 *obj = calloc(1, sizeof(MD5));

    if (obj == NULL) {
        return NULL;
    }

    obj->size = 0;

    if (!(obj->data_p = calloc(1, sizeof(uint8_t)))) {
        free(obj);
        return NULL;
    }

    return obj;
}


/**
 * @brief Append character/data to the MD5 data.
 *
 * @param md5 The MD5 object pointer.
 * @param c The character/data to add, in uint8_t.
 * @return int - 0 if successfully append. 1 otherwise.
 */
int appendMessage(MD5 *md5, uint8_t c) {
    if (!md5->data_p) {
        return 1;
    }

    md5->size++;

    if (!(md5->data_p = realloc(md5->data_p, md5->size * sizeof(uint8_t)))) {
        return 1;
    }

    md5->data_p[md5->size - 1] = c;
    return 0;
}


/**
 * @brief Get the message as input and assign to object MD5. The message should be string and in ASCII.
 * Max message length is 2^64 - 1 (not including null character).
 *
 * @param md5 The MD5 object.
 * @param message The string input.
 * @return int EXIT_SUCCESS if read successfully, EXIT_FAILURE otherwise.
 */
int attachMessageMD5(MD5 *md5, uint8_t *message) {
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

    messageLength *= 8;

    for (int i = 7; i > 0; i--) {
		appendMessage(md5, (messageLength >> (i * 8)) & 0xFF);
    }

	appendMessage(md5, messageLength & 0xFF);
    return EXIT_SUCCESS;
}


Block *getBlocks(MD5 *md5) {
    if (!md5) {
        return NULL;
    }

    uint64_t numBlocks = md5->size / 64;
    Block *blocks = calloc(numBlocks, sizeof(Block));

    uint64_t dataIndex = 0;

    for (int i = 0; i < numBlocks; i++) {
        for (int j = 0; j < 16; j++) {
            blocks[i].words[j] = 0;

            for (int k = 1; k <= 4; k++) {
                blocks[i].words[j] |= md5->data_p[dataIndex++] << (32 - (8 * k));
            }

            printf("%x\n", blocks[i].words[j]);
        }
    }

    return blocks;
}


/**
 * @brief Digests the message into MD5 hash.
 * 
 * @param md5 The md5 object pointer to digest.
 */
void digest(MD5 *md5) {
    Block *blocks;

    if (!(blocks = getBlocks(md5))) {
        puts("Can't process data into blocks");
        return;
    }
}
