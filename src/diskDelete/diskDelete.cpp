/**
 * @file letterCheck.cpp
 * @brief disk erasure library implementation
 * 
 * @author Henry Chronowski
 * @assignment Lab 12.1
 * @date 30/11/2020
 * @credits Lecture 12.1
 **/

#include "diskDelete.h"
#include <string.h>
 
/** @brief Returns the number of occurences of the first character in the following string
 */
int checkLetter(char* word)
{
    int ret = 0;
 
    char *target = word;
    int len = strlen(word);
    char *check = target + 1;
 
    for (int i = 0 ; i < len ; ++i, ++check)
    {
        if (*check == *target)
        {
            ret++;
        }
    }
 
    return ret;
}