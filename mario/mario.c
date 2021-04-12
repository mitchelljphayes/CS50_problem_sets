#include <cs50.h>
#include <stdio.h>

void pyramid(int n);
int get_valid_input(void);
// This is the actual program
int main(void)
{
    // Ask for valid input function to get user input
    int h = get_valid_input();
    // Calls the function to generate the pyramid
    pyramid(h);
}

// only accept intergers between 1 and 8 inclusive
int get_valid_input(void)
{
    //intiialises n
    int n;
    do
    {
        n = get_int("How tall should we make the pyramid: ");
    }
    // sets the acceptable params for n
    while (n < 1 || n >= 9);
    return n;
}

// Generate pyramid
void pyramid(int n)
{
    while (n < 1);
    // This loop counts up the rows
    for (int i = 0; i < n; i++)
    {
        // This loop counts up and prints the spaces until n-i
        for (int s = 1; s < n - i; s++)
        {
            printf(" ");
        }
        // This loop counts up and prints the octothorpes on the incline
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // This loop prints the chasm
        printf("  ");
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // This loop counts up and prints the octothorpes on the decline
        printf("\n");
    }
}