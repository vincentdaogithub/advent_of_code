#ifndef MD5_H
#define MD5_H

#include <stdint.h>

/**
 * @brief MD5 object to use for MD5 hash.
 *
 */
typedef struct MD5 {
    uint8_t  *data_p;
    uint64_t size;
} MD5;

/**
 * @brief Initiate a MD5 object and return its pointer.
 *
 * @return MD5* - The MD5 object's pointer, NULL if the object failed to be created.
 */
MD5 *initMD5(void);

/**
 * @brief Get the message as input and assign to object MD5. The message should be string and in ASCII.
 * Max message length is 2^64 (not including null character).
 *
 * @param md5 The MD5 object.
 * @param message The string input.
 * @return int - EXIT_SUCCESS if read successfully, EXIT_FAILURE otherwise.
 */
int attachMessageMD5(MD5 *md5, uint8_t *message);

/**
 * @brief Digests the message into MD5 hash.
 * 
 * @param md5 The md5 object pointer to digest.
 */
void digest(MD5 *md5);

#endif  // MD5_H
