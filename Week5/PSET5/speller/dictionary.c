// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
//fopen fclose fscanf
#include <stdio.h>
//mallco free
#include <stdlib.h>
//strcpy
#include <string.h>
//strcasecmp
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 5381;

// Hash table
node *table[N];

unsigned int dic_size = 0;

unsigned int hashcode = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    hashcode = hash(word);
    node *cur = table[hashcode];
    while (cur != NULL)
    {
        if (strcasecmp(word, cur->word) == 0)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /*  hash * 33 + c  */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO: Load all the data into hash table
    char word[LENGTH + 1];
    FILE *dic = fopen(dictionary, "r");
    if (dic != NULL)
    {
        while (fscanf(dic, "%s", word) != EOF)
        {
            node *n = malloc(sizeof(node));
            if (n != NULL)
            {
                strcpy(n->word, word);
                hashcode = hash(word);
                n->next = table[hashcode];
                table[hashcode] = n;
                dic_size++;
            }
        }
        fclose(dic);
    }
    else
    {
        return false;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dic_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n != NULL)
        {
            node *tmp = n;
            n = n->next;
            free(tmp);
        }
        if (i == N - 1 && n == NULL)
        {
            return true;
        }
    }
    return false;
}
