#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Promtps user input of name
    string name = get_string("What's your name?\n");
    // Returns hello user name
    printf("Hello, %s\n", name);
}