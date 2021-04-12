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
void test_preferences(void);
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cyclecheck(int index, int target, int source);

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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
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
            if ((i != j) && ((preferences[i][j] - preferences[j][i]) > 0))
                // for each case where i and j are not equal & i is prefered over j assign it to the current index in the p array
                // then increment the pair_count and the p index
            {
                pairs[p].winner = i;
                pairs[p].loser = j;
                pair_count++;
                p++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // do while loop for bubble sorting while each pass has swaps; the sort will end when a pass has no swaps
    int swaps = 0;
    do
    {
        swaps = 0;
        for (int p = 0; p < pair_count; p++)
        {
            // Looping through pairs of preferences and swaping them if the first is lower than the second.
            // This will bubble the lowest values to the end.
            int i = pairs[p].winner;
            int j = pairs[p].loser;
            int sovp = (preferences[i][j] - preferences[j][i]);
            int q = p + 1;
            int a = pairs[q].winner;
            int b = pairs[q].loser;
            int sovq = (preferences[a][b] - preferences[b][a]);
            // swap function => maybe make it a function later?
            if (sovp < sovq)
            {
                pair temp = pairs[p];
                pairs[p] = pairs[q];
                pairs[q] = temp;
                swaps++;
            }
        }
    }
    while (swaps > 0);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Lock function
    for (int p = 0; p < pair_count; p++)
    {
        int i = 0, j = 0;
        i = pairs[p].winner;
        j = pairs[p].loser;
        bool cycle_found = true;
        // call cycle check function and assign to boolean
        cycle_found = cyclecheck(p, i, j);
        if (cycle_found == false)
        {
            locked[i][j] = true;
        }

    }
    return;
}

// cycle check function!! checks for cycles in the graph!
bool cyclecheck(int index, int source, int target)
{
    // search for the current source as a destination below the current index and compare it's source against the target,
    // then search for that positions source again
    bool cycle_found = false;
    //decrement throuh pairs array from index of source where function was called.
    for (int s = index; s >= 0; s--)
    {
        int origin = pairs[s].winner;
        int destination = pairs[s].loser;
        if (source == destination)
        {
            if (origin == target)
            {
                cycle_found = true;
            }
            else
            {
                cycle_found = cyclecheck(s, origin, target);
            }
        }
        if (cycle_found == true)
        {
            break;
        }
    }
    return cycle_found;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int j = 0, i = 0;

    for (j = 0; j < candidate_count; j++)
    {
        bool is_source = true;
        for (i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == true)
            {
                is_source = false;
                break;
            }
        }
        if (is_source == true)
        {
            printf("%s\n", candidates[j]);
            return;
        }
    }
    return;
}
