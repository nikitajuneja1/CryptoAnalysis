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


	// printf("String: %s\n", hashstring );
	// printf("SHA-256 hash: ");
	// for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
  	// 	printf("%02x", buf[i]);
  	// }
    
    printf("\n");

}

int main(){

    int choice;
    FILE *fp;
    CHAR password[10];
    CHAR username[20];
    
    printf("Welcome!\n\t1.SignUp\n\t2.SignIn\n\t3.Exit\n");
    scanf("%d", &choice);

    if(choice==1){

            // FILE *fp;
            int userFlag=0;
            // New User
            while(userFlag==0){
                printf("Username: " );
                scanf("%s",username);
                
                //For searching username
                char username_file_location[] ="usernames.txt";
                char fileUser[USERMAX];
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
            exit(0);

    }
    if(choice == 3 ){
        exit(0);
    }
    
                printf("Username: " );
                scanf("%s",username);
                printf("Password: " );
                scanf("%s",password);

    
            // fp1 = fopen(password_file_location, "r");
            char fileUser[20];
            CHAR tempPassword[10];
            CHAR SHAvalue[64];
            char salt[7];
            int match=0;
            CHAR buffer[64];

            fp = fopen("passwords.txt","r");

            while(!feof(fp)){

                fscanf(fp, "%s %s %s", fileUser, salt, SHAvalue);

                // printf("%s %s %s\n", fileUser, salt, SHAvalue);
                if(strcmp(fileUser,username)==0){

                    strcpy(tempPassword,password);
                    // printf("%s \n", tempPassword);
                    strcat(tempPassword,salt);
                    // printf("%s \n", tempPassword);

                    shaGenerator(tempPassword);

                    // printf("New SHA value calculated :");

                    FILE *fp1;
                    fp1=fopen("tempHash.txt","w");

                    for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
                        fprintf(fp1,"%02x", buf[i]);
                    }
                    fclose(fp1);

                    fp1=fopen("tempHash.txt","r");
                    fscanf(fp1,"%s",buffer);
                    fclose(fp1);
                    
                    // printf("SHA value read from file :" );

                    for(int i=0; i<64;++i){
                        // printf("%c", SHAvalue[i]);

                        if(buffer[i]==SHAvalue[i]){
                            match=1;
                            continue;
                        }
                        else
                        {
                            printf("\nPassword Not Matched \n");
                            match=0;
                            break;
                        }
                    }
                    if(match==1){
                        printf("\nPassword Matched\nLogin Successful");
                    }
                    break;
                }
                else{
                    continue;
                }
            }

            
    return 0;
}