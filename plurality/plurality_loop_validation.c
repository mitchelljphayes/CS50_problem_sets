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
void merge_sort(candidate arr, int low, int high);

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

// Update vote totals given a new vote
// bool vote(string name)
// {
//     // check that name is a valid name of a candidate
//         //for each element in the candidates array test name against each letter, if name[i] != candidate.name[i] move to next element of candidates
//     bool valid_vote = false;
//     for (int j = 0; (j < candidate_count) && (valid_vote == false); j++)
//     {
//         bool valid_candidate = true;
//         for (int i = 0; i < strlen(name) && valid_candidate == true; i++)
//         {
//             if (name[i] == candidates[j].name[i])
//             {
//                 valid_candidate = true;
//             }
//             else
//             {
//                 valid_candidate = false;
//                 break;
//             }
//         }
//         if (valid_candidate == true)
//         {
//         candidates[j].votes++;
//         valid_vote = true;
//         }
//     }
//     return valid_vote;
// }

bool vote(string name)
{


    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return 1;
        }
    }
    return 0;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
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

void merge_sort (candidate arr, int low, int high)
{
    /*//find array length
    if (length == 1)
    {
        return;
    }

    //find array midpoint
    array_A = (arraylength/2 + 1) // define array A  - first to ith elements of array
    array_B = (arraylength/2) // define array B ith to last elements of element
    merge_sort(array_A);
    merge_sort(array_B);

    */
}