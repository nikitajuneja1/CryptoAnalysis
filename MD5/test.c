#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "md5.h"

int main(){
	uint8_t *result;
	char text1[10000];
	printf("Enter a String: \n");
	scanf("%s\n",&text1);
	result = md5_string(text1);
	printf("\n\n\n\n\nString: %s\n", text1);
	printf("MD5 Hash: ");
	print_hash(result);
	free(result);
}
