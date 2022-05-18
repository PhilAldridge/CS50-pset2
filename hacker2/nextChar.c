#include <stdio.h>
#include <cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char salt[] = "aa";
    string possibleSaltChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
    
    do
    {
        int pos = strlen(salt) - 1;
        int done = 0;
        char * ptr;
        
        while(done!=1)
        {
            if(salt[pos]==47)
            {
                salt[pos] = 97;
                pos --;
            } else {
                ptr = strchr(possibleSaltChars, salt[pos]);
                salt[pos] = possibleSaltChars[ptr-possibleSaltChars+1];
                done = 1;
            }               
        }
        printf("%s ",salt);
    } while (strncmp(salt, "//", 2)!=0);
}
