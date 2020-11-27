#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "sha256.c"
#include "sha256.h"
#define SALTMAX 6
#define PASSMAX 10
char tmp_s[];
void gen_random(const int len) {

    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    srand((unsigned) time(NULL) * getpid());


    for (int i = 0; i < len; ++i)
        tmp_s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

}
void shaGenerator(char *hashstring)
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

int main() {
    //char password[] = "aa";
    CHAR password[PASSMAX];
    for(int i=0; i < PASSMAX; ++i){
    scanf("%c", &password[i]);
  }
    gen_random(SALTMAX);
    strcat(password, tmp_s);
    printf("%s \n", tmp_s);
    printf("%s \n", password);
    shaGenerator(password);
    return 0;
}
