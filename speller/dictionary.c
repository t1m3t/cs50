// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

unsigned int word_count;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int h = hash(word);
    node *list = table[h];
    while (list != NULL)
    {
        if (strcasecmp(word, list->word) == 0)
        {
            return true;
        }
        list = list->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Sums the ASCII characters in string, then mod to table size
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        char c = word[i];
        if (isalpha(c))
        {
            sum += (int) tolower(c);
        }
        else
        {
            sum += (int) c;
        }
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dictf = fopen(dictionary, "r");
    if (dictf == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(dictf, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        int h = hash(word);
        strcpy(n->word, word);
        n->next = table[h];
        table[h] = n;

        word_count++;
    }

    fclose(dictf);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *list = table[i];
        while (list != NULL)
        {
            node *tmp = list;
            list = list->next;
            free(tmp);
        }
        if (i == N - 1 && list == NULL)
        {
            return true;
        }
    }
    return false;
}
