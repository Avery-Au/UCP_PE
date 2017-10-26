/**
 * * UNIX & C Programming (COMP1000) Assignment
 * * Author: Avery Au (14740248)
 * * Description: contain main functions
 * * contain program underlying the required spellchecking functionality from
 * * assignment sheet
 * **/


#include "spellChecker.h"

/**
 * * spellchecker main function
 * *****Parameters*****
 * * argc - number of parameters passed to the program + 1
 * * argv - parameter string length passed into the program
 * *****ReturnVal*****
 * * 1 when an error occurs, or 0 for successful completion
 * **/
int main(int argc, char* argv[])
{
    /* 0 = normal, everything else = failed */
    int retFuncVal = 0;
    if(argc != 2)
    {
        /* error prompt for correct function usage */
        printf("\nMissing user file input in first arguement\n");
        printf("Usage: %s [Input File Name]\n", argv[0]);
        retFuncVal = -1;
    }
    else
    {
        /* dynamically allocate memory to head node for reading setting file */
        Setting* settingHead = (Setting*)malloc(sizeof(Setting));

        if(readSetting(settingHead) == 1)
        {
            /* initiate char arrays for storing dictionary words and user file
             * word, char array for storing user file name, int varaible for
             *  storing dictionary lsit size and user file list size */
            char** dictionaryArray;
            char** userFileArray;
            char* userFileName;
            int dictionaryCount;
            int userFileCount;

            /* dynamically allocate memory for the list head node */
            Node* dictionaryHead = (Node*)malloc(sizeof(Node));
            Node* userFileHead = (Node*)malloc(sizeof(Node));
           
            /* make sure the next pointers are pointing at NULL */ 
            dictionaryHead->next = NULL;
            userFileHead->next = NULL;
 
            /* display setting file information read to user */
            printf("================================\n");
            printf("Display of reading setting file\n");
            printf("dictionary = %s\n", settingHead->dictfile);
            printf("maxdifference = %d\n", settingHead->maxdifference);
            printf("autocorrect = %d\n", settingHead->autocorrect);
            printf("================================\n");
           
        
            /* dynamically allocate memory for the user file name */
            userFileName = (char*)malloc(30*sizeof(char));
            /* copy user command into the variable for storing userfile name */
            strcpy(userFileName, argv[1]);
            /* call readFile function to read the input words from dictionary file into a dictionary link list */  
            dictionaryCount = readFile(dictionaryHead, settingHead->dictfile);
            
            /* ensure the readFile proceed smoothly */
            if(dictionaryCount != -1)
            {
                /* display the user total number of words loaded from dictfile */
                printf("\n=========================\n");
                printf("Loaded dictionary file successfully!!\n");
                printf("\nLoaded %d words from %s\n", dictionaryCount,
                    settingHead->dictfile);
                printf("\n=========================\n");
                /* memory allocation for dictionary Array */
                dictionaryArray = (char**)malloc(dictionaryCount*
                    sizeof(char*));
                /* call the function to put link list into array */
                linkListToArray(dictionaryHead, dictionaryArray,
                    dictionaryCount);

                /* free up memory for the link list as we are done with it */
                freeLinkList(dictionaryHead);
                dictionaryHead = NULL;
                
                /* call function readFile to read user file into link list */
                userFileCount = readFile(userFileHead, userFileName);
                if(userFileCount != -1)
                {
                    /* initialise the callback function action */
                    ActionFunc action;
                    /* let user know how many words have been loaded into the list */
                    printf("\n=========================\n");
                    printf("Loaded user file successfully!!\n");
                    printf("\nLoaded %d words from %s\n", userFileCount,
                        userFileName);
                    printf("\n=========================\n");
                    /* memory allocation for array to store user file information*/ 
                    userFileArray = (char**)malloc(userFileCount*
                        sizeof(char*));
                    /* call function linkListToArray to convert link list into the user array */
                    linkListToArray(userFileHead, userFileArray,
                        userFileCount);
                    /* free the linklist once the process is completed */
                    freeLinkList(userFileHead);
                    userFileHead = NULL;
                    /* depending on the autocorrect value in setting file choose the correct mode for the callback action function */
                    if(settingHead->autocorrect == TRUE)
                    {
                        action = &autoCorrect;
                    }
                    else
                    {
                        action = &userDecision;
                    }

                    /* the action spell checking operation */
                    check(userFileArray, userFileCount, dictionaryArray,
                        dictionaryCount, settingHead->maxdifference,
                        action);

                    /* as we now have the corrected word user array, we will
                     * required to clear the file before writing into it */
                    remove(userFileName);

                    /* writing the corrected word array into the userFile */
                    writeFile(userFileArray, userFileCount, userFileName);
                    printf("File correction completed\n");
                    /* as the writing function has completed the user word array is no longer in use */
                    /* free individual word stored in the user array */
                    freeWordArray(userFileArray, userFileCount);
                    /* free the user array itself */
                    free(userFileArray);
                    /* make sure everything has been freed */
                    userFileArray = NULL;
                    retFuncVal = 0;
                }
                else
                {
                    printf("Error occured during loading [%s]\n", userFileName);
                    retFuncVal = -1;
                    free(userFileHead);
                }
                /* similar process to as the user array */
                freeWordArray(dictionaryArray, dictionaryCount);
                /* free individual word stored in the array */
                free(dictionaryArray);
                /* free array itself */
                free(userFileName);
                /* make sure it is freed */
                dictionaryArray = NULL;
            }
            else
            {
                printf("Error occured during loading [%s]\n",
                    settingHead->dictfile);
                printf("please check whether you have entered a valid dictionary file name\n");
                retFuncVal = -1;
                free(userFileName);
                free(userFileHead);
                userFileHead = NULL;
                free(dictionaryHead);
                dictionaryHead = NULL;
            }
            /* freeing the link list settingHead* pointer to dictfile */
            free(settingHead->dictfile);
            /* make sure the free process is completed */
            settingHead->dictfile = NULL;
            /* freeing the head node */
            free(settingHead);
            settingHead = NULL;
        }
        else
        {
            printf("Error occured during readSetting Function\n");
            retFuncVal = -1;
            free(settingHead);
            settingHead = NULL;
            
        }
    }
    return retFuncVal;
}

