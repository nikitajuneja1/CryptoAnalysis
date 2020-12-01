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

void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[1000];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);


    /*
     * Repeat till all occurrences are replaced. 
     */
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        // Bakup current line
        strcpy(temp, str);

        // Index of current found word
        index = pos - str;

        // Terminate str after word found index
        str[index] = '\0';

        // Concatenate str with new word 
        strcat(str, newWord);
        
        // Concatenate str with remaining words after 
        // oldword found index.
        strcat(str, temp + index + owlen);
    }
}

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

            // printf("%s \n", tmp_s);
            // printf("%s \n", username);
            // printf("%s \n", password);

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
    else if(choice == 3 ){
        exit(0);
    }
    else if(choice !=2){
        printf("Wrong Input!");
        exit(0);
    }
    
    int userFlag=1;
    while(userFlag==1){
        printf("Username: " );
        scanf("%s",username);
        
        //For searching username
        char username_file_location[] ="usernames.txt";
        char fileUser[USERMAX];
        fp = fopen(username_file_location, "a+");

        while(!feof(fp)){

            fscanf(fp,"%s",fileUser);

            if(strcmp(fileUser,username)==0){
                userFlag=0;
                break;
            }
            else{
                userFlag=1;
                continue;
            }
        }
        if(userFlag==1){
            printf("This username does not exists.\n");
        }
        fclose(fp);

    }

    printf("Password: " );
    scanf("%s",password);


    // fp1 = fopen(password_file_location, "r");
    CHAR fileUser[20];
    CHAR tempPassword[10];
    CHAR SHAvalue[64];
    char salt[7];
    int match=0;
    CHAR buffer[64];
    CHAR currentUser[20];

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
                    printf("Password Not Matched\nLogin failed.");
                    match=0;
                    exit(0);
                }
            }
            if(match==1){
                printf("Login Successful\n\n");
                strcpy(currentUser,username);

                time_t rawtime;
                struct tm * timeinfo;
                time(&rawtime);
                timeinfo = localtime(&rawtime);
                
                fp1=fopen("sessionLogs.txt","a+");

                fprintf(fp1,"%s Login Time: %s", currentUser, asctime(timeinfo));
                fclose(fp1);
            }
            break;
        }
        else{
            continue;
        }
    }

    fclose(fp);

    int internalChoice;
    CHAR newUsername[20];
    CHAR NewPassword[10];
    // CHAR readUser[20];
    // int changed=0;

    printf("Welcome %s !", currentUser);
    printf("\nYou can do the following things\n");
    printf("\t1.Change Username\n\t2.Change Password\n\t3.Logout\n");
    scanf("%d",&internalChoice);
    
    // FILE *fp2;

    if(internalChoice==1){

        FILE *fPtr;
        FILE *fTemp;

        char userBuffer[1000];
        int userFlag=0;

        while(userFlag==0){
            printf("Enter New Username:\n");
            scanf("%s", newUsername);
            
            //For searching username
            char username_file_location[] ="usernames.txt";
            fp = fopen(username_file_location, "r");

            while(!feof(fp)){

                fscanf(fp,"%s",fileUser);

                if(strcmp(fileUser,newUsername)==0){
                    printf("This username already exists.\n");
                    userFlag=0;
                    break;
                }
                else{
                    userFlag=1;
                    continue;
                }
            }

            fclose(fp);

        }
        
        fPtr  = fopen("usernames.txt", "r");
        fTemp = fopen("replace.tmp", "w"); 

        while ((fgets(userBuffer, 1000, fPtr)) != NULL){
            replaceAll(userBuffer, currentUser, newUsername);
            fputs(userBuffer, fTemp);
        }

        fclose(fPtr);
        fclose(fTemp);

        remove("usernames.txt");
        rename("replace.tmp", "usernames.txt");

        fPtr  = fopen("passwords.txt", "r");
        fTemp = fopen("replacePass.tmp", "w"); 

        while ((fgets(userBuffer, 1000, fPtr)) != NULL){
            replaceAll(userBuffer, currentUser, newUsername);
            fputs(userBuffer, fTemp);
        }

        fclose(fPtr);
        fclose(fTemp);

        remove("passwords.txt");

        rename("replacePass.tmp", "passwords.txt");

        printf("Username changed Successfully\nPlease Login with new username\n");
        internalChoice=3;

    }
    if(internalChoice == 2){

        FILE *fPtr;
        FILE *fTemp;

        char userBuffer[1000];
        int userFlag=0;

        printf("Enter New Password:\n");
        scanf("%s", NewPassword);

        // fp = fopen("passwords.txt","r");

        // while(!feof(fp)){

        // fscanf(fp, "%s %s %s", fileUser, salt, SHAvalue);

        // strcat(password, salt);
        // shaGenerator(password);

        
        // }
        
        
        fPtr  = fopen("passwords.txt", "r");
        fTemp = fopen("replacePass.tmp", "w"); 

        while ((fgets(userBuffer, 1000, fPtr)) != NULL){
            replaceAll(userBuffer, currentUser, newUsername);
            fputs(userBuffer, fTemp);
        }

        fclose(fPtr);
        fclose(fTemp);

        remove("passwords.txt");

        rename("replacePass.tmp", "passwords.txt");

        printf("Password Changed Successfully");

    }
    if( internalChoice == 3){
        FILE *fp1;

        printf("You are logged Out.\n\n");

        time_t rawtime;
        struct tm * timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        
        fp1=fopen("sessionLogs.txt","a+");

        fprintf(fp1,"%s Logout Time: %s", currentUser, asctime(timeinfo));
        fclose(fp1);

    }
    else{
        printf("Wrong Input!");
    }


    return 0;
}