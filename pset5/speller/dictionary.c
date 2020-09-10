// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// 1 letter + 2 letters('s not possible as minimum of 3 letters' + 3++ letters)
const unsigned int N = (26) + (26 * 26) + (26 * 27 * 27);

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    // Gets the hash and the nodewalker
    node *temp;
    char *checkword = malloc(strlen(word) + 1);
    strcpy(checkword, word);
    for (int i = 0, n = strlen(checkword); i < n; i++)
    {
        checkword[i] = tolower(checkword[i]);
    }

    int hashword = hash(checkword);
    //printf("%i", hashword);
    if (table[hashword] == NULL)
    {
        free(checkword);
        return false;
    }
    else
    {
        temp = table[hashword];
    }

    //Walk until found, if null, return false
    while (strcmp(temp->word, checkword) != 0)
    {
        if (temp->next == NULL)
        {
            free(checkword);
            return false;
        }
        else
        {
            temp = temp->next;
        }
    }
    free(checkword);
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    char *insertword = malloc(strlen(word) + 1);
    if (insertword == NULL)
    {
        return -1;
    }
    strcpy(insertword, word);
    int hashnumber;

    // Hash words with 1 letter
    if (strlen(insertword) == 1)
    {
        hashnumber = insertword[0] - 97;
    }

    // Hash words with 2 letters
    else if (strlen(insertword) == 2)
    {
        hashnumber = ((insertword[0] - 96) * 26) + (insertword[1] - 97);
    }

    // Hash words with >= 3 letters
    else
    {
        if (insertword[1] == '\'')
        {
            // All 1 letters + 2 letters + 3rd letters
            hashnumber = 26 +
                         (26 * 26) +
                         // 1st letter + pos for " ' " + 3rd letter
                         ((insertword[0] - 96) * 26 * 27) + (26 * 27) + (insertword[2] - 97);
        }
        else if (insertword[2] == '\'')
        {
            // All 1 letters + 2 letters + 3rd letters
            hashnumber = 26 +
                         (26 * 26) +
                         // 1st letter + 2nd letter + pos for " ' "
                         ((insertword[0] - 96) * 26 * 27) + ((insertword[1] - 96) * 27) + 27;
        }
        else
        {
            // All 1 letters + 2 letters + 3rd letters
            hashnumber = 26 +
                         (26 * 26) +
                         // 1st letter + 2nd letter  + 3rd letter
                         ((insertword[0] - 96) * 26 * 27) + ((insertword[1] - 96) * 27) + (insertword[2] - 96);
        }
    }

    free(insertword);
    return hashnumber;
}

// Loads dictionary into memory, returning true if successful else false
// Since the average length of english word is 5 character,
// We will use half of that for each hash
bool load(const char *dictionary)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Read Dictionary File
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("%s\n", "self error");
        return false;
    }

    char insertword[LENGTH + 1];
    while (fscanf(file, "%s", insertword) != EOF)
    {
        for (int i = 0, n = strlen(insertword); i < n; i++)
        {
            insertword[i] = tolower(insertword[i]);
        }

        // Gets word from dictionary
        int hashword = hash(insertword);


        // Adds word into dictionary
        // If Hash table is empty
        if (table[hashword] == NULL)
        {
            // Make a new node
            node *x = malloc(sizeof(node));
            if (x == NULL)
            {
                return false;
            }

            // Fill the new node
            strcpy(x->word, insertword);
            x->next = NULL;


            // Add new node to table
            table[hashword] = x;
        }
        else
        {
            // Create walker node
            node *temp = table[hashword];

            if (temp == NULL)
            {
                return false;
            }

            // Move to last node in linked list
            while (temp->next != NULL)
            {
                //printf("%s\n", temp->word);
                temp = temp->next;
            }

            // Create new node and adds the new node to linked list
            node *x = malloc(sizeof(node));
            if (x == NULL)
            {
                return false;
            }
            strcpy((x->word), insertword);
            x->next = NULL;
            temp->next = x;

        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int total_size = 0;
    // TODO
    // Goes through all hash table
    for (int hashtablePos = 0; hashtablePos < N; hashtablePos++)
    {
        // If empty move to next hash;
        if (table[hashtablePos] != NULL)
        {
            total_size++;
            // If there is a next node, increase totalsize;
            for (node *walker = table[hashtablePos]; walker->next != NULL; walker = walker->next)
            {
                total_size++;
            }

        }
    }
    return total_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int hashtablePos = 0; hashtablePos < N; hashtablePos++)
    {
        // If empty move to next hash;
        if (table[hashtablePos] != NULL)
        {
            // If there is only one node to delete
            node *walker = table[hashtablePos];
            if (walker->next == NULL)
            {
                free(walker);
            }
            else
            {
                node *todelete;
                walker = walker->next;

                // If there is a next node, increase totalsize;
                for (todelete = table[hashtablePos]; todelete->next != NULL; walker = walker->next)
                {
                    free(todelete);
                    todelete = walker;
                }
                free(todelete);
            }
        }
    }
    return true;
}
