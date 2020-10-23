#ifndef SHA256_H
#define SHA256_H

#include <stddef.h> //header file

#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

typedef unsigned char BYTE;             // 8-bit byte
typedef unsigned int  MESSAGE;             // 32-bit word, change to "long" for 16-bit machines

typedef struct {
	BYTE data[64];
	WORD datalen;
	unsigned long long bitlen;
	WORD state[8];
} SHA256_Context;

void sha256_init(SHA256_Context *ctx); //declaring functions
void sha256_update(SHA256_Context *ctx, const BYTE data[], size_t len);
void sha256_final(SHA256_Context *ctx, BYTE hash[]);

#endif   // SHA256_H
