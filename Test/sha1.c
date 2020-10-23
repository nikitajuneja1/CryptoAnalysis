#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "sha1.h"

/****************************** MACROS ******************************/
#define ROTLEFT(a, b) ((a << b) | (a >> (32 - b)))

/*********************** FUNCTION DEFINITIONS ***********************/
void sha1_transform(SHA1Context *context, const CHAR data[])
{
	INT a, b, c, d, e, i, j, t, m[80];

	for (i = 0, j = 0; i < 16; ++i, j += 4)
		m[i] = (data[j] << 24) + (data[j + 1] << 16) + (data[j + 2] << 8) + (data[j + 3]);
	for ( ; i < 80; ++i) {
		m[i] = (m[i - 3] ^ m[i - 8] ^ m[i - 14] ^ m[i - 16]);
		m[i] = (m[i] << 1) | (m[i] >> 31);
	}

	a = context->Hash[0];
	b = context->Hash[1];
	c = context->Hash[2];
	d = context->Hash[3];
	e = context->Hash[4];

	for (i = 0; i < 20; ++i) {
		t = ROTLEFT(a, 5) + ((b & c) ^ (~b & d)) + e + context->constant[0] + m[i];
		e = d;
		d = c;
		c = ROTLEFT(b, 30);
		b = a;
		a = t;
	}
	for ( ; i < 40; ++i) {
		t = ROTLEFT(a, 5) + (b ^ c ^ d) + e + context->constant[1] + m[i];
		e = d;
		d = c;
		c = ROTLEFT(b, 30);
		b = a;
		a = t;
	}
	for ( ; i < 60; ++i) {
		t = ROTLEFT(a, 5) + ((b & c) ^ (b & d) ^ (c & d))  + e + context->constant[2] + m[i];
		e = d;
		d = c;
		c = ROTLEFT(b, 30);
		b = a;
		a = t;
	}
	for ( ; i < 80; ++i) {
		t = ROTLEFT(a, 5) + (b ^ c ^ d) + e + context->constant[3] + m[i];
		e = d;
		d = c;
		c = ROTLEFT(b, 30);
		b = a;
		a = t;
	}

	context->Hash[0] += a;
	context->Hash[1] += b;
	context->Hash[2] += c;
	context->Hash[3] += d;
	context->Hash[4] += e;
}

void sha1_init(SHA1Context *context)
{
	context->length = 0;
	context->bitlen = 0;
	context->Hash[0] = 0x67452301;
	context->Hash[1] = 0xEFCDAB89;
	context->Hash[2] = 0x98BADCFE;
	context->Hash[3] = 0x10325476;
	context->Hash[4] = 0xc3d2e1f0;
	context->constant[0] = 0x5a827999;
	context->constant[1] = 0x6ed9eba1;
	context->constant[2] = 0x8f1bbcdc;
	context->constant[3] = 0xca62c1d6;
}

void sha1_update(SHA1Context *context, const CHAR data[], size_t len)
{
	size_t i;

	for (i = 0; i < len; ++i) {
		context->data[context->length] = data[i];
		context->length++;
		if (context->length == 64) {
			sha1_transform(context, context->data);
			context->bitlen += 512;
			context->length = 0;
		}
	}
}

void sha1_final(SHA1Context *context, CHAR hash[])
{
	INT i;

	i = context->length;

	// Pad whatever data is left in the buffer.
	if (context->length < 56) {
		context->data[i++] = 0x80;
		while (i < 56)
			context->data[i++] = 0x00;
	}
	else {
		context->data[i++] = 0x80;
		while (i < 64)
			context->data[i++] = 0x00;
		sha1_transform(context, context->data);
		memset(context->data, 0, 56);
	}

	// Append to the padding the total message's length in bits and transform.
	context->bitlen += context->length * 8;
	context->data[63] = context->bitlen;
	context->data[62] = context->bitlen >> 8;
	context->data[61] = context->bitlen >> 16;
	context->data[60] = context->bitlen >> 24;
	context->data[59] = context->bitlen >> 32;
	context->data[58] = context->bitlen >> 40;
	context->data[57] = context->bitlen >> 48;
	context->data[56] = context->bitlen >> 56;
	sha1_transform(context, context->data);

	// Since this implementation uses little endian byte ordering and MD uses big endian,
	// reverse all the bytes when copying the final Hash to the output hash.
	for (i = 0; i < 4; ++i) {
		hash[i]      = (context->Hash[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4]  = (context->Hash[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8]  = (context->Hash[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (context->Hash[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (context->Hash[4] >> (24 - i * 8)) & 0x000000ff;
	}
}
// CHAR* sha1_string(char *input){
// 	SHA1Context context;
//   CHAR buf[SHA1HashSize];
//   sha1_init(&context);
// 	sha1_update(&context, (const CHAR)input, strlen(input));
// 	sha1_final(&context, buf);
//
// 	CHAR *result = malloc(20);
// 	memcpy(result, context.hash, 20);
// 	return result;
// }
// void print_hash(CHAR *p){
// 	for(unsigned int i = 0; i < 20; ++i){
// 		printf("%02x", p[i]);
// 	}
// 	printf("\n");
// }
