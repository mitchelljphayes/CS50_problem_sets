#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void print_preferences(void);
void print_pairs_array(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }
    print_preferences();
    add_pairs();
    print_pairs_array();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

void print_preferences(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("candidate: %s over %s by: %i\n",candidates[i],candidates[j],preferences[i][j]);
        }
    }
}
void print_pairs_array(void)
{
    for (int p = 0; p < (candidate_count + (candidate_count - 1)) / 2; p++)
    {
        int i = 0, j = 0;
        i = pairs[p].winner;
        j = pairs[p].loser;
        printf("winner:%s loser:%s strenth of victory:%i\n",candidates[i],candidates[j],preferences[i][j]);
    }
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // loop through candidate array
    for (int i = 0; i < candidate_count; i++)
    {
        // Compare candidate name to vote name
        if (strcmp(candidates[i], name) == 0)
        {
            //record vote rank in rank array
            ranks[rank] = i;
            return true;
        }
    }
    //return true if name isnt found
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // identify each candidate for given voter rank
    for (int p = 0; p < candidate_count; p++)
    {
        int i;
        int j;
        i = ranks[p];
        //loops through all ranks lower thank current and increments the prefferences array
        for (int o = (p + 1); o < candidate_count; o++)
        {
            j = ranks[o];
            preferences[i][j]++; // record the preffered ranking

        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for (int i = 0, p = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if ((i != j) && (preferences[i][j] > preferences[j][i]))
            // if (preferences[i][j] > preferences[j][i])
            {
                pairs[p].winner = i;
                pairs[p].loser = j;
                pair_count++;
                p++;
                printf("winner:%s loser:%s paircount:%i\n",candidates[i],candidates[j],pair_count);
            }
            // else if ((i != j) && (preferences[i][j] < preferences[j][i]))
            // else if (preferences[i][j] < preferences[j][i])
            // {
            //     pairs[p].winner = j;
            //     pairs[p].loser = i;
            //     pair_count++;
            //     p++;
            // }

        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int swaps = 0;
    do
    {
        swaps = 0;
        for (int p = 0; p < pair_count; p++)
        {
            int i = pairs[p].winner;
            int j = pairs[p].loser;
            int sovp = preferences[i][j];
            int q = p + 1;
            int a = pairs[q].winner;
            int b = pairs[q].loser;
            int sovq = preferences[a][b];
            printf("pairsP: %i, pairsQ: %i\n",sovp,sovq);
            if (sovp < sovq)
            {
                pair temp = pairs[p];
                pairs[p] = pairs[q];
                pairs[q] = temp;
                swaps++;
            }
        }
    } while (swaps > 0);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

