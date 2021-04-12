#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string t);
int count_words(string t);
int count_sentences(string t);

int main(void)
{
    string text = get_string("Text: ");
    int total_letters = count_letters(text);
    int total_words = count_words(text);
    int total_sentences = count_sentences(text);
    float L = (float) total_letters / total_words * 100;
    float S = (float) total_sentences / total_words * 100;
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}


int count_letters(string t)
{
    int l = 0; //letters
    int len = strlen(t);
    for (int i = 0; i <= len; i++)
    {
        if ((bool)isalpha((unsigned char) t[i]))
        {
            ++l; // increment letters by 1
        }

    }
    return l;

}
int count_words(string t)
{
    int w = 1; //words
    int len = strlen(t);
    for (int i = 0; i <= len; i++)
    {
        if (((bool)isspace((unsigned char) t[i]))
            && !((bool)isspace((unsigned char) t[i + 1])))// is a space and next charachter is not a space
        {
            ++w; //count words
        }
    }
    return w;

}

int count_sentences(string t)
{

    int s = 0; //sentences
    int len = strlen(t);
    for (int i = 0; i <= len; i++)
    {
        if (((int) t[i] == 33) || ((int) t[i] == 46) || ((int) t[i] == 63))
        {
            ++s; // count sentences.
        }
    }
    return s;

}


