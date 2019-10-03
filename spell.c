/****************************************************************************
 * dictionary.c
 *
 * Application Security, Assignment 1
 *
 * Submission from Yu Zhang
 ***************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// TODO: use regex
bool isPunctuation(char currChar) {
    if (currChar == '\'' || currChar == '.') {
        return false; 
        // TODO: handle currChar == '“' || currChar == '”' ||
    } else if ((currChar >= 33 && currChar <= 64) || (currChar >= 91 && currChar <= 96) || (currChar >= 123 && currChar <= 126)) {
        return true;
    } else {
        return false; 
    }
}

bool isAsciiLetter(char ch) {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
        return true; 
    } else {
        return false; 
    }
}


/**
 * Array misspelled is populated with words that are misspelled. Returns the length of misspelled.
 */
/**
 * Inputs:
 *  fp:         A file pointer to the document to check for spelling errors.
 *  hashtable:  The hash table used to determine spelling
 *  misspelled: An empty char* array to be populated with misspelled words.
 *              This array will never be greater than 1000 words long.
 *            
 * Returns:
 *  int:        The number of words in the misspelled arary.
 *
 * Modifies:
 *  misspelled: This array will be filled with misspelled words.
 *
 * Example:
 *  int num_misspelled = check_words(text_file, hashtable, misspelled);
 **/
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) {
    // Set int num_misspelled to 0.
    int numMisspelled = 0; 
    char currWord[LENGTH + 1]; 
    int currIndex = 0; 
    bool longword = false; 
    char currChar = fgetc(fp);
    char nextChar; 
    while (currChar != EOF && numMisspelled < MAX_MISSPELLED) {
        nextChar = fgetc(fp);
        if (currIndex == LENGTH) {
            longword = true; 
            currWord[currIndex] = '\0';
            if (!check_word(currWord, hashtable)) {
                misspelled[numMisspelled] = malloc((LENGTH + 1) * sizeof(char));
                strcpy(misspelled[numMisspelled++], currWord);
            }
            // reset currWord and currIndex
            strcpy(currWord, "");
            currIndex = 0;
        }
        if ((currChar == '.' && (nextChar == ' ' || nextChar == EOF || nextChar == '\n')) || currChar == ' ' || currChar == '\n' || isPunctuation(currChar)) {
            longword = false; 
            if (currIndex != 0) {
                currWord[currIndex] = '\0';
                if (!check_word(currWord, hashtable)) {
                    misspelled[numMisspelled] = malloc((LENGTH + 1) * sizeof(char));
                    strcpy(misspelled[numMisspelled++], currWord);
                }
            // reset currWord and currIndex
                strcpy(currWord, "");
                currIndex = 0;
            }
        } else if (!longword) {
            currWord[currIndex++] = currChar;
        }
        currChar = nextChar;
    }
    fclose(fp);
    return numMisspelled;
}



/**
 * Returns true if word is in dictionary else false.
 */
/**
 * Inputs:
 *  word:       A word to check the spelling of.
 *  hashtable:  The hash table used to determine spelling
 *            
 * Returns:
 *  bool:       A boolean value indicating if the word was correctly spelled.
 *
 * Modifies:
 *  
 * Example:
 *  bool correct  = check_word(word, hashtable);
 **/
bool check_word(const char* word, hashmap_t hashtable[]) {
    if (strcmp(word, "\0") == 0) {
        return true; 
    }
    char lowerCaseWord[LENGTH + 1]; 
    int i = 0; 
    while (word[i] != '\0') {
        lowerCaseWord[i] = tolower(word[i]);
        i++; 
    }
    lowerCaseWord[i] = '\0';
    int bucket = hash_function(lowerCaseWord);
    hashmap_t cursor = hashtable[bucket];
    while (cursor != NULL) {
        if (strcmp(lowerCaseWord, cursor->word) == 0) {
            return true; 
        }
        cursor = cursor->next; 
    }
    return false; 
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
/**
 * Inputs:
 *  dictionary_file:    Path to the words file.
 *  hashtable:          The hash table to be populated.
 *            
 * Returns:
 *  bool:       Whether or not the hashmap successfully populated.
 *
 * Modifies:
 *  hashtable: This hashmap should be filled with words from the file provided.
 *
 * Example:
 *  bool success = load_dictionary("wordlist.txt", hashtable);
 **/
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {
    // Initialize all values in hash table to NULL.
    for (int i = 0; i < HASH_SIZE; ++i) {
        hashtable[i] = NULL;
    }
    FILE* fptr = fopen(dictionary_file, "r");
    if (fptr == NULL) {
        printf("Cannot open file \n");
        return false; 
    }
    char currWord[LENGTH + 1]; 
    int currIndex = 0; 
    char currChar = fgetc(fptr);
    while (currChar != EOF) {
        if (currChar == ' ' || currChar == '\n' || currIndex == LENGTH) {
            // get the node ready
            currWord[currIndex] = '\0';
            hashmap_t newNode = malloc(sizeof(struct node));
            strcpy(newNode->word, currWord);
            newNode->next = NULL; 
            // put the node in the hashmap
            int indexInHashmap = hash_function(currWord); 
            if (hashtable[indexInHashmap] != NULL) {
                newNode->next = hashtable[indexInHashmap]; 
            }
            hashtable[indexInHashmap] = newNode;
            // reset currWord and currIndex
            strcpy(currWord, "");
            currIndex = 0;
        } else {
            currWord[currIndex++] = currChar;
        }
        currChar = tolower(fgetc(fptr));
    }
    fclose(fptr);
    return true; 
}
