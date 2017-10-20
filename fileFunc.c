/**
 * UNIX & C Programming (COMP1000) Assignment
 * Author: Avery Au (14740248)
 * Description: contain all the prototypes for file handling functions
 * mainly for reading dictionary and user file, outputing autocorrected word
 * array back to the user file
 **/

#include "fileFunc.h"

/**
 * readFile - handles reading a provided file (dictionary or user file)
 *****Parameter*****
 * head - passing in a newly initialised linked List
 * fileName - string of input file name
 *****ReturnVal*****
 * fail file opening signal or linked list size
 **/
int readFile(Node* head, char* fileName)
{
    /* open input file in read mode */
    FILE* fptr = fopen(fileName, "r");
    int retFuncVal = 0, retfscanfVal = 0;
    /* each word is assigned with maximum length */
    char loadWord[MAX_WORD_SIZE];
    /* dynamically allocate memory for currentNode */
    Node* currentNode = (Node*)malloc(sizeof(Node));

    /* error checking if the file has been opened correct */
    if(fptr == NULL)
    {
        /* notify user if the file provided is invalid */
        printf("Unable to open %s", fileName);
        /* end readFile function and return -1 as error condition */
        retFuncVal = -1;
    }
    else
    {
        do
        {
            /* create a new linked list */
            currentNode = head;
            /* use fscanf to scanf file line by line and
             * return scanning condition */
            retfscanfVal = fscanf(fptr, "%s", loadWord);

            /* error check if fscanf does not return a non
             * end of file value '\0' */
            if(retfscanfVal != EOF)
            {
                /* allocate memory for the next node */
                currentNode->next = (Node*)malloc(sizeof(Node));
                /* move node to the next node position */
                currentNode = currentNode->next;
                /* make sure next node is ended correctly */
                currentNode->next = NULL;
                /* use strcpy to store the word into the node */
                strcpy(*((Word*)(currentNode->data))->wordString, loadWord);
                /* keep track of the link list size */
                retFuncVal++;
            }
        }
        /* loop until reaching the end of the input file */
        while(retfscanfVal != EOF);
        /* close the file as readFile function is complete */
        fclose(fptr);
    }
    /* passing out link list size or report error of reading file */
    return retFuncVal;
}

/**
 * writeFile - handles writing correct word array to user file
 * no need to preserve file formatting
 *****Parameter*****
 * correctWordArray - the product of autocorrected word array
 * arrayLength - indicate the size of the correctWordArray
 * fileName - the string containing the output file name
 *****ReturnVal*****
 * function status
 **/

int writeFile(char* correctWordArray[], int arrayLength, char* fileName)
{
    /* open file in write mode */
    FILE* fptr = fopen(fileName, "w");
    int i, retFuncVal = 0;

    /* error check to ensure file open correctly */
    if(fptr == NULL)
    {
        /* notify user the given file was unwritable */
        printf("Unable to write to %s",fileName);
        retFuncVal = -1;
    }
    else
    {
        /* go through each of the element within the correct wordArray
         * and write into the designated file destination */
        for(i=0; i < arrayLength; i++)
        {
            fprintf(fptr, "%s", correctWordArray[i]);
        }
        /* close the output file once the writing process is completed */
        fclose(fptr);
        retFuncVal = 1;
    }
    return retFuncVal;
}

/**
 * readSetting - handles reading configuration file into the setting struct
 *****Parameter*****
 * head - pointer of the head node of a link list
 *****ReturnVal*****
 * function status
 **/

int readSetting(Node* head)
{
    FILE* fptr = fopen("spellconf.txt","r");
    int retFuncVal = 0, retfscanfVal = 0, i;
    /* largest string name is 13(i.e.maxdifference) + NULL terminator = 14 */
    char name[14];
    /* largest string value is 13(i.e. spellconf.txt) + NULL terminator = 14 */
    char value[14];

    /* assign each of the array element to condition of dictfile,
     * maxdifference and autocorrect respectively*/
    int condition[3];

    /* initiate each condition as FALSE */
    for(i = 0; i<3; i++)
    {
        condition[i] = FALSE;
    }
    /* dynamically allocate memory for currentNode */
    Node* currentNode = NULL;
    currentNode = (Node*)malloc(sizeof(Node));

    if(fptr == NULL)
    {
        printf("Unalbe to write to spellconf.txt");
        retFuncVal = -1;
    }
    else
    {
        do
        {
            currentNode = head;
            retfscanfVal = fscanf(fptr, "%s = %s", name, value);
            if(retfscanfVal != EOF)
            {
                if(strcmp(name, "dictfile") == 0)
                {
                    condition[0] = TRUE;
                    strcpy(*((Setting*)(currentNode->data))->dictfile, value);
                    retFuncVal = 1;
                }
                else if(strcmp(name, "maxdifference") == 0)
                {
                    condition[1] = TRUE;

                    *((Setting*)(currentNode->data))->maxdifference = atoi(value);
                    if((*((Setting*)(currentNode->data))->maxdifference == 0) |
                      (*((Setting*)(currentNode->data))->maxdifference <= 0))
                    {
                        printf("maxdifference cannot be equal or less than 0");
                        printf("autocorrect is set to no as default");
                        strcpy(*((Setting*)(currentNode->data))->autocorrect, "FALSE");
                    }
                    retFuncVal = 1;
                }
                else if(strcmp(name, "autocorrect") == 0)
                {
                    condition[2] = TRUE;
                    if((strcmp(value, "yes") == 0) | (strcmp(value, "YES") == 0))
                    {
                        strcpy(*((Setting*)(currentNode->data))->autocorrect, "TRUE");
                        retFuncVal = 1;
                    }
                    else if((strcmp(value, "no") == 0) | (strcmp(value, "NO") == 0))
                    {
                        strcpy(*((Setting*)(currentNode->data))->autocorrect, "FALSE");
                    }
                    else
                    {
                        printf("Unknown value %s for autocorrect\n", value);
                        printf('autocorrect is set to no as default');
                        strcpy(*((Setting*)(currentNode->data))->autocorrect, "FALSE");
                        retFuncVal = 1;
                    }

                }
                else
                {
                    printf("Unkown variable '%s'in spellconf.txt", name);
                    retFuncVal = -1;
                }
            }
        }
        while(retfscanfVal != EOF);
        fclose(fptr);

        for(i = 0; i<3; i++)
        {
            if(condition[i] != TRUE)
            {
                char defaultName[14];
                switch(i)
                {
                    case 0:
                        strcpy(defaultName, "dictfile");
                        break;
                    case 1:
                        strcpy(defaultName, "maxdifference");
                        break;
                    case 2:
                        strcpy(defaultName, "autocorrect");
                        break;
                    default:
                        printf("unexpected entry");
                        break;
                }
                retFuncVal = -1;
                printf("Missing variable '%s' in spellconfig.\n", defaultName);

            }
        }


    }
    return retFuncVal;
}
