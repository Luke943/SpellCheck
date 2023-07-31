## Description

A command-line spell-check program written in `C`.

Allows the user to pass in a text file and dictionary of the their choosing. Then outputs all spelling mistakes in the text compared to the dictionary used.

### Dictionaries included

A default dictionay is provided in `words.txt`, which will be used when the user does not specify a dictionary. It is a list of over 466,000 English words. It originates from this [english-words](https://github.com/dwyl/english-words) repository.

A smaller list is also provided in `words-small.txt`, contains 64,000 English words.

## Building

The spell-checker can be compiled from this folder. For example, using `gcc`:

```
gcc -o spellcheck spellcheck.c dictionary.c
```

## Usage

To use the spell-checker on a file called `text`, run the following:

```
./spellcheck [dictionary] text
```
`dictionary` is an optional argument. It will default to `words.txt` when not provided.

The program will then print the line number and word of all mispelt words to the command line.

## Contents

The files required for the program are:

- `spellcheck.c` - Main file to run the spell checker.
- `dictionary.c` - Defines data structure and functions with loading the dictionary file into a hash table for use in the spell checker.
- `dictionary.h` - Declarations for including dictionary.c in spellcheck.c.
