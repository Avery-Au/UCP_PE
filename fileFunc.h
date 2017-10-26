/**
 * * UNIX & C Programming (COMP1000) Assignment
 * * Author: Avery Au (14740248)
 * * Description: header file for prototypes used for file handling functions
 * * mainly for reading dictionary and user file, outputing autocorrected word
 * * array back to the user file
 * **/

#ifndef FILEFUNC_H
#define FILEFUNC_H

/* fprintf and fscanf*/
#include <stdio.h>
/* strcpy */
#include <string.h>

#include <stdlib.h>
/* word struct */
#include "linkList.h"
/* for boolean declaration */
#include "check.h"

void stringFilter(char* stringInput);
int readFile(Node* head, char* fileName);
int writeFile(char* correctWordArray[], int arrayLength, char* fileName);
int readSetting(Setting* settingHead);


#endif

