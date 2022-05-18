#include <stdio.h>
#include <cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <crypt.h>

int main (void)
{
    string password = GetString();
    string salt = GetString();
    string hashed = crypt(password, salt);
    printf("%s\n",hashed);
    return 0;
}
