#include <stdio.h>
#include <cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <crypt.h>

static string nextChar(string str);

int main(void)
{

    string hashedPassword = GetString();
    int maxWordLength = 8;
    int hashLength = 13;
    FILE * pFile;
    char word[50];
    string password;
    pFile = fopen("/usr/share/dict/linux.words", "r");
    
    
    if(pFile != NULL) //checks dictionary file is open
    {
        while(fgets(word, 50, pFile) != NULL) //read dictionary one line at a time
        {
            if(strlen(word)<=maxWordLength) //skip words that are too long
            {
                password = strtok(word, "\n");
                char salt[] = "aa";
                do                          //loop through possible salts
                {
                    if(strncmp(crypt(password,salt), hashedPassword, hashLength)==0)
                    {
                        printf("%s\n",password);
                        return 0;
                    } else if(isupper(password[0])) {       //check first letter capitalizations
                        password[0] = password[0] + 32;
                        if(strncmp(crypt(password,salt), hashedPassword, hashLength)==0)
                        {
                           printf("%s\n",password);
                           return 0;
                        }
                    } else {
                        password[0] = password[0] - 32;
                        if(strncmp(crypt(password,salt), hashedPassword, hashLength)==0)
                        {
                            printf("%s\n",password);
                            return 0;
                        }
                    }
                    strcpy(salt, nextChar(salt));
                 } while (strncmp(salt, "//", 2)!=0);  
             }   
        }
        fclose(pFile);
    } else {
        printf("Couldn't open dictionary file");
    }
    printf("Couldn't find the password");
    return 1;
}
    
static string nextChar(string strg)  //function for getting the next character in a string
{
    int pos = strlen(strg) - 1;
    int done = 0;
    char * ptr;
    string possibleSaltChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
       
    while(done!=1)
    {
        if(strg[pos]==47)
        {
            strg[pos] = 97;
            pos --;
        } else {
            ptr = strchr(possibleSaltChars, strg[pos]);
            strg[pos] = possibleSaltChars[ptr-possibleSaltChars+1];
            done = 1;
        }               
    }
    return strg;
}


