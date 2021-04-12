#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
candidate merge_sort(candidate C);
candidate merge(candidate A, candidate B, int A_size, int B_size);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

bool vote(string name)
{
    // Loop over all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Compare candidate name to vote name
        if (strcmp(candidates[i].name, name) == 0)
        {
            //increment votes by name if the comparison is true & exit return false so the invalid vote doesn't run
            candidates[i].votes++;
            return 1;
        }
    }
    //return true if name isnt found
    return 0;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    merge_sort(candidates[MAX-1]);
    for (int j = 0; j < candidate_count; j++)
    {
        // call sort algorithhm
        // if arraylength is 1 return
        // else
        //      sort first half
        //      sort second half
        //      merge arrays a & b

        printf("%s: %i \n",candidates[j].name, candidates[j].votes);
    }
    return;
}

candidate merge_sort(candidate C)
{

    int array_size = sizeof(C) / 1; //find array length
    if (array_size == 1)
    {
        return C;
    }
    candidate array_A[(array_size / 2)];
    candidate array_B[((array_size / 2) + 1)];
    for (int i = 0; i < array_size; i++)
    {
        int A_size = 0, B_size = 0;
        if (i <= array_size/2)
        {
            array_A + candidates[i];
            A_size++;
        }
        else
        {
            array_B + candidates[i];
            B_size++;
        }
    }
    merge_sort(array_A);
    merge_sort(array_B);

    candidates = merge(array_A, array_B, A_size, B_size);

    return C;
}

candidate merge(candidate A, candidate B, int A_size, int B_size)
{
    int L = 0, R = 0, m = 0;
    candidate temp[(A_size + B_size)];
    do
    {
        if ((A[L].votes <= B[R].votes) && (L < A_size))
        {
            temp[m] = A[L];
            m++;
            L++;
        }
        else if ((A[L].votes >= B[R].votes) && (R < B_size))
        {
            temp[m] = B[R];
            m++;
            R++;
        }
        else if ((L == A_size) && (R < B_size))
        {
            do
            {
                temp[m] = B[R];
                m++;
                R++;
            } while (R < B_size);
        }
        else if ((L < A_size) && (R == B_size))
        {
            do
            {
                temp[m] = A[L];
                m++;
                L++;
            } while (L < A_size);
        }
    } while ((L < A_size) && (R < B_size))

    return temp;
}