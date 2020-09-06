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
bool check_cycle(int loser, int pointer);

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (i != j)
            {
                int preference1 = ranks[i];
                int preference2 = ranks[j];
                preferences[preference1][preference2]++;
                //printf("[%d][%d]: %d\n", preference1, preference2, preferences[preference1][preference2]);
            }
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int position = 0;
    for (int i = 0; i < MAX; i++)
    {
        for (int j = i + 1; j < MAX; j++)
        {
            if (preferences[i][j] != preferences[j][i])
            {
                if (preferences[i][j] + preferences[j][i] != 0)
                {
                    if (preferences[i][j] > preferences[j][i])
                    {
                        pairs[position].winner = i;
                        pairs[position].loser = j;
                        position++;
                        printf("Pair %d\n", position);
                    }
                    else if (preferences[i][j] < preferences[j][i])
                    {
                        pairs[position].winner = j;
                        pairs[position].loser = i;
                        position++;
                        printf("Pair %d\n", position);
                    }
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp;

    for (int j = 0; j < (MAX * (MAX - 1) / 2) - 1; j++)
    {
        for (int i = 0; i < (MAX * (MAX - 1) / 2) - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                temp.winner = pairs[i].winner;
                temp.loser = pairs[i].loser;
                pairs[i].winner = pairs[i + 1].winner;
                pairs[i].loser = pairs[i + 1].loser;
                pairs[i + 1].winner = temp.winner;
                pairs[i + 1].loser = temp.loser;
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < MAX * (MAX - 1) / 2; i++)
    {
        if (pairs[i].winner != pairs[i].loser)
        {
            if (!check_cycle(pairs[i].loser, i))
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
        }
    }
    return;
}

bool check_cycle(int loser, int pointer)
{
    if (loser == pairs[pointer].winner)
    {
        printf("Loop Found");
        return true;
    }
    for (int i = 0; i < MAX; i++)
    {
        if (locked[loser][i])
        {
            if (check_cycle(i, pointer))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    bool winner = true;
    string winnername;
    // TODO
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            // if win matchup
            if (locked[i][j])
            {
                //Check if any losses
                for (int k = 0; k < MAX; k++)
                {
                    if (locked[k][i])
                    {
                        winner = false;
                    }
                }
                if (winner)
                {
                    winnername = candidates[i];
                }
            }
            winner = true;
        }
    }

    printf("%s\n", winnername);
    return;
}

