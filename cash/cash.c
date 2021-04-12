#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_money(void);
int least_coins(int money);
int main(void)
{
    int money = get_money();
    int coins = 0;
    coins = least_coins(money);
    // printf("We got %i cents\n", cents);
    printf("%d\n", coins);
}

int get_money(void)
{
    //intiialises m
    float m;
    do
    {
        m = get_float("Change Owed: ");
        m = round(m * 100);
    }
    // sets the acceptable params for m
    while (m < 0.01);
    return m;
}

int least_coins(int money)
{
    int m = money;
    int c = 0;
    do
    {
        if (m >= 25)
        {
            m = m - 25;
            c++;
        }
    }
    while (m >= 25);
    do
    {
        if (m >= 10)
        {
            m = m - 10;
            c++;
        }
    }
    while (m >= 10);
    do
    {
        if (m >= 5)
        {
            m = m - 5;
            c++;
        }
    }
    while (m >= 5);
    do
    {
        if (m >= 1)
        {
            m = m - 1;
            c++;
        }
    }
    while (m >= 1);

    return c;
}




//get value from user
//(only accept positive float values over 0.01)
//establish currecy denoms
//check if the value is lower than the largest coin
//if so subtract the value of the largest coin from the total
//increment coin_counter by 1
//in not check against the next coin
//if so subtract the value of the next largest coin from the total
//increment coin_counter by 1
//(needs to loop back to current coin) then move on
