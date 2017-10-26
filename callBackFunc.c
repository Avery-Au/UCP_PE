/**
 * UNIX & C Programming (COMP1000) Assignment
 * Author: Avery Au (14740248)
 * Description: contain the functions for call back decision
 **/

 #include "callBackFunc.h"

/**
 * userDecision - ask user for decision as whether the suggested word
 * is appropriate
 *****Parameter*****
 * word - pointer to the misspelt word
 * suggestion - pointer to the suggestion
 *****ReturnVal*****
 * TRUE - correction to be accepted
 *  FALSE - correction to be rejected
 * -1 - no suggestion provided
 **/
int userDecision(char* word, char* suggestion)
{
    int retFuncVal = 0, status = FALSE;
    char userResponse;
    /* error check and make sure there is a suggestion available */
    if(suggestion != NULL)
    {
        printf("\nIs the word '%s' meant to be '%s'? (y/n)\n", word, suggestion);
        while(status == FALSE)
        {
            char flush;
            scanf("%c", &userResponse);
            /* intended to flush out dangeling characters from input buffer
             * using getchar to remove it all 
	     * reference : https://stackoverflow.com/questions/7898215/how-to-clear-input-buffer-in-c
	     **/
            while((flush=getchar()) != '\n' && flush != EOF)
            {
            }
            /* accept both upper and lowercase response from user */
   	    switch(userResponse)
	    {
                case 'y': case 'Y':
	            retFuncVal = TRUE;
                    status = TRUE;
	        break;
	        case 'n': case 'N':
	            retFuncVal = FALSE;
                    status = TRUE;
	        break;
	        default:
	            printf("Invalid input. (y/n) or (Y/N)\n");
	    }
        }    
    }
    else
    {
        /* if there is no suggestion available from the given library,
	 * the program will prompt no suggestion available */
        retFuncVal = -1;
	printf("\nNo suggestion available for this word '%s'\n", word);
    }
    return retFuncVal;
}

/**
 * autocorrect - automatically replace a suggestion to a misspelt word
 *****Parameter*****
 * word - pointer to a misspelt word
 * suggestion - pointer to a suggestion
 *****ReturnVal*****
 * TRUE - correction accepted
 * -1 - no suggestion provided
 **/
int autoCorrect(char* word, char* suggestion)
{
    int retFuncVal = 0;
    /* as this is autocorrect, the program will check whether the word from user file exist in dictionary file
     * if not it will prompt the no suggestion available message */
    if(suggestion != NULL)
    {
        retFuncVal = TRUE;
    }
    else
    {
        retFuncVal = -1;
	printf("\nNo suggestion available for this word '%s'\n", word);
    }
    return retFuncVal;
}
