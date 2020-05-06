// Implements a dictionary's functionality

#include <strings.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26 * 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int n = hash(word);
    for (node *tmp = table[n]; tmp != NULL; tmp = tmp->next)
    {
        int cmp = strcasecmp(word, tmp->word);
        if (cmp == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int n = 0;
    if ('a' <= word[0] && word[0] <= 'z' && 'a' <= word[1] && word[1] <= 'z')
    {
        n = (word[0] - 97) * 26 + (word[1] - 97);
    }
    if ('A' <= word[0] && word[0] <= 'Z' && 'A' <= word[1] && word[1] <= 'Z')
    {
        n = (word[0] - 65) * 26 + (word[1] - 65);
    }
    if ('A' <= word[0] && word[0] <= 'Z' && 'a' <= word[1] && word[1] <= 'z')
    {
        n = (word[0] - 65) * 26 + (word[1] - 97);
    }
    if ('a' <= word[0] && word[0] <= 'z' && 'A' <= word[1] && word[1] <= 'Z')
    {
        n = (word[0] - 97) * 26 + (word[1] - 65);
    }
    return n;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    unsigned int n = 0;
    if (file == NULL)
    {
        fclose(file);
        return false;
    }
    else
    {
        char w[LENGTH + 1];
        while (fscanf(file, "%s", w) != EOF)
        {
            n = hash(w);
            node *t = malloc(sizeof(node));
            if (t != NULL)
            {
                strcpy(t->word, w);
                t->next = table[n];
            }
            table[n] = t;
        }
        fclose(file);
        return true;
    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int n = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            n++;
        }
    }
    return n;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}