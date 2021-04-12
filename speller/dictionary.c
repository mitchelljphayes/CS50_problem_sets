// Implements a dictionary's functionality
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of words in dictionary
int numberofwords = 0;

// Number of buckets in hash table
const unsigned int N = 1987;

// Hash table
node *table[N];


// Returns true if word is in dictionary else false
bool check(const char *w)
{
    int index = hash(w);
    node *cursor;
    //move cursor to the index
    cursor = table[index];
    //loop through the nodes comparing the word to the dictionary words
    while (cursor != NULL)
    {
        char *wordCheck = cursor->word;
        if (strcasecmp(wordCheck, w) == 0)
        {
            //return true if word found
            return true;
        }
        else
        {
            //move to next node if cursor not present
            cursor = cursor->next;
        }
    }
    //return false if word not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    int index = 0;
    //loop thourgh each letter of the word
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // for each letter (in lower case) in the word times it by 251 (smallish prime) and add it to all the others
        char c = tolower(word[i]);
        index += 251 * (int) c;
    }
    // mod the index by the max to make sure everything fits
    index = index % N;
    return index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    int numWords = 0;
    if (dict == NULL)
    {
        printf("dictionary == Null\n");
        return false;
    }
    char *w = malloc(LENGTH + 1);
    while (fscanf(dict, "%s", w) != EOF)
    {
        //allocate memory for new node
        struct node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            printf("newNode == NULL");
            return false;
        }
        // transfer word into node
        strcpy(newNode->word, w);
        newNode->next = NULL;
        int index = hash(w);
        //For each index without a list behind it, attach the newNode
        if (table[index] == NULL)
        {
            table[index] = newNode;
            numberofwords++;
        }
        else
        {
            //For each index with a list behind it, attach the newNode to the front
            newNode->next = table[index];
            table[index] = newNode;
            numberofwords++;
        }
    }
    //free up the word pointer & close the file
    free(w);
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return numberofwords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor;
    //Loop through each index
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        if (cursor == NULL)
        {
            continue;
        }
        node *tmp = cursor;
        //Loop along Linked List while freeing each node
        do
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        while (tmp != NULL);
    }
    free(cursor);

    return true;
}