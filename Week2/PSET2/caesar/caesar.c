#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>


//A function prototype
bool only_digits(int argc, string arg);

int main(int argc, string argv[])
{

    //Ensure proper only_digits
    if (!only_digits(argc, argv[1]))
    {
        printf(" Usage: ./caesar key \n ");
        return 1;
    }

    //Convert strings of argv[1] to int
    int key = atoi(argv[1]);

    //module the key if key is bigger than 26
    if (key > 26)
    {
        key %= 26;
    }

    //get the input 'plaintext' from the user
    string plaintext = get_string("plaintext: ");


    if (argc == 2)
    {
        //loop all the letter in the plaintext
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            //do this if it's uppercase letter
            if (plaintext[i] >= 65 && plaintext[i] <= 90)
            {
                if (plaintext[i] + key > 90)
                {
                    //make sure it's still letter
                    plaintext[i] -= 26;
                }
                plaintext[i] += key;
            }
            else if (plaintext[i] >= 97 && plaintext[i] <= 121)
            {
                if (plaintext[i] + key > 121)
                {
                    //make sure it's still letter
                    plaintext[i] -= 26;
                }
                plaintext[i] += key;
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);
    return 0;
}


bool only_digits(int argc, string arg)
{
    //Ensure only two argument
    if (argc != 2)
    {
        return false;
    }

    //Return true if the string is onlydigits else false
    for (int i = 0; i < strlen(arg); i++)
    {
        if (!isdigit(arg[i]))
        {
            return false;
        }
    }
    return true;
}