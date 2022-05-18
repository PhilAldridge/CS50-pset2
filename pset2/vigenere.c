#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string phrase;
    int alphaletters = 26;
    int lowercasestart = 97; //marks A and a in ASCII
    int uppercasestart = 65;
    
    if(argc==2 )
    {
        //implement the cyper
        string k = argv[1];
        int key[strlen(k)];
        
        for(int j = 0, length = strlen(k); j<length; j++) //create key and check k is valid
        {
            if(islower(k[j]))
            {
                key[j] = k[j]-lowercasestart;
            } else if(isupper(k[j])) {
                key[j] = k[j]-uppercasestart;
            } else {
                printf("Your key must only contain alphabetic characters\n");
                return 1;
            }
        }
        
        do
        {
            //printf("Please type in a phrase to encrypt: ");
            phrase = GetString();
        } while (strlen(phrase)==0);
        
        
        int keynum = 0;

        for (int i = 0, length=strlen(phrase); i<length; i++)
        {
            int newchar;
            if (islower(phrase[i])) //character is a lowercase letter (97-122)
            {
                newchar = phrase[i] + key[keynum];
                keynum = (keynum + 1)%strlen(k);
                if (newchar >= (lowercasestart+alphaletters))
                {
                    newchar -= alphaletters;
                }
                printf("%c", newchar );
            } else if (isupper(phrase[i])) { //character is an uppercase letter (65-90)
                newchar = phrase[i] + key[keynum];
                keynum = (keynum + 1)%strlen(k);
                if (newchar >= (uppercasestart+alphaletters))
                {
                    newchar -= alphaletters;
                }
                printf("%c", newchar );
            } else { //for other characters
                printf("%c", phrase[i] );
            }
        }
        printf("\n");
        
        return 0;
    } else {
        //show error message
        printf("Usage: /home/cs50/caesar <key>\n");
        return 1;
    }
}
