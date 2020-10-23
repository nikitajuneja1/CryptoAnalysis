#ifndef SHA256_H
#define SHA256_H

#include <stddef.h> //header file

#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

typedef unsigned char CHAR;             // 8-bit byte
typedef unsigned int  INT;             // 32-bit word, change to "long" for 16-bit machines

typedef struct {
	CHAR data[64];
	INT length;
	unsigned long long bitlen;
	INT Hash[8];
} SHA256_Context;

void sha256_init(SHA256_Context *context); //declaring functions
void sha256_update(SHA256_Context *context, const CHAR data[], size_t len);
void sha256_final(SHA256_Context *context, CHAR hash[]);

#endif   // SHA256_H
