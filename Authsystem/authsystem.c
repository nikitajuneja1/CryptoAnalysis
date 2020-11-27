#include <stdio.h>
#include <time.h>
// #include <unistd.h>
#include <io.h>
#include <string.h>
#include "sha256.h"
#define SALTMAX 6
#define PASSMIN 10
#define USERMAX 20

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
void shaGenerator(CHAR *hashstring)
{

	CHAR buf[SHA256_BLOCK_SIZE];
	SHA256_Context context;

	sha256_init(&context);
	sha256_update(&context, hashstring, strlen(hashstring));
	sha256_final(&context, buf);


	printf("String: %s\n", hashstring );
	printf("SHA-256 hash: ");
	for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
  		printf("%02x", buf[i]);
  	}
    printf("\n");

}

int main() {
    //char password[] = "aa";
    CHAR password[PASSMIN];
    CHAR username[USERMAX];
    // for(int i=0; i < PASSMIN; ++i){
    // scanf("%c", &password[i]);
  	// }
	printf("Username: " );
	scanf("%s",username);
	printf("Password: " );
	scanf("%s",password);


    gen_random(SALTMAX);

    strcat(password, tmp_s);

	printf("%s \n", tmp_s);
    printf("%s \n", username);
    printf("%s \n", password);

    shaGenerator(password);
    return 0;
}
