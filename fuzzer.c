#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// fuzz_target.cc
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    hashmap_t hashtable[HASH_SIZE];
    char *misspelled[MAX_MISSPELLED];
    check_words_buf(Data, Size, hashtable, misspelled);
    return 0;  // Non-zero return values are reserved for future use.
}