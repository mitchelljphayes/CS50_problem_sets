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
    int most_votes = 0;
    // find the highest number of votes
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes > most_votes)
        {
            most_votes = candidates[j].votes;
        }
    }
    // print candidates with the highest number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == most_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

