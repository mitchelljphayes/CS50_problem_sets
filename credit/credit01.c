#include <stdio.h>
#include <cs50.h>
#include <math.h>

long get_cc(void);
void ccv(long number);
int main(void)
{
    long number = get_cc();
    ccv(number);
    int m = 20 % 10;

    // printf("%i \n", m);
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
    int e = 0;
    int o = 0;
    char evens;
    char odds;
    int i = 0;
    printf("Start %ld\n",n);
    for (i = 1; n > 0; i++)
    {
        if (i % 2 != 0 && n > 0)
        {
            o = (n % 10);
            odds = odds + ("%d", o);
            n = n / 10;
            printf("odds: %i, n:%ld o:%d e:%d i:%d\n"odds, n , o, e, i);
        }

        else if (i % 2 == 0 && n > 0)
        {
            evens = (2*(n % 10));
            e = e +
            n = n / 10;
            printf("evens: %i, n:%ld, o:%d, e:%d, i:%d\n"evens, n , o, e, i);
        }
    }
    int l = 10;
    int check_sum = (o + e);
    int luhn = check_sum % l;



    bool valid;
    valid = (luhn == 0);

    printf("Check sum: %d, Modulo: %d, Valid: %d \n",check_sum, luhn, valid);

    // if (valid == true)
    // {
    //     if ((i == 15) && ((number >= 340000000000000 && number < 350000000000000) ||(number >= 370000000000000 && number < 380000000000000)))
    //     {
    //         printf("AMEX\n");
    //     }
    //     else if ((i == 16) && (number >= 5100000000000000 && number <= 5600000000000000))
    //     {
    //         printf("MASTERCARD\n");
    //     }
    //     else if ((i == 16 || i == 13) && ((number >= 4000000000000000 && number < 5000000000000000) || (number >= 4000000000000 && number < 5000000000000)))
    //     {
    //         printf("VISA\n");
    //     }
    // }
    // else
    // {
    //     printf("INVALID\n");
    // }
}

