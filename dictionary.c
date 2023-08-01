// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

#define HASH_TABLE_SIZE 65536U // 2^16

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

unsigned int WORD_COUNT = 0;

node *table[HASH_TABLE_SIZE];

bool check(const char *word)
{
    unsigned int h = hash(word); // need to pass lower case word into hash function
    node *n = table[h];
    while (n != NULL)
    {
        if (strcasecmp(n->word, word) == 0)
            return true;
        else
            n = n->next;
    }
    return false;
}

// Hashes using djb2 c.f. http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned int h = 5381;
    char c;
    while (*word++) // while next character not \0
    {
        c = tolower(*word);
        h = ((h << 5) + h) + c; // hash * 33 + *str
    }
    return h & (HASH_TABLE_SIZE - 1); // size is power of 2
}

bool load(const char *dictionary)
{
    // make hash table pointers null
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
        table[i] = NULL;
    // open dictionary as file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
        return false;
    char buffer[LENGTH + 1];

    // scan for words and put in hash table
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // for each word in dictionary create node
        node *n = malloc(sizeof(node));
        if (n == NULL)
            return false;

        strcpy(n->word, buffer);

        unsigned int h = hash(n->word);

        // place node at head of list from hash table
        n->next = table[h];
        table[h] = n;
        WORD_COUNT++;
    }
    fclose(file);
    return true;
}

unsigned int size(void)
{
    return WORD_COUNT;
}

bool unload(void)
{
    unsigned int total_free_count = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
            total_free_count++;
        }
    }
    return total_free_count == WORD_COUNT;
}
