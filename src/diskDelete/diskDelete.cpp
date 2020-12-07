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
bool wipeDisk(char* disk, ssize_t chunkSize = 512)
{
    // Open the given disk file
    int chunk = open(disk, O_WRONLY);

    // If open returns < 0 this signifies an error opening the disk file
    if(chunk < 0)
    {
        fprintf(stderr, "Error opening disk file\n");
        return EXIT_FAILURE;
    }
    
    // Write 0s to the disk in chunks of 512 bytes - stop when unable to write a full 512 bytes
    char* zeroes = reinterpret_cast<char*>(calloc(1, chunkSize));
    ssize_t written, total = 0;
    do{
        written = write(chunk, zeroes, chunkSize);
        total += written;
    } while (written == chunkSize);

    // When unable to write any more chunks return a success along with the number of bytes written
    printf("\rBytes written: %chunk", total);
    printf("\nWiping successful\n");

    // Close the given disk file and free the allocated memory
    close(chunk);
    free(zeroes);
 
    return EXIT_SUCCESS;
}