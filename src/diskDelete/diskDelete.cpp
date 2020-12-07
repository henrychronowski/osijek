/**
 * @file diskDelete.cpp
 * @brief disk erasure library implementation
 * 
 * @author Henry Chronowski
 * @assignment Final Project
 * @date 07/12/2020
 * @credits fdfs
 **/

#include "diskDelete.h"
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
 
/** @brief Returns the number of occurences of the first character in the following string
 */
bool wipeDisk(char* disk)
{
    // Open the given disk file
    int chunk = open(disk, O_WRONLY);
    
    // Write 0s to the disk in chunks of 512 bytes - stop when unable to write a full 512 bytes

    // When unable to write any more chunks return a success along with the number of bytes written

    // Close the given disk file
    close(chunk);
 
    return EXIT_SUCCESS;
}