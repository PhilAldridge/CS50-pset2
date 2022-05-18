#include <stdio.h>
#include <cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <crypt.h>

static string nextChar(string str);

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: /home/cs50/crack <hashedpass>\n");
        return 1;
    }

    char * hashedPasswordnSalt = argv[1];
    char hashedPassword[11];
    int maxWordLength = 8;
    int hashLength = 13;
    char salt[2];
    strncpy(salt,hashedPasswordnSalt,2);
    strncpy(hashedPassword,&hashedPasswordnSalt[2],11);
    string password;
    char word[50];
    
    //this is a simple dictionary attack
    FILE * pFile;
    
    
    pFile = fopen("/usr/share/dict/linux.words", "r");
    
    
    if(pFile != NULL) //checks dictionary file is open
    {
        while(fgets(word, 50, pFile) != NULL) //read dictionary one line at a time
        {
            if(strlen(word)<=maxWordLength) //skip words that are too long
            {
                password = strtok(word, "\n");
               
                if(strncmp(crypt(password,salt), hashedPasswordnSalt, hashLength)==0) 
                {
                    printf("%s\n",password);
                    return 0;
                } else if(isupper(password[0])) {       //check first letter capitalizations
                    password[0] = password[0] + 32;
                    if(strncmp(crypt(password,salt), hashedPasswordnSalt, hashLength)==0)
                    {
                       printf("%s\n",password);
                        return 0;
                    }
                } else {
                    password[0] = password[0] - 32;
                    if(strncmp(crypt(password,salt), hashedPasswordnSalt, hashLength)==0)
                    {
                        printf("%s\n",password);
                        return 0;
                    }
                }
             }   
        }
        fclose(pFile);
    } else {
        printf("Couldn't open dictionary file\n");
    }
    
    
    //now try all letter-number combinations
    char password2[] = "a";
    while(strlen(password2)<=maxWordLength)
    {
        if(strncmp(crypt(password2,salt), hashedPasswordnSalt, hashLength)==0) 
        {
            printf("%s\n",password2);
            return 0;
        } else {
            strcpy(password2, nextChar(password2));
            //printf("%s\n",password2);
        }
    }
        
    printf("Couldn't find the password\n");
    return 1;
}
    
static string nextChar(string strg)  //function for getting the next character in a string
{
    int pos = strlen(strg) - 1;
    int done = 0;
    char * ptr;
    string possibleChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./?@#-_ ";
       
    while(done!=1)
    {
        if(strg[pos]==47)
        {
            strg[pos] = 97;
            if(pos == 0)
            {
                strcat(strg,"a");
                done = 1;
            } else {
                pos --;
            }
        } else {
            ptr = strchr(possibleChars, strg[pos]);
            strg[pos] = possibleChars[ptr-possibleChars+1];
            done = 1;
        }               
    }
    return strg;
}

