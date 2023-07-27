// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Checks if word is in dictionary
bool check(const char *word);

// Hashes word from dictionary
unsigned int hash(const char *word);

// Loads dictionary into memory
bool load(const char *dictionary);

// Returns number of words in dictionary if loaded else 0
unsigned int size(void);

// Unloads dictionary from memory
bool unload(void);

#endif // DICTIONARY_H
