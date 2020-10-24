#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "sha1.h"

int sha1_test()
{
	//test cases
	CHAR text1[] = {"abc"};
	CHAR text2[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
	CHAR text3[] = {"aaaaaaaaaa"};
	//pre-computed hash value
	CHAR hash1[SHA1HashSize] = {0xa9,0x99,0x3e,0x36,0x47,0x06,0x81,0x6a,0xba,0x3e,0x25,0x71,0x78,0x50,0xc2,0x6c,0x9c,0xd0,0xd8,0x9d};
	CHAR hash2[SHA1HashSize] = {0x84,0x98,0x3e,0x44,0x1c,0x3b,0xd2,0x6e,0xba,0xae,0x4a,0xa1,0xf9,0x51,0x29,0xe5,0xe5,0x46,0x70,0xf1};
	CHAR hash3[SHA1HashSize] = {0x34,0x95,0xff,0x69,0xd3,0x46,0x71,0xd1,0xe1,0x5b,0x33,0xa6,0x3c,0x13,0x79,0xfd,0xed,0xd3,0xa3,0x2a};
	CHAR buf[SHA1HashSize];
	int idx;
	SHA1Context context;
	int pass = 1;
  CHAR *result;

	sha1_init(&context);
	sha1_update(&context, text1, strlen(text1));
	sha1_final(&context, buf);
  printf("%s\n", text1 );
  for(unsigned int i = 0; i < SHA1HashSize; ++i){
		printf("%02x", buf[i]);
	}
  printf("\n");
	pass = pass && !memcmp(hash1, buf, SHA1HashSize);


	sha1_init(&context);
	sha1_update(&context, text2, strlen(text2));
	sha1_final(&context, buf);
  printf("%s\n", text2 );
  for(unsigned int i = 0; i < SHA1HashSize; ++i){
		printf("%02x", buf[i]);
	}
  printf("\n");
  pass = pass && !memcmp(hash2, buf, SHA1HashSize);


	sha1_init(&context);
	sha1_update(&context, text3, strlen(text3));
	sha1_final(&context, buf);
  printf("%s\n", text3);
  for(unsigned int i = 0; i < SHA1HashSize; ++i){
		printf("%02x", buf[i]);
	}
  printf("\n");
	pass = pass && !memcmp(hash3, buf, SHA1HashSize);

	return(pass);
}

int main()
{
	printf("SHA1 tests: %s\n", sha1_test() ? "SUCCEEDED" : "FAILED");

	return(0);
}
