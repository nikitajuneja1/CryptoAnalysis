#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "sha256.h"

void sha256_test()
{

	CHAR buf[SHA256_BLOCK_SIZE];
	SHA256_Context context;
	CHAR text1[10000];

	printf("Enter a string:\n");
	scanf("%s\n", &text1);

	sha256_init(&context);
	sha256_update(&context, text1, strlen(text1));
	sha256_final(&context, buf);


	printf("\n\n\n\nString: %s\n", text1 );
	printf("SHA-256 hash: ");
	for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
  		printf("%02x", buf[i]);
  	}
    printf("\n");

}

int main()
{
	sha256_test();
	return(0);
}
