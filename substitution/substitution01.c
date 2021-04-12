#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

char encipher(char p);

int UPPERARRAY[26];
int lowerarray[26];


int main(int argc, string argv[])
{
    // check for 2 argument only in arg c
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1; // returns failed program if key not accepted
    }
    // check length of argv[1]
    else if ((argc == 2) && (strlen(argv[1]) != 26))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    bool no_dups = true;
    bool alpha_check = true;
    // check each charcter in argv[1] for alpha
    if ((argc == 2) && (strlen(argv[1]) == 26))
    {
        // for loop checks each position of string for alphas, breaks out if non-alpha detected.
        for (int i = 0; i < 26 && alpha_check == true; i++)
        {
            alpha_check = (bool)isalpha(argv[1][i]); // breaks out as false if non alpha detected otherwise remains true
            UPPERARRAY[i] = toupper(argv[1][i]); // convert all characters to uppercase and store in array
            lowerarray[i] = tolower(argv[1][i]); // convert all characters to lowercase and store in array

                for (int j = 0; j < i && no_dups == true; j++)
                {
                    no_dups = toupper(argv[1][i]) != UPPERARRAY[j];
                }
        }
    }
    if (no_dups == false)
    {
        printf("Key must not contain duplicate letters.\n");
        return 1;
    }

    if (alpha_check == false)
    {
        printf("Key must contain letters only.\n");
        return 1;
    }
    //vchprzgjntlskfbdqwaxeuymoi

    string key_string = argv[1]; // converts argv string to int
    string s = get_string("plaintext: "); // prompts for plaintext
    string ciphertext[strlen(s)];
    printf("ciphertext: "); //prints cipher text label
    for (int i = 0; i < strlen(s) ; i++) //loops through string and encodes cipher
    {
        char cipherchar = encipher(s[i]);
        //printf("%c", cipherchar); // prints each character after being encoded
        ciphertext[i] =& cipherchar;
    }
    printf("%s\n", (string)ciphertext);

    // Get text;
    // pass message through cipher function substituting each character for its cipher index charachter preservng case and
    // passing through punctuation & digits.
    // print each charachter or store as string and print.
}

char encipher(char p)
{
    char c = 36;
    if ((bool)isalpha(p)) // makes sure char is an alpha
    {
        for (int i = 0; c == 36; i++)
        {
            if ((bool)isupper(p))
            {
                if (p == UPPERARRAY[i])
                {
                    c = (65 + i);
                }
            }
            else if ((bool)islower(p))
            {
                if (p == lowerarray[i])
                {
                    c = (97 + i);
                }
            }
        }
    }
    else
    {
        c = p; // passthrough non-letters
    }
    return c;
}