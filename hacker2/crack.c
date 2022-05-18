#include <stdio.h>
#include <cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>

//check argument given is valid


//try simple dictionary attack first (with capital or non-capital first letter and/or numbers at front
//this should be pretty quick so long as password given is just a single word

string hashedPassword = argv[1];

int maxPasswordLength = 8; //set maxpassword length here so that it can easily be changed

//open dictionary file
FILE * pFile;
pFile = fopen("/usr/share/dict/linux.words", "r");



foreach(word in dictionary)
{
	if(strlen(word)<=maxPasswordLength) //avoid checking words that are longer than the max length to save time
	{
		if(crypt(word)==hashedPassword)
		{
			printf(word+numberEnding);
				return ;
		} 
	}
}

for(int i=0; i<100; i++) //checking words with numbers on the end
{
	string numberEnding;
	numberEnding = i; //may need to convert to string officially
	
	foreach(word in dictionary)
	{
		if(strlen(word)< maxPasswordLength)
		{
			if(crypt(word+numberEnding)== hashedPassword)
			{
				printf(word+numberEnding);
				return ;
			} else if (crypt(word+numberEnding)== hashedPassword) {  //check capitalization of first letter
				printf(word+numberEnding); 
				return ;
			}
		}
	}
}



//try all possible combinations starting with one-letter words and working upwards
string possibleCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 "; //assume password is made from this list of common symbols
string word["a"]; //starting point
boolean finished = false;

while(!finished)
{
	if(crypt(word)== hashedPassword)
	{
		printf(word);
		return ;
	}
	word = getNextWord(word); //calls function defined below which increments to the next possible password	
}
