/**
 * UNIX & C Programming (COMP1000) Assignment - Spell checking code.
 * Author: Avery Au (14740248)
 * Description: contain all the prototypes to handle link
 * list related functionality
 **/

/* This function create an empty linked list and
 * dynamically allocated for the head node*/
#include "linkList.h"


/* Converts a linked list into a dynamically allocated array.
 * the array char pointer is pre allocated with size of arrayLength
 * before passing into this function */
void linkListToArray(Node* head, char* array[], int arrayLength)
{
    Node* currentNode = head;
    int i;

    /* loop through each of the elements jump to the next node in
     * the list and copy it into the arry */
    for(i = 0; i < arrayLength; i++)
    {
        currentNode = currentNode->next;
        array[i] = (char*)malloc(MAX_WORD_SIZE*sizeof(char));
        strcpy(array[i], ((Word*)(currentNode->data))->wordString);
    }
}

/* this is the function for freeing the word array */
void freeWordArray(char* array[], int arrayLength)
{
    int i;

    /* loop through the entire the array and free each of the element */
    for(i=0; i < arrayLength; i++)
    {
        free(array[i]);
    }
}

/* free each element in the link list and free the head node of the list */
void freeLinkList(Node* head)
{
    Node* current = head;
    /* a temporary node is used so that we dont lose the
     * link after freeing the current node */
    Node* tempNode;

    current = current->next;

    /* loop through the entire link list and free each node */
    while(current != NULL)
    {
        tempNode = current;
        current = current->next;
        free(tempNode);
    }

    /* free the head node of the link list */
    free(head);
    head = NULL;
}
