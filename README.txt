/* This is the documentation README.txt for UCP 2017 sem2 assignment */
/* author: Avery Au */
/* submission date 26/10/2017 */

Usage instruction
$ make

$ ./spellChecker user.txt

1. List of all files submitted and their purpose

spellChecker.c - contain the main function - handle user arguements and user display for spell check program status, all the required functionality are called within this main function
spellChecker.h - header file for spellChecker.c contain - contain boolean and required #include declarations 
fileFunc.c - contain 4 functions: stringFilter, readFile, writeFile, readSetting - handles all file related functionality such as reading dictionary user file and setting file, also writing the corrected word array to user file and finally the required function to filter unwanted non alphabet characters
fileFunc.h - header file for fileFunc.c - contain required #include and functions forward declarations
linkList.c - contain 4 functions: insertNewNode, freeLinklist, linkListToArray, freeWordArray to handle all link list related operations and free the required array and linked list
linkList.h - header file for linkList.c - contain required #include, #define, struct for setting and linklist node, and functions forwards declarations
callBackFunc.c - contain 2 functions: UserDecision, autoCorrect to handle suggestion provide from check() and prompt user input to correct word
callBackFunc.h - header file for callBackFunc.c - contain required #include and functions forward declarations
makefile - makefile for compilation
.spellconf - setting configuration
user.txt - testing file user input
dictionary.txt - small sized dictionary
simpledict.words - medium sized dictionary
linux.words - large sized dictionary
README.txt - assignment documentation
README.md - used for github push

2. Program functionality Checklist

I have attempted all the required functionality.
To the best of my knowledge, all the required functionality work as intended. 

a) accept one commandline parameter with relevant error message and exit

   the first stage of test will inidcates to user whether they forgot to input a user file name in command line
   no memory leaked
   free'd properly if user arguement failed
   
b) read the setting file .spellconf and store content in struct

   tested with invalid parameter name or parameter variable
   return proper error messages
   no memory leaked, free'd properly if read setting file failed
   
c) read the dictionary file specified inside the setting file, placing each dictionary word into a linked list
   the dicitonary file contains one word per line. Once the whole dictionary file has been read, program should
   copy the contents of linked list to a dynamically allocated array
   
   tested with non alphabetical character, assuming no words exceed the size of 46 (including null terminator)
   display the loaded word after string has been processed (convert from uppercase to lowercase)
   no memory leaked
   
d) read the user file in the same fashion, assume file consists entirely of words separated whitespace
   the second stage tested with invalid user file name
   no memory leaked, free'd properly 
 
   similar to dictionary file, tested with non alphabetical character with no words exceed the size of 46
   display the laoded word after string has been converted to lowercase
   no memory leaked
  
e) call the pre-exiting function check(), providing callback functions

   works fine with the provided check.o and check.h file 
   promopt user if in no autocorrect condition to check whether the suggestion is correct
   tested with invalid user input and it will ask for it again
   
f) program should write the user file array back to user file, no need to preserve the original formatting
   
   the writing part works fine and the result is in a single line separated with a whitespace
   after all process is done, everything is checked with memory leak and free'd properly

3. bugs or defects
There is a significant loading time for reading the linux.words 

The filter string function convert all non alphabetic character except hyphen to 'a'
which in some situation are not ideal but the main functionaly remain intact

As the exercise did not specific how accurate the correction must be
and it is solely based on characters difference without word meaning attached to it.

valgrind has been used at all stages of the program and show no memory leaked

4. 314 labmachine used
This program has been tested in room 314.232, on computer with service tag HN56HZ1

 
