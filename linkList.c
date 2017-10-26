/**
 * * UNIX & C Programming (COMP1000) Assignment - Spell checking code.
 * * Author: Avery Au (14740248)
 * * Description: contain all the prototypes to handle link-
 * * list related functionality
 * **/

/* This function create an empty linked list and
 * dynamically allocated for the head node*/
#include "linkList.h"

/* insertNewNode handles all the functionality required to insert a 
 * the target wordInput into an linked list
 * ****Parameters*****
 * Node* currentNode - could be dictionary list or user file list
 * wordInput - the word read from user file or dictionary file
 * ****ReturnVal****
 * return the last node back 
 * */
Node* insertNewNode(Node* currentNode, char* wordInput)
{
    /* dynamically allocate memory to store each node */
    Node* newNode = (Node*)malloc(sizeof(Node));
    /* make sure next pointer points to NULL */
    newNode->next = NULL;
    /* dynamically allocate memory to store a word within the data field */
    newNode->data = (void*)malloc(MAX_WORD_SIZE*sizeof(char));
    /* strncpy to store the wordInput into the linklist under struct data */
    strncpy((char*)newNode->data, wordInput, MAX_WORD_SIZE);
    
    /* making sure the current node is not empty, if it is then it must be the head node */
    if(currentNode != NULL)
    {
        #ifdef DEBUG
        printf("address of currentNode %p\n", (void*)currentNode);
        printf("address of next %p\n", (void*)currentNode->next);
        #endif
        
        /* make sure there is a next pointer and is pointing to NULL */
        while( currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }
        /* make the return node is at the end of Link list */
        currentNode->next = newNode;
    }
    return newNode;
}

/* Converts a linked list into a dynamically allocated array.
 * the array char pointer is pre allocated with size of arrayLength
 * before passing into this function 
 * ****Parameters*****
 * Node* head - link list head node
 * array[] - pointer to the link list
 * arrayLength - size of the array
 * ***ReturnVal*****
 * void
 * */
void linkListToArray(Node* head, char* array[], int arrayLength)
{
    Node* currentNode = head;
    int i;

    /* loop through each of the elements jump to the next node in
     * the list and copy it into the arry */
    for(i = 0; i < arrayLength; i++)
    {
        currentNode = currentNode->next;
        /* initialise each element in the array to a max word size of char */
        array[i] = (char*)malloc(MAX_WORD_SIZE*sizeof(char));
        /* using strncpy to store data within link list to the array
         * type cast is need as we are accessing a void* type */
        strncpy(array[i], (char*)(currentNode->data),MAX_WORD_SIZE);
    }
}

/* this is the function for freeing the word array 
 * ****Parameters****
 * array[] - pointer to an array
 * arrayLength - length of the incoming array
 * */
void freeWordArray(char* array[], int arrayLength)
{
    int i;

    /* loop through the entire the array and free each of the element */
    for(i=0; i < arrayLength; i++)
    {
        free(array[i]);
    }
}

/* free each element in the link list and free the head node of the list 
 * ****Parameters*****
 * Node* head - head node of the link list that about to be freed
 * ****ReturnVal****
 * void
 * */
void freeLinkList(Node* head)
{
    Node* current = head;
    /* a temporary node is used so that we dont lose the
 *      * link after freeing the current node */
    Node* tempNode;
    
    /* moving across the linkList */
    current = current->next;

    /* loop through the entire link list and free each node */
    while(current != NULL)
    {
        /* a tempnod is used such that we dont lose the position 
         * of current node */
        tempNode = current;
        current = current->next;
        /* free the content with tempNode */
        free(tempNode->data);
        /* free the tempnode itself*/
        free(tempNode);
    }

    /* free the head node of the link list */
    free(head);
    head = NULL;
}

