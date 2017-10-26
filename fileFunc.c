/**
 * * UNIX & C Programming (COMP1000) Assignment
 * * Author: Avery Au (14740248)
 * * Description: contain all the prototypes for file handling functions
 * * mainly for reading dictionary and user file, outputing autocorrected word
 * * array back to the user file
 * **/

#include "fileFunc.h"

/**
 * stringFilter - function to handle strings read from files format 
 * filter out all the non alphabet except hyphen
 * ****Parameters****
 * stringInput - loadWord from readFile function
 * ****ReturnVal****
 * void
 * */
void stringFilter(char* stringInput)
{
    int i=0;
    /* filter out all the non alphabet character except hyphen */
    while(stringInput[i] != '\0')
    {
        if(!((stringInput[i] >= 65 && stringInput[i] <= 90)||(stringInput[i] >= 97 && stringInput[i] <= 122)||(stringInput[i] == 45)))
        {
            stringInput[i] = 97;
        }
        /* convert string from uppercase to lowercase so that our word comparsion function properly */
        if(stringInput[i] >= 65 && stringInput[i] <= 90)
        {
            stringInput[i] += 32;
        }
        i++;
    }   
}
/**
 * * readFile - handles reading a provided file (dictionary or user file)
 * *****Parameter*****
 * * head - passing in a newly initialised linked List
 * * fileName - string of input file name
 * *****ReturnVal*****
 * * fail file opening signal or linked list size
 * **/
int readFile(Node* head, char* fileName)
{
    /* open input file in read mode */
    FILE* fptr = fopen(fileName, "r");
    int retFuncVal = 0, retfscanfVal =0;
    
    /* error checking if the file has been opened correct */
    if(fptr == NULL)
    {
        /* notify user if the file provided is invalid */
        printf("Unable to open %s\n", fileName);
        /* end readFile function and return -1 as error condition */
        retFuncVal = -1;
    }
    else
    {
        /* Initialise current and previous node */
        Node* currentNode;
        Node* previousNode;
        /* initiliase laod word as a char* with NULL value */
        char* loadWord = NULL;
        /* do while loop to handle scaning each word from the user file and 
         * and utilise the insertNewNode function to store the string in a struct
         */     
        do
        {   
            /* dynamically allocate the max word size to loadWord */
            loadWord = (char*)malloc(MAX_WORD_SIZE * sizeof(char));
            /* fscanf to read the word string */
            retfscanfVal = fscanf(fptr,"%s",loadWord);           
	    
            /* make sure fscanf didnt reach the end of file */  
            if(retfscanfVal != EOF)
            {
                #ifdef DEBUG
                printf("%s ",loadWord);
                #endif
                /* calling the string filter function */
                stringFilter(loadWord);
                printf("%s ",loadWord);
                #ifdef DEBUG
                printf("teset1");         
                printf("address of head %p\n",(void*)head);
                printf("address of next %p\n",(void*)head->next);
                printf("address of loadWord %p\n", loadWord);
                printf("value of loadWord %s\n", loadWord);
                #endif
                /* check if its the first node to be made */
                if(head == NULL)
                {
                    head = insertNewNode(head, loadWord);
                    /* check if data insertion was successful */
                    if(head->data != NULL)
                    {
                        /* set the number of nodes return to 1 */
                        retFuncVal = 1;
                    }
                    else
                    {
                        /* if the loading data failed free the head node */
                        printf("error reading data into first node\n");
                        free(head);
                        head = NULL;
                    }
                }
                else
	        {
                    /*case for node insertion are not the first node */ 
                    currentNode = insertNewNode(head, loadWord);
                    /* check if data insertion was successful */
                    if(currentNode->data != NULL)
                    {
                        /* increment the return value to show the array size for use later on */
                        retFuncVal ++;
                        
                    }
                    else
                    {
                        /* free the node if reading data failed */
                        printf("error reading data into node\n");
                        previousNode->next = NULL;
                        free(currentNode);
                    }
                }
            }
             
            /* move the previous node along the list */
           
            previousNode = currentNode;
            free(loadWord);
        }
        while(retfscanfVal != EOF);
                
    }
    if(fptr != NULL)
    {
        fclose(fptr);
    }
    /* passing out link list size or report error of reading file */
    return retFuncVal;
}

/**
 * writeFile - handles writing correct word array to user file
 * no need to preserve file formatting
 * ****Parameter****
 * correctWordArray - the product of autocorrected word array
 * arrayLength - indicate the size of the correctWordArray
 * fileName - the string containing the output file name
 * ****ReturnVal****
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
 *          * and write into the designated file destination */
        for(i=0; i < arrayLength; i++)
        {
            fprintf(fptr, "%s ", correctWordArray[i]);
        }
        /* close the output file once the writing process is completed */
        fclose(fptr);
        retFuncVal = 1;
    }
    return retFuncVal;
}

/**
 * readSetting - handles reading configuration file into the setting struct
 * ****Parameter****
 * head - pointer of the head node of a link list
 * ****ReturnVa*****
 * function status
 **/

int readSetting(Setting* settingHead)
{
    FILE* fptr = fopen(".spellconf","r");
    /* retFuncVal 0 ->everything run smoothly, -1 -> error occured */
    /* retCorrectVal ->True or False return to autocorrect in the setting head struct */
    /* ret fscanfVal -> return value to check whether the file reading pointer has reached the end of file */
    int retFuncVal = 0, retCorrectVal = 0, i, retfscanfVal = 0;
    /* largest string name is 13(i.e.maxdifference) + NULL terminator = 14 */
    char name[14];
    /* largest string value is 29 + NULL terminator = 30 */
    char value[30];

    /* assign each of the array element to condition of dictfile,
     * maxdifference and autocorrect respectively*/
    int condition[3];

    /* initiate each condition as FALSE
     * [0] = dictfile
     * [1] = maxdifference
     * [2] = autocorrect
     **/
    for(i = 0; i<3; i++)
    {
        condition[i] = FALSE;
    }
    /* error checking whether configuration file is opened correctly */
    if(fptr == NULL)
    {
        printf("\nUnalbe to read .spellconf\n");
        retFuncVal = -1;
    }
    else
    {
        /* do - while loop to read the entire file */
        do
        {
            /* using fscanf to read the configure file and place it in variable value */
            retfscanfVal = fscanf(fptr, "%s = %29s", name, value);
            /* check whether fscanf reached the end of file */
            if(retfscanfVal != EOF)
            {
                /* input the value to dictfile struct if the name variable is dictfile */
                if(strcmp(name, "dictfile")== 0 )
                {
                    /* allocate memory to the dictfile pointer */
                    settingHead->dictfile = (char*)malloc(MAX_WORD_SIZE*sizeof(char));
                    condition[0] = TRUE;
                    /* strncpy the value into the dictfile struct */
                    strncpy(settingHead->dictfile, value,MAX_WORD_SIZE);
                    retFuncVal = 1;
                }   
                
                    /* similar process to dictfile but no need memory allcoation as it is just an int */
                else if(strcmp(name, "maxdifference") == 0)                                     {
                    condition[1] = TRUE;
                    settingHead->maxdifference = atoi(value);
                    retFuncVal = 1;
                    /* error check as maxdifference cannot be equal to 0 or less than 1 */
                    if((settingHead->maxdifference == 0)|(settingHead->maxdifference < 0))
                    {
                        printf("maxdifference cannot be equal or less than 0\n");
                        printf("autocorrect is set to no as default\n");
                        retCorrectVal = FALSE;
                        settingHead->autocorrect = retCorrectVal;
                        condition[1] = FALSE;
                    }
                }

                /* similar to previous process storing a True or false value */
                else if(strcmp(name,"autocorrect") == 0)      
                {             
                    /* accomodate upper and lower case for both no and yes input */
                    if((strcmp(value, "yes") == 0) | (strcmp(value, "YES") == 0))
                    {
                        condition[2] = TRUE;
                        retCorrectVal = TRUE;
                    }
                    /* doing the same for no value */
                    else if((strcmp(value, "no") == 0) | (strcmp(value, "NO") == 0))
                    {
                        condition[2] = TRUE;
                        retCorrectVal = FALSE;
                    }
                    /* prompt user the value provided is not recognisable by the program */
                    else
                    {  
                        printf("Unknown value %s for autocorrect\n", value);
                        printf("autocorrect is set to no as default\n");
                        condition[2] = FALSE;
                        retCorrectVal = FALSE;
                    }
                    settingHead->autocorrect = retCorrectVal;
                    retFuncVal = 1;
                }
                else
                {
                    printf("This name '%s' is not recognisable by the program\n",name);
                }
            }
        }
        while(retfscanfVal != EOF);
        /* closing the user file as we finish using it */
        fclose(fptr);

    
    
        /* error message and tell user the default value the program is expecting */
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
                printf("Missing variable for '%s' in .spellconfig\n", defaultName);
            }
        }
        /* check whether dictfile is initialise such that we dont over freeing */
        if(condition[0] != TRUE)
        {
            free(settingHead);
            settingHead = NULL;
        }
        else if((condition[1] != TRUE) || (condition[2] != TRUE))
        {
            /* freeing the link list settingHead* pointer to dictfile */
            free(settingHead->dictfile);
            /* make sure the free process is completed */
            settingHead->dictfile = NULL;
            /* freeing the head node */
            free(settingHead);
            settingHead = NULL;
        }
    } 
    return retFuncVal;
}

