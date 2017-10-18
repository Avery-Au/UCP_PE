/**
 * UNIX & C Programming (COMP1000) Assignment
 * Author: Avery Au (14740248)
 * Description: header file for prototypes used for Action functions callback
 **/

 #ifndef CALLBACKFUNC_H
 #define CALLBACKFUNC_H

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 /* for the true or false declaration */
 #include "check.h"

 int userDecision(char* word, char* suggestion);

 int autoCorrect(char* word, char* suggestion);

 #endif
