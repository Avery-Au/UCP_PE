/**
 * * UNIX & C Programming (COMP1000) Assignment
 * * linkList.h
 * * Author: Avery Au (14740248)
 * * Description: linklist header file for prototypes forward declaration, include required libraries and declare max word size
 * */

/* include guards for this header file */
#ifndef LINKLIST_H
#define LINKLIST_H

/* assumption that no word should exceed the longest word within the library
 * using this bash line:
 * cat linux.words | sed 's/ /\n/g' | sort | uniq | awk '{print length, $0}' | sort -nr | head
 * reference : https://stackoverflow.com/questions/8962466/finding-the-longest-word-in-a-text-file
 * the longest word within linux.word can be determined as 45
 * and +1 to handle the null terminator char '/0' i.e. 46 max word length*/
#define MAX_WORD_SIZE 46
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* struct for reading in parameters from .spellconf */
typedef struct
{
    /* store dictionary file name string */
    char* dictfile;
    int maxdifference;
    int autocorrect;
} Setting;

/* struct for each Node which holds a word data struct
 *  * and the next node pointer */
typedef struct Node
{
    /* void* for generic link list */
    void* data;
    struct Node* next;
} Node;

Node* insertNewNode(Node* head, char* word);

void freeLinkList(Node* head);

void linkListToArray(Node* head, char* array[], int arrayLength);

void freeWordArray(char* array[], int arrayLength);

#endif

