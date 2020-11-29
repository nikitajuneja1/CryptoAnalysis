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
CHAR buf[SHA256_BLOCK_SIZE];

// Random String Generator
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

	// CHAR buf[SHA256_BLOCK_SIZE];
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

    // File Input 
    FILE *fp;

    int userFlag=0;

    while(userFlag==0){
        printf("Username: " );
        scanf("%s",username);
        
        //For searching username
        char username_file_location[] ="usernames.txt";
        char fileUser[30];
        fp = fopen(username_file_location, "a+");

        while(!feof(fp)){

            fscanf(fp,"%s",fileUser);

            if(strcmp(fileUser,username)==0){
                printf("This username already exists.\n");
                userFlag=0;
                break;
            }
            else{
                userFlag=1;
                continue;
            }
        }

        fprintf(fp, "%s\n", username);
        fclose(fp);

    }


    printf("Password: " );
	scanf("%s",password);


    gen_random(SALTMAX);

    strcat(password, tmp_s);

	printf("%s \n", tmp_s);
    printf("%s \n", username);
    printf("%s \n", password);

    shaGenerator(password);


    //Signup
    if(userFlag==1){
        char pass_file_location[] ="passwords.txt";

        fp = fopen(pass_file_location,"a+");

        fprintf(fp, "%s %s ", username, tmp_s);

        for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
            fprintf(fp, "%02x", buf[i]);
        }
        
        fprintf(fp,"\n");
        
        printf("Signed Up successfully");
        fclose(fp);
    }

    return 0;
}
