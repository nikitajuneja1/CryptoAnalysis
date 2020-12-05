#include <stdio.h>
#include <time.h>
// #include <unistd.h>
#include <io.h>
#include <string.h>
#include "sha256.h"
#include <stdlib.h>

#define SALTMAX 8
#define PASSMAX 20
#define USERMAX 20
#define SHAlength 64


char tmp_s[SALTMAX];
CHAR buf[SHA256_BLOCK_SIZE];
CHAR buffer[SHAlength];

void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[1000];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);

    while ((pos = strstr(str, oldWord)) != NULL)
    {
        // Bakup current line
        strcpy(temp, str);

        // Index of current found word
        index = pos - str;
        
        // Terminate str after word found index
        str[index] = '\0';
        // printf("%s ",str);
        // Concatenate str with new word 
        strcat(str, newWord);
        
        // Concatenate str with remaining words after 
        // oldword found index.
        strcat(str, temp + index + owlen);
    }
}

void gen_random(int len) {

    
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "!@#$/^&*(){}[]<>,.|~";

    srand((unsigned) time(NULL));
    // srand((unsigned) time(NULL) * getpid());

    for (int i = 0; i < len; i++){
        tmp_s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

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

char* sessionTime(){

    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    return(asctime(timeinfo));

}

int searchUsername(char* username, FILE* fp){

    int userFlag=0;
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

    fprintf(fp, "%s\n", username);
    fclose(fp);
    return userFlag;
}

void changeFormat(){

    FILE *fp1;
    fp1=fopen("tempHash.txt","w");

    for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
        fprintf(fp1,"%02x", buf[i]);
    }

    fclose(fp1);

    fp1=fopen("tempHash.txt","r");
    fscanf(fp1,"%s",buffer);
    fclose(fp1);

}

int main(){

    int choice;
    FILE *fp;
    CHAR password[PASSMAX];
    CHAR username[USERMAX];
    char c;

    CHAR fileUser[USERMAX];
    CHAR tempPassword[PASSMAX];
    CHAR SHAvalue[SHAlength];
    char salt[SALTMAX+1];
    int match=0;
    // CHAR buffer[SHAlength];
    CHAR currentUser[USERMAX];

    int internalChoice;
    CHAR newUsername[USERMAX];
    CHAR NewPassword[PASSMAX];

    fp = fopen("banner.txt","r");
    printf("\n\n");

    // while(!feof(fp)){
    //     printf("%c", fp);
    // }
    
    while ( 1 ){
        c = fgetc ( fp ) ; // reading the file
        if ( c == EOF )
        break ;
        printf ( "%c", c ) ;
    }
    fclose(fp);
    printf("\n\n");
    printf("Welcome!\n\t1.SignUp\n\t2.SignIn\n\t3.Exit\n");
    scanf("%d", &choice);

    if(choice==1){

            // FILE *fp;
            int userFlag=0;
            // New User
            printf("Get Started! Create your account\n");
            while(userFlag==0){
                printf("Username: " );
                scanf("%s",username);
                
                // //For searching username
                // char username_file_location[] ="usernames.txt";
                // char fileUser[USERMAX];
                // fp = fopen(username_file_location, "a+");

                // while(!feof(fp)){

                //     fscanf(fp,"%s",fileUser);

                //     if(strcmp(fileUser,username)==0){
                //         printf("This username already exists.\n");
                //         userFlag=0;
                //         break;
                //     }
                //     else{
                //         userFlag=1;
                //         continue;
                //     }
                // }

                userFlag=searchUsername(username,fp);

                if(userFlag==0){
                    printf("This username already exists.\n");
                }

                // fprintf(fp, "%s\n", username);
                // fclose(fp);

            }
            
            printf("Password: " );
            scanf("%s", password);

            gen_random(SALTMAX);
            // printf("%s", tmp_s);
            strcat(password, tmp_s);

            // printf("%d",userFlag);

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

                // for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
                //     printf("%02x", buf[i]);
                // }
                
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
    

    printf("Welcome Back! Good to see you again.\n");
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

    int passFlag=1;

    while(passFlag){

        printf("Password: " );
        scanf("%s",password);

        // fp1 = fopen(password_file_location, "r");
        
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

                // FILE *fp1;
                // fp1=fopen("tempHash.txt","w");

                // for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
                //     fprintf(fp1,"%02x", buf[i]);
                // }

                // fclose(fp1);

                // fp1=fopen("tempHash.txt","r");
                // fscanf(fp1,"%s",buffer);
                // fclose(fp1);

                changeFormat();
                
                // printf("SHA value read from file :" );

                for(int i=0; i<SHAlength;++i){
                    // printf("%c", SHAvalue[i]);

                    if(buffer[i]==SHAvalue[i]){
                        match=1;
                        continue;
                    }
                    else
                    {
                        printf("Wrong Password!\n\n");
                        match=0;
                        break;
                    }
                }

                if(match==1){
                    passFlag=0;
                    printf("Signed in successfully\n\n");
                    strcpy(currentUser,username);

                    // time_t rawtime;
                    // struct tm * timeinfo;
                    // time(&rawtime);
                    // timeinfo = localtime(&rawtime);

                    FILE*fp1;
                    
                    fp1=fopen("sessionLogs.txt","a+");

                    fprintf(fp1,"%s LoginTime: %s", currentUser, sessionTime());
                    fclose(fp1);
                }
                if(match==0){
                    printf("Do you want to\n\t1.Retry\n\t2.Exit\n");
                    int choice;
                    scanf("%d",&choice);
                    if(choice==2){
                        exit(0);
                    }
                }

            }
            // else{
            //     continue;
            // }
        }
    }

    fclose(fp);

    
    // CHAR readUser[20];
    // int changed=0;

    printf("Hi %s! ", currentUser);
    printf("You can do the following things with your account:\n\n");
    printf("\t1.Edit username\n\t2.Edit password\n\t3.SignOut\n");
    scanf("%d",&internalChoice);

    if(internalChoice !=2 && internalChoice!=1 && internalChoice!=3){       
        printf("Wrong Input!");
    }
    
    // FILE *fp2;

    if(internalChoice==1){

        FILE *fPtr;
        FILE *fTemp;

        char userBuffer[1000];
        int userFlag=0;

        while(userFlag==0){
            printf("Enter new username:\n");
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

        printf("\n\nUsername changed successfully\nPlease Login with new username\n");
        internalChoice=3;

    }
    if( internalChoice == 3 ){
        FILE *fp1;

        printf("You are signed out.\n\n");

        // time_t rawtime;
        // struct tm * timeinfo;
        // time(&rawtime);
        // timeinfo = localtime(&rawtime);
        
        fp1=fopen("sessionLogs.txt","a+");

        fprintf(fp1,"%s LogoutTime: %s", currentUser, sessionTime());
        fclose(fp1);
        exit(0);
    }
    // if(internalChoice == 2){

        FILE *fPtr;
        FILE *fT;

        char userBuffer[1000];
        // int passFlag=0;
        // char tempSalt[6];


        printf("Enter New Password:\n");
        scanf("%s", NewPassword);

        while(1){
            if(strcmp(NewPassword,password)==0){
                printf("You cannot use the old password again\n");
                printf("Enter New Password:\n");
                scanf("%s", NewPassword);
                continue;
            }
            else{
                break;
            }
        }

        fp = fopen("passwords.txt","r");

        while(!feof(fp)){

            fscanf(fp, "%s %s %s", fileUser, salt, SHAvalue);

            if(strcmp(fileUser,currentUser)==0){
                // printf("This username already exists.\n");
                // strcpy(tempSalt,salt);
                // strcpy(buffer,SHAvalue);
                break;
            }
            else{
                continue;
            }
            
        }

        fclose(fp);

        // printf("%s %s %s \n", fileUser, salt, SHAvalue);

        strcat(NewPassword, salt);
        shaGenerator(NewPassword);

        // for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
        //     printf("%02x", buf[i]);
        // }
        
    
        fPtr  = fopen("passwords.txt", "r");
        fT = fopen("replaceSHA.tmp", "w");
        
        // FILE *fp1;

        // fp1=fopen("tempHash.txt","w");

        // for(unsigned int i = 0; i < SHA256_BLOCK_SIZE; ++i){
        //     fprintf(fp1,"%02x", buf[i]);
        // }
        // fclose(fp1);

        // fp1=fopen("tempHash.txt","r");
        // fscanf(fp1,"%s",buffer);
        // fclose(fp1);

        changeFormat();

        // printf("\nBuffer: %s\n", buffer);

    
        while ((fgets(userBuffer, 1000, fPtr)) != NULL){
            replaceAll(userBuffer, SHAvalue, buffer);
            fputs(userBuffer, fT);
        }

        // printf("%s \n", buffer);

        fclose(fPtr);
        fclose(fT);

        remove("passwords.txt");
        rename("replaceSHA.tmp", "passwords.txt");

        printf("\nPassword changed successfully\nYou are signed out.\nPlease signin with new password.\n");

        // time_t rawtime;
        // struct tm * timeinfo;
        // time(&rawtime);
        // timeinfo = localtime(&rawtime);
        
        FILE *fp1;

        fp1=fopen("sessionLogs.txt","a+");

        fprintf(fp1,"%s LogoutTime: %s", currentUser, sessionTime());
        fclose(fp1);

    // }

    return 0;
}