/**
 * UNIX & C Programming (COMP1000) Assignment
 * Author: Avery Au (14740248)
 * Description: contain main functions
 * contain program underlying the required spellchecking functionality from
 * assignment sheet
 **/


#include "spellChecker.h"
#define DEBUG
/**
 * spellchecker main function
 *****Parameters*****
 * argc - number of parameters passed to the program + 1
 * argv - parameter string length passed into the program
 *****ReturnVal*****
 * 1 when an error occurs, or 0 for successful completion
 **/
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        /* error prompt for correct function usage */
        printf("Usage: ./%s [Input File Name]\n", argv[0]);
    }
    else
    {
        /* dynamically allocate memory to head node for reading setting file */
        Node* settingHead = (Node*)malloc(sizeof(Node));

        if(readSetting(settingHead) == 1)
        {
            #ifdef DEBUG
                printf("Display of reading setting file\n");
                printf("dictionary = %s\n", ((Setting*)(settingHead->data))->dictfile);
                printf("maxdifference = %d\n", ((Setting*)(settingHead->data))->maxdifference);
                printf("autocorrect = %d\n", ((Setting*)(settingHead->data))->autocorrect);
            #endif
            /* initiate char arrays for storing dictionary words and user file
             * word, char array for storing user file name, int varaible for
             * storing dictionary lsit size and user file list size */
            char** dictionaryArray;
            char** userFileArray;
            char* userFileName;
            int dictionaryCount;
            int userFileCount;

            /* dynamically allocate memory for the list head node */
            Node* dictionaryHead = (Node*)malloc(sizeof(Node));
            Node* userFileHead = (Node*)malloc(sizeof(Node));

            /* dynamically allocate memory for the user file name */
            userFileName = (char*)malloc(30*sizeof(char));
            /* copy user command into the variable for storing userfile name */
            strcpy(userFileName, argv[1]);

            dictionaryCount = readFile(dictionaryHead, ((Setting*)(settingHead->data))->dictfile);

            if(dictionaryCount != -1)
            {
                #ifdef DEBUG
                printf("Loaded %d words from %s\n", dictionaryCount,
                    ((Setting*)(settingHead->data))->dictfile);
                #endif

                dictionaryArray = (char**)malloc(dictionaryCount*
                    sizeof(char*));
                linkListToArray(dictionaryHead, dictionaryArray,
                    dictionaryCount);

                /* free up memory for the link list as we are done with it */
                freeLinkList(dictionaryHead);
                dictionaryHead = NULL;

                userFileCount = readFile(userFileHead, userFileName);
                if(userFileCount != -1)
                {
                    ActionFunc action;
                    #ifdef DEBUG
                    printf("Loaded %d words from %s\n", userFileCount,
                        userFileName);
                    #endif

                    userFileArray = (char**)malloc(userFileCount*
                        sizeof(char*));
                    linkListToArray(userFileHead, userFileArray,
                        userFileCount);

                    freeLinkList(userFileHead);
                    userFileHead = NULL;

                    if(((Setting*)(settingHead->data))->autocorrect == TRUE)
                    {
                        action = &autoCorrect;
                    }
                    else
                    {
                        action = &userDecision;
                    }

                    /* the action spell checking operation */
                    check(userFileArray, userFileCount, dictionaryArray,
                        dictionaryCount, ((Setting*)(settingHead->data))->maxdifference,
                        action);

                    /* as we now have the corrected word user array, we will
                    required to clear the file before writing into it */
                    remove(userFileName);

                    /* writing the corrected word array into the userFile */
                    writeFile(userFileArray, userFileCount, userFileName);

                    freeWordArray(userFileArray, userFileCount);
                    free(userFileArray);
                    userFileArray = NULL;
                }
                else
                {
                    printf("Error occred during loading [%s]", userFileName);
                }
                freeWordArray(dictionaryArray, dictionaryCount);
                free(dictionaryArray);
                dictionaryArray = NULL;
            }
            else
            {
                printf("Error occured during loading [%s]",
                    ((Setting*)(settingHead->data))->dictfile);
            }
            freeLinkList(settingHead);
            settingHead = NULL;
        }
        else
        {
            printf("Error occured during readSetting Function");
        }
    }
    return 0;
}
