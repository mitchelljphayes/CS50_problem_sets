#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

void concatenate(char p[], char q[]);
long get_cc(void);
string ccv(long number);


int main(void)
{
    long number = get_cc();
    string verified = ccv(number);
    printf("%s\n",verified);
}

long get_cc(void)
{
    //intiialises n
    long n;
    do
    {
        n = get_long("Number: ");
    }
    // sets the acceptable params for n
    while (n < 1);
    return n;
}

string ccv(long number)
{
    long n = number;
    string result = NULL;
    int array[16];
    int len = 0;
    for (int i = 0; n > 0; i++) // create reversed array from number and count the length of card number
    {
        array[i] = (n % 10);
        n = n / 10;
        len = i; // keeps length as final value of i in for loop
        // printf("n:%ld, array:%i, \n", n, array[i]); // Just for testing
    }
    int e = 0;
    int o = 0;
    for (int i = 0, h = 0; i <= len; i++)
    {
        // if even index
        if (i % 2 == 0)
        {
            // sum together
            e += array[i];
            // printf("e:%i\n",e);// Just for testing
        }
        // if odd index
        else if (i % 2 != 0)
        {
            // sum digits and sum together
            h = 2*array[i];
            o += (h / 10) + (h % 10);
            // printf("o:%i\n",o);// Just for testing
        }
    }
    // Calculate Modulo
    int modulo = (e+o)%(int)10;
    // Determine card type based on given tests
    if (((len+1) == 15) && (array[len] == 3) && ((array[len-1] == 4) || (array[len-1] == 7)) && modulo == 0)
    {
       result = "AMEX\n";
    }
    else if (((len+1) == 16) && (array[len] == 5) && ((array[len-1] >= 1) && (array[len-1] <= 5)) && modulo == 0)
    {
        result = "MASTERCARD\n";
    }
    else if ((((len+1) == 13) || ((len+1) == 16)) && (array[len] == 4) && modulo == 0)
    {
        result = "VISA\n";
    }
    else
    {
        result = "INVALID\n";
    }
    return result;
}
// 5105105105105100