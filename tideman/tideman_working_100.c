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
void print_preferences(void);
void print_pairs_array(void);
void print_locked_array(void);
bool cyclecheck(int index, int target, int source);
void test_preferences(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    /**/
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
    /**/
    // test_preferences();
    print_preferences();
    add_pairs();
    print_pairs_array();
    sort_pairs();
    print_pairs_array();
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
        printf("\n");
    }
    printf("\n\n");
}
void print_pairs_array(void)
{
    for (int p = 0; p < pair_count; p++)
    {
        int i = 0, j = 0;
        i = pairs[p].winner;
        j = pairs[p].loser;
        int sov = (preferences[i][j] - preferences[j][i]);
        printf("winner:%s loser:%s strenth of victory:%i\n",candidates[i],candidates[j],sov);
    }
    printf("\n\n");
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
            // ADD COMMENT EXPLAINING BELOW
            {
                pairs[p].winner = i;
                pairs[p].loser = j;
                pair_count++;
                p++;
                // printf("winner:%s loser:%s paircount:%i\n",candidates[i],candidates[j],pair_count);
            }
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
            int sovp = (preferences[i][j] - preferences[j][i]);
            int q = p + 1;
            int a = pairs[q].winner;
            int b = pairs[q].loser;
            int sovq = (preferences[a][b] - preferences[b][a]);
            // printf("pairsP: %i, pairsQ: %i\n",sovp,sovq);
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
    for (int p = 0; p < pair_count; p++)
    {
        int i = 0, j = 0;
        i = pairs[p].winner;
        j = pairs[p].loser;
        bool cycle_found = true;

        cycle_found = cyclecheck(p,i,j);
        printf("cycle found: %i\narrow number: %i\n\n", cycle_found, (p + 1));
        if (cycle_found == false)
        {
            locked[i][j] = true;
        }
        // search for the current source as a destination below the current index and compare it's source against the target, then search for that positions source again

        print_locked_array();
    }
    return;
}

void print_locked_array(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf(" %i  ", locked[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

bool cyclecheck(int index, int source, int target)
{
    bool cycle_found = false;
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

            cycle_found = cyclecheck(s, origin, target);
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
        for ( i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == true)
            {
                is_source = false;
                break;
            }
        }
        if (is_source == true)
        {
            printf("%s\n",candidates[j]);
            return;
        }
    }
    printf("nope!\n");
    return;
}

void test_preferences(void)
{
    candidate_count = 5;
    candidates[0] = "A";
    candidates[1] = "B";
    candidates[2] = "C";
    candidates[3] = "D";
    candidates[4] = "E";

    preferences[0][0] = 0;
    preferences[0][1] = 7;
    preferences[0][2] = 5;
    preferences[0][3] = 5;
    preferences[0][4] = 4;

    preferences[1][0] = 5;
    preferences[1][1] = 0;
    preferences[1][2] = 7;
    preferences[1][3] = 6;
    preferences[1][4] = 7;

    preferences[2][0] = 7;
    preferences[2][1] = 5;
    preferences[2][2] = 0;
    preferences[2][3] = 6;
    preferences[2][4] = 6;

    preferences[3][0] = 7;
    preferences[3][1] = 6;
    preferences[3][2] = 6;
    preferences[3][3] = 0;
    preferences[3][4] = 4;

    preferences[4][0] = 8;
    preferences[4][1] = 5;
    preferences[4][2] = 6;
    preferences[4][3] = 8;
    preferences[4][4] = 0;

    // preferences[0][0] = 0;
    // preferences[0][1] = 0;
    // preferences[0][2] = 0;
    // preferences[0][3] = 0;
    // preferences[0][4] = 0;

    // preferences[0][0] = 0;
    // preferences[0][1] = 0;
    // preferences[0][2] = 0;
    // preferences[0][3] = 0;
    // preferences[0][4] = 0;

    return;
}