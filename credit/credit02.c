#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

void concatenate(char p[], char q[]);
long get_cc(void);
void ccv(long number);


int main(void)
{
    long number = get_cc();
    ccv(number);
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

void ccv(long number)
{
    long n = number;
    char str[256];
    // sprintf(s,"%ld", n);
//     printf("%s\n", str);
//     int len = strlen(str);
//     printf("%d\n", len);
    // int e = 0;
    // int o = 0;
    // char evens;
    // char odds;
    // string s = NULL;
    sprintf(str "%ld", n);

    // for (int i = 0; n > 0; i++)
    // {
    //     s[i] = (n % 10);
    //     n = n / 10;
    // }
    printf("%s\n",s);
}

    // {
    //     if (i % 2 != 0 && n > 0)
    //     {
    //         o = (n % 10);
    //         // sprintf(o,"%ld", o);
    //         concatenate(odds, o);
    //         n = n / 10;
    //         printf("odds: n:%ld o:%s e:%s i:%d\n", n , o, e, i);
    //     }

    //     else if (i % 2 == 0 && n > 0)
    //     {
    //         e = (2*(n % 10));
    //         // e = char e;
    //         concatenate(evens, e);
    //         n = n / 10;
    //         printf("evens: n:%ld, o:%s, e:%s, i:%d\n", n , o, e, i);
    //     }
    // }
//     int l = 10;
//     int check_sum = (o + e);
//     int luhn = check_sum % l;



//     bool valid;
//     valid = (luhn == 0);

//     printf("Check sum: %d, Modulo: %d, Valid: %d \n",check_sum, luhn, valid);

//     // if (valid == true)
//     // {
//     //     if ((i == 15) && ((number >= 340000000000000 && number < 350000000000000) ||(number >= 370000000000000 && number < 380000000000000)))
//     //     {
//     //         printf("AMEX\n");
//     //     }
//     //     else if ((i == 16) && (number >= 5100000000000000 && number <= 5600000000000000))
//     //     {
//     //         printf("MASTERCARD\n");
//     //     }
//     //     else if ((i == 16 || i == 13) && ((number >= 4000000000000000 && number < 5000000000000000) || (number >= 4000000000000 && number < 5000000000000)))
//     //     {
//     //         printf("VISA\n");
//     //     }
//     // }
//     // else
//     // {
//     //     printf("INVALID\n");
//     // }
// }
