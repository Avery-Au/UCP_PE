/**
 * UNIX & C Programming (COMP1000) Assignment
 * linkList.h
 * Author: Avery Au (14740248)
 * Description: linklist header file for prototypes forward declaration
 */

/* include guards for this header file */
#ifndef LINKLIST_H
#define LINKLIST_H

/* assuming lenght of wards to be supported by this program is 40
 * and +1 to handle the null terminator char '/0' */
#define MAX_WORD_SIZE 41
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* struct for each word */
typedef struct
{
    /* each word string is allocated with the maximum word size */
    char word[MAX_WORD_SIZE];
}WORD;

/* struct for each setting parameter */
typedef struct
{
    /* store dictionary file name string */
    char dictfile[MAX_WORD_SIZE];
    int maxdifference;
    int autocorrect;
} SETTING;

/* struct for each Node which holds a word data struct
   and the next node pointer */
typedef struct Node
{
    WORD* word;
    SETTING* setting;
    struct Node* next;
} Node;

/* struct for head node of each linked list */


Node* createEmptyList(void);

void freeLinkList(Node* head);

void linkListToArray(Node* head, char* array[], int arrayLength);

void freeWordArray(char* array[], int arrayLength);

#endif
