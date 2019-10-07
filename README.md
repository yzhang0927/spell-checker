# spell-checker
<img src="https://travis-ci.org/yzhang0927/spell-checker.svg?branch=master" />
* Spell checker for Application Security course, which will be later used for extensive testing (including fuzz input)

## Part 2
### How the program works
* I pretty much implemented as instructed in the file Pseudocode.txt. 
* first, the program loads a dictionary, which is delimited by space or new line
  * then it creates a hashtable (open hashtable with linkedlist) to store all the words
  * all the words are created on the heap, and the pointer was added onto the hashtable/linkedlist
* Then, the program also accepts a testing file
  * the program loops through the file, using punctuation, space, new line, etc. as delimiters to get each word in the file
  * then we need to preprocess the word, to remove the punctuation in the end, to turn the word into lowercase, etc. etc. 
  * A membership query of the word is then performed on the hashtable 
  * if it's a miss, then add that word onto the misspelled list
* since the misspelled list has a limited length, we need to check that boundary to avoid buffer overflow 

* output of Valgrind
```
==4783== Memcheck, a memory error detector
==4783== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==4783== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==4783== Command: ./spell_check test1.txt
==4783== HEAP SUMMARY:
==4783==     in use at exit: 6,918,117 bytes in 123,297 blocks
==4783==   total heap usage: 123,315 allocs, 18 frees, 6,932,453 bytes allocated
==4783==
==4783== LEAK SUMMARY:
==4783==    definitely lost: 100,042 bytes in 1,787 blocks
==4783==    indirectly lost: 6,795,432 bytes in 121,347 blocks
==4783==      possibly lost: 72 bytes in 3 blocks
==4783==    still reachable: 200 bytes in 6 blocks
==4783==         suppressed: 22,371 bytes in 154 blocks
==4783== Rerun with --leak-check=full to see details of leaked memory
==4783==
==4783== For lists of detected and suppressed errors, rerun with: -s
==4783== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)
```
* it is kinda expected that so much memory was lost, as I used so much malloc, but no free at all
* probably I should've freed all of those in main.c
* but then again, since it's not graded, I didn't do it at the time. 

### bugs I expected from the code
* some segmentation fault maybe? 
  * as the input file is quite large, I'm not sure that I handled everything correctly
* it's not gonna recognize `j.ust` as `just`
  * in my implementation, it will just recognize that as two words, 'j' and 'ust', as it treats '.' as a delimiter 
  * UPDATE, now fixed 
* maybe some memory error, as when I malloced all the places for the dictionary, I never get around to free those stuff. Maybe valgrind will report those as memory errors
* if you put any unicode character up, it will not process correctly
* the program also won't process any unicode punctuation, i.e. '“'

### why those bugs might occur
* lack of consideration when writing the code
  * I didn't first write unit tests and then start writing the program, so I, the developer might not think of some of the edge cases
  * those edge cases would include unicode characters and unicode punctuations

### steps took to mitigate those bugs
  * I used multiple print statements to try to figure out what happened when "j.ust" test case was failed
  * probably I should've used GDB, but it just seems like an overkill for such a small project
  * pretty much just regular debug, except for that I was paying extra attention whenever I'm doing strcpy, strcmp, malloc


# part 3 

## bugs found by tests
* it didn't handle "j.ust" as expected
* segmentation fault when reading a_tale_of_two_city.txt

## bugs found by fuzzing
* it didn't handle well two punctuations in a roll
* it didn't handle well programs start with a punctuation
* it didn't handle well unicode punctuations


## how the bugs were fixed 
* it didn't handle "j.ust" as expected
  * as '.' was treated as a delimiter, the program would just read in "j" and then "ust"
  * so I first removed '.' as a delimiter -> which led it to fail previous unit tests
  * then I used a one character look ahead to only use ". " as a delimiter
  * but then fuzzing found that I'm not handling "brew... ", which should be part of dictionary
* segmentation fault when reading a_tale_of_two_city.txt
  * it simply overflowed my misspell list, so I did a bound checking before going further to read the document and add more misspelled words
* bugs found by fuzzing
  * I'm still thinking about other ways to solve such problems, it's kinda hard... maybe we can get more time to finish this homework? 

## how similar bugs can be avoided in the future
* I think even if it's a simple program, maybe take 10 minutes to first write a design doc and think about sample inputs and sample outputs which would likely crash the program
* then we can employ test driven development, and first write such unit tests
* then we can group these unit tests, and implement the easier functionality first and harder functionality later
* probably we can have others review our design doc with us, so that we can think of more edge cases and more ways to test the program. 
* also, maybe after design doc, we can write pseudo code first, and then we should inspect the pseudo code to first come up with algorithms to deal with those edge cases, and then move on to implementation details
* as I have not programmed in C in quite a long time, if I had used the approach detailed above, I would abstract away the algorithm from C implementation, which would make things a lot easier.  

## github and travis set up
* it's pretty much just following the tutorial, plus I knew github from work and school before
* it took me a while to figure out that I don't actually have to set up os for this little C project in travis
* but then it's good to learn about how to set that up in case I need to test in those


