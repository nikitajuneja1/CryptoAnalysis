#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "md5.h"
#include "sha1.h"
#include "sha256.h"

int test()
{
	//testcases
	CHAR text1[] = {"abc"};
	CHAR text2[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
	CHAR text3[] = {"aaaaaaaaaa"};

	//SHA256
	SHA256_Context context;
	CHAR hash1[SHA256_BLOCK_SIZE] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
									0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};
	CHAR hash2[SHA256_BLOCK_SIZE] = {0x24,0x8d,0x6a,0x61,0xd2,0x06,0x38,0xb8,0xe5,0xc0,0x26,0x93,0x0c,0x3e,0x60,0x39,
	                               	0xa3,0x3c,0xe4,0x59,0x64,0xff,0x21,0x67,0xf6,0xec,0xed,0xd4,0x19,0xdb,0x06,0xc1};
	CHAR hash3[SHA256_BLOCK_SIZE] = {0xbf,0x2c,0xb5,0x8a,0x68,0xf6,0x84,0xd9,0x5a,0x3b,0x78,0xef,0x8f,0x66,0x1c,0x9a,
	                                 0x4e,0x5b,0x09,0xe8,0x2c,0xc8,0xf9,0xcc,0x88,0xcc,0xe9,0x05,0x28,0xca,0xeb,0x27};
	CHAR buf[SHA256_BLOCK_SIZE];

	//SHA1
	SHA1Context ctx;
	CHAR hash4[SHA1HashSize] = {0xa9,0x99,0x3e,0x36,0x47,0x06,0x81,0x6a,0xba,0x3e,
								0x25,0x71,0x78,0x50,0xc2,0x6c,0x9c,0xd0,0xd8,0x9d};
	CHAR hash5[SHA1HashSize] = {0x84,0x98,0x3e,0x44,0x1c,0x3b,0xd2,0x6e,0xba,0xae,
								0x4a,0xa1,0xf9,0x51,0x29,0xe5,0xe5,0x46,0x70,0xf1};
	CHAR hash6[SHA1HashSize] = {0x34,0x95,0xff,0x69,0xd3,0x46,0x71,0xd1,0xe1,0x5b,
								0x33,0xa6,0x3c,0x13,0x79,0xfd,0xed,0xd3,0xa3,0x2a};
	CHAR buffer[SHA1HashSize];

	//MD5
	uint8_t *result;
	uint8_t hash7[MD5HashSize] = {0x90,0x01,0x50,0x98,0x3c,0xd2,0x4f,0xb0,0xd6,0x96,
								0x3f,0x7d,0x28,0xe1,0x7f,0x72};
	uint8_t hash8[MD5HashSize] = {0x82,0x15,0xef,0x07,0x96,0xa2,0x0b,0xca,0xaa,0xe1,
								0x16,0xd3,0x87,0x6c,0x66,0x4a};
	uint8_t hash9[MD5HashSize] ={0xe0,0x9c,0x80,0xc4,0x2f,0xda,0x55,0xf9,0xd9,0x92,
								0xe5,0x9c,0xa6,0xb3,0x30,0x7d};
    uint8_t md5buffer[MD5HashSize];

	int pass = 1;

	//For test1
	printf("\nString: %s\n\n", text1 );
	printf("Output for different Hash Algorithms: \n\n");
	printf("MD5: " );
	result = md5_string(text1);
	print_hash(result);
	pass = pass && !memcmp(hash7, md5buffer, MD5HashSize);


	sha1_init(&ctx);
	sha1_update(&ctx, text1, strlen(text1));
	sha1_final(&ctx, buffer);
	printf("SHA1: ");
	for(unsigned int i = 0; i < SHA1HashSize; ++i){
		printf("%02x", buffer[i]);
	}
	printf("\n");
	pass = pass && !memcmp(hash4, buffer, SHA1HashSize);


	sha256_init(&context);
	sha256_update(&context, text1, strlen(text1));
	sha256_final(&context, buf);
  	printf("SHA256: ");
	for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
			printf("%02x", buf[i]);
		}
  	printf("\n");
	pass = pass && !memcmp(hash1, buf, SHA256_BLOCK_SIZE);

	//for Test2
	printf("\nString: %s\n\n", text2 );
	printf("Output for different Hash Algorithms: \n\n");
	printf("MD5: " );
	result = md5_string(text2);
	print_hash(result);
	pass = pass && !memcmp(hash8, md5buffer, MD5HashSize);

	sha1_init(&ctx);
	sha1_update(&ctx, text2, strlen(text2));
	sha1_final(&ctx, buffer);
	printf("SHA1: ");
	for(unsigned int i = 0; i < SHA1HashSize; ++i){
		printf("%02x", buffer[i]);
	}
	printf("\n");
	pass = pass && !memcmp(hash5, buffer, SHA1HashSize);

	sha256_init(&context);
	sha256_update(&context, text2, strlen(text2));
	sha256_final(&context, buf);
  	printf("SHA256: ");
  	for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
		printf("%02x", buf[i]);
	}
  	printf("\n");
  	pass = pass && !memcmp(hash2, buf, SHA256_BLOCK_SIZE);

	//for Test3
	printf("\nString: %s\n\n", text3 );
	printf("Output for different Hash Algorithms: \n\n");
	printf("MD5: " );
	result = md5_string(text3);
	print_hash(result);
	pass = pass && !memcmp(hash9, md5buffer, MD5HashSize);

	sha1_init(&ctx);
	sha1_update(&ctx, text3, strlen(text3));
	sha1_final(&ctx, buffer);
  	printf("SHA1: ");
  	for(unsigned int i = 0; i < SHA1HashSize; ++i){
		printf("%02x", buffer[i]);
	}
  	printf("\n");
	pass = pass && !memcmp(hash6, buffer, SHA1HashSize);

	sha256_init(&context);
	sha256_update(&context, text3, strlen(text3));
	sha256_final(&context, buf);
  	printf("SHA256: ");
  	for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
		printf("%02x", buf[i]);
	}
  	printf("\n");
	pass = pass && !memcmp(hash3, buf, SHA256_BLOCK_SIZE);

	free (result);
	return(pass);
}

int main()
{
	printf("\nTests: %s\n", test() ? "FAILED" : "SUCCEEDED");
	return(0);
}
