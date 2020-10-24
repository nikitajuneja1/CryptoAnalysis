#ifndef SHA1_H
#define SHA1_H

//Header files and macros
#include <stddef.h>

#define SHA1HashSize 20              // SHA1 outputs a 20 byte digest

typedef unsigned char CHAR;             // 8-bit byte
typedef unsigned int  INT;             // 32-bit word, change to "long" for 16-bit machines

typedef struct {
	CHAR data[64];
	INT length;
	unsigned long long bitlen;
	INT Hash[5];
	INT constant[4];
} SHA1Context;

//FUNCTION DEFINITIONS
void sha1_init(SHA1Context *context);
void sha1_update(SHA1Context *context, const CHAR data[], size_t len);
void sha1_final(SHA1Context *context, CHAR hash[]);

#endif   // SHA1_H
