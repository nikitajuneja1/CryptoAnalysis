#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "sha256.h"


int sha256_test()
{
	CHAR text1[] = {"abc"};
	CHAR text2[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
	CHAR text3[] = {"aaaaaaaaaa"};
	CHAR hash1[SHA256_BLOCK_SIZE] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
																		0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};
	CHAR hash2[SHA256_BLOCK_SIZE] = {0x24,0x8d,0x6a,0x61,0xd2,0x06,0x38,0xb8,0xe5,0xc0,0x26,0x93,0x0c,0x3e,0x60,0x39,
	                               	0xa3,0x3c,0xe4,0x59,0x64,0xff,0x21,0x67,0xf6,0xec,0xed,0xd4,0x19,0xdb,0x06,0xc1};
	CHAR hash3[SHA256_BLOCK_SIZE] = {0xbf,0x2c,0xb5,0x8a,0x68,0xf6,0x84,0xd9,0x5a,0x3b,0x78,0xef,0x8f,0x66,0x1c,0x9a,
	                                 0x4e,0x5b,0x09,0xe8,0x2c,0xc8,0xf9,0xcc,0x88,0xcc,0xe9,0x05,0x28,0xca,0xeb,0x27};
	CHAR buf[SHA256_BLOCK_SIZE];
	int idx;
	SHA256_Context context;
	int pass = 1;

	sha256_init(&context);
	sha256_update(&context, text1, strlen(text1));
	sha256_final(&context, buf);
  printf("%s\n", text1 );
  for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
		printf("%02x", buf[i]);
	}
  printf("\n");
	pass = pass && !memcmp(hash1, buf, SHA256_BLOCK_SIZE);

	sha256_init(&context);
	sha256_update(&context, text2, strlen(text2));
	sha256_final(&context, buf);
  printf("%s\n", text2 );
  for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
		printf("%02x", buf[i]);
	}
  printf("\n");
  pass = pass && !memcmp(hash2, buf, SHA256_BLOCK_SIZE);


	sha256_init(&context);
	sha256_update(&context, text3, strlen(text3));
	sha256_final(&context, buf);
  printf("%s\n", text3);
  for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
		printf("%02x", buf[i]);
	}
  printf("\n");
	pass = pass && !memcmp(hash3, buf, SHA256_BLOCK_SIZE);

	return(pass);
}

int main()
{
	printf("SHA256 tests: %s\n", sha256_test() ? "SUCCEEDED" : "FAILED");

	return(0);
}
