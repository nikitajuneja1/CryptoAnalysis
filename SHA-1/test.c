#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "sha1.h"

void sha1_test()
{

	CHAR buf[SHA1HashSize];
	SHA1Context context;
	CHAR text1[10000];

	printf("Enter a string:\n");
	scanf("%s\n", &text1);

	sha1_init(&context);
	sha1_update(&context, text1, strlen(text1));
	sha1_final(&context, buf);


	printf("\n\n\n\nString: %s\n", text1 );
	printf("SHA-1 hash: ");
  	for(unsigned int i = 0; i < SHA1HashSize; ++i){
		printf("%02x", buf[i]);
	}
  	printf("\n");

}

int main()
{
	sha1_test();
	return(0);
}
