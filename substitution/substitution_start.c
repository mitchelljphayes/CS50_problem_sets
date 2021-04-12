#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

char encipher(char p, int k);

int main(int argc, string argv[])
{
    bool key_check = true; // creating a boolean for verifying digits only in the key need to be here to pass out of if statement.
    if (argc == 2) // Check that there is a second word before testing it's length otherwise Segmentfault
    {
        int argv_len = strlen(argv[1]);
        // for loop checks each position of string for digits, breaks out if non-digit detected.
        for (int i = 0; i < argv_len && digit_check == true; i++)
        {
            digit_check = (bool)isdigit(argv[1][i]); // breaks out as false if non digit detected otherwise remains true
        }
    }

    if ((digit_check == true) && (argc == 2)) // checks that only 1 word passed as key and that word contains only digits
    {
        string key_string = argv[1]; // converts argv string to int
        string s = get_string("plaintext: "); // prompts for plaintext
        printf("ciphertext: "); //prints cipher text label
        // int len = strlen(s); // was used to stop for loop, but changed to test for null char
        for (int i = 0; s[i] != '\0'; i++) //loops through string and encodes cipher
        {
            char cipherchar = encipher(s[i], key_string);
            printf("%c", cipherchar); // prints each character after being encoded
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1; // returns failed program if key not accepted
    }
}

char encipher(char p, int k)
{
    char c = p;
    if ((bool)isalpha(p)) // makes sure char is an alpha
    {
        if ((bool)isupper(p))
        {
            c = (((p - 65) + k) % 26) + 65; // encodes uppercase letters
        }
        else if ((bool)islower(p))
        {
            c = (((p - 97) + k) % 26) + 97; // encodes lowercase letters
        }
    }
    else
    {
        c = p; // passthrough non-letters
    }
    return c;
}


