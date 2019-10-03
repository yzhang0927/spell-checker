#include <stdio.h>
#include "dictionary.h"

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_worlist.txt"

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        // TODO: log error
    }
    hashmap_t hashtable[HASH_SIZE];
    char *misspelled[MAX_MISSPELLED];
    bool success = load_dictionary(DICTIONARY, hashtable);
    printf("%d\n", success);
    printf("~~~~~~~~~~~~~~~%s\n", argv[1]);
    FILE *fp = fopen(argv[1], "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    printf("misspelled: %d\n", num_misspelled);
    for (int i = 0; i < 8; ++i) {
        printf("%s\n", misspelled[i]);
    }
    return 0;
}
