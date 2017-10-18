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
	  int retFuncVal = 0;
		char userResponse;
	  /* error check and make sure there is a suggestion available */
	  if(suggestion != NULL)
		{
			  printf("Is the word '%s' meant to be '%s'? (y/n)", word, suggestion);

			  scanf("%c", &userResponse);
				switch(userResponse)
				{
						case 'y': case 'Y':
								retFuncVal = TRUE;
								break;
						case 'n': case 'N':
								retFuncVal = FALSE;
								break;
						default:
								printf("Invalide input. (y/n) or (Y/N)");
				}


		}
		else
		{
		    retFuncVal = -1;
				printf("No suggestion available for correction");
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
		if(suggestion != NULL)
		{
		    retFuncVal = TRUE;
		}
		else
		{
		    retFuncVal = -1;
				printf("No suggestion available for correction");
		}
		return retFuncVal;
}
