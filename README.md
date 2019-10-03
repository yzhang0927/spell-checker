# spell-checker
<img src="https://travis-ci.org/yzhang0927/spell-checker.svg?branch=master" />
* Spell checker for Application Security course, which will be later used for extensive testing (including fuzz input)

## Part 2
* How the program works
  * I pretty much implemented as instructed in the file Pseudocode.txt. 
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
* bugs I expected from the code
  * some segmentation fault
    * 
  * it's not gonna recognize `j.ust` as `just`
  * maybe some memory error, as when I malloced all the places for the dictionary, I never get around to free those stuff. Maybe valgrind will report those as memory errors
* why those bugs might occur
  * lack of consideration when writing the code
  * I didn't first write unit tests and then start writing the program, so I, the developer might not think of some of the edge cases
  * I didn't start the homework until the last day, so I might be careless
* steps took to mitigate those bugs
  * 
