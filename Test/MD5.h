#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MD5HashSize 16      //MD5 ouputs 16 bytes digest

typedef struct {
	uint64_t size;			// Size of input in bytes
	uint32_t buffer[4];		// Current accumulation of hash
	uint8_t input[64];		// Input to be used in the next step
	uint8_t digest[16];		// Result of algorithm
} md5_context;

void md5_init(md5_context *ctx);
void md5_update(md5_context *ctx, uint8_t *input, size_t input_len);
void md5_finalize(md5_context *ctx);
void md5_steps(uint32_t *buffer, uint32_t *input);

uint8_t* md5_string(char *input);
uint8_t* md5_file(FILE *file);

uint32_t F(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t G(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t H(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t I(uint32_t X, uint32_t Y, uint32_t Z);

uint32_t rotate_left(uint32_t x, uint32_t n);

void print_bytes(void *p, size_t length);
void print_hash(uint8_t *p);
