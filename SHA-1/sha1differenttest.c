#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "sha1.h"

/*
 *  Define patterns for testing
 */
#define TEST1   "nikitajuneja"
#define TEST2   "biditmangal"
#define TEST3   "vagishajain"

char *testingArray[3] =
{
    TEST1,
    TEST2,
    TEST3
};
long int repeatCount[3] = { 1, 2, 3};
char *correctResultantArray[3] =
{
    "0D 50 E6 08 47 B2 01 41 5A 1A 66 BA 27 EA 9C 12 E5 3A 11 AD",
    "8F 51 65 72 11 84 75 45 C8 87 64 07 D9 B7 A8 29 AD 47 F0 17",
    "BD 6A DD C6 36 69 68 47 F0 D0 52 2E 43 5F F8 8E 25 46 6E 02"
};

int main()
{
    SHA1Context sha;
    int i, j, err;
    uint8_t Message_Digest[20];

    //SHA-1 tests
    for(j = 0; j < 3; ++j)
    {
        printf( "\nTest %d: %d, '%s'\n",
                j+1,
                repeatCount[j],
                testingArray[j]);

        err = SHA1Reset(&sha);
        if (err)
        {
            fprintf(stderr, "SHA1 Reset Error %d is encountered.\n", err );
            break;
        }

        for(i = 0; i < repeatCount[j]; ++i) //number of repetitions for each test
        {

            err = SHA1Input(&sha,
                  (const unsigned char *) testingArray[j],
                  strlen(testingArray[j]));
            if (err)
            {
                fprintf(stderr, "SHA1 Input Error %d. is encountered\n", err );
                break;
            }
        }

        err = SHA1Result(&sha, Message_Digest);
        if (err)
        {
            fprintf(stderr,
            "SHA1 Result Error %d, could not compute message digest.\n",
            err );
        }
        else
        {
            printf("Value computed from the used sha-1 algorithm: \n");
            printf("\t");
            for(i = 0; i < 20 ; ++i)
            {
                printf("%02X ", Message_Digest[i]);
            }
            printf("\n");
        }
        printf("Should match the pre-computed value:\n");
        printf("\t%s\n", correctResultantArray[j]);
    }

    /* Test some error returns */
    // err = SHA1Input(&sha,(const unsigned char *) testingArray[1], 1);
    // printf ("\nError %d. Should be %d.\n", err, shaStateError );
    // err = SHA1Reset(0);
    // printf ("\nError %d. Should be %d.\n", err, shaNull );
    return 0;
}
