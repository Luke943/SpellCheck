// Implements the spell-checker

#include <ctype.h>
#include <stdio.h>

#include "dictionary.h"

#define DICTIONARY "words.txt" // Default dictionary

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./spellcheck [DICTIONARY] text\n");
        return 1;
    }

    // Determine dictionary to use
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // Load dictionary
    bool loaded = load(dictionary);
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }
    printf("Loaded %u words from dictionary.\n", size());

    // Open text
    char *text = (argc == 3) ? argv[2] : argv[1];
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    // Perform spell-check
    printf("\nMISSPELLED WORDS\n\n");

    int index = 0, misspellings = 0, words = 0, line = 1;
    char word[LENGTH + 1];

    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        if (c == '\n')
            line++;

        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = c;
            index++;

            // Ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                while ((c = fgetc(file)) != EOF && isalpha(c))
                    ;
                index = 0;
            }
        }

        // Ignore words with numbers (like MS Word)
        else if (isdigit(c))
        {
            while ((c = fgetc(file)) != EOF && isalnum(c))
                ;
            index = 0;
        }

        // Found a word
        else if (index > 0)
        {
            word[index] = '\0';
            words++;

            // Check word's spelling and print if misspelled
            bool misspelled = !check(word);
            if (misspelled)
            {
                printf("%d. %s\n", line, word);
                misspellings++;
            }
            index = 0;
        }
    }

    // Check for error
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", text);
        unload();
        return 1;
    }

    // Close text
    fclose(file);

    // Unload dictionary
    bool unloaded = unload();
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    return 0;
}
