/**
 * @file diskDelete.cpp
 * @brief disk erasure library implementation
 * 
 * @author Henry Chronowski
 * @assignment Final Project
 * @date 07/12/2020
 * @credits https://en.cppreference.com/w/cpp/language/explicit_cast
 * 
 **/

#include "diskDelete.h"
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <filesystem>
 



/** @brief Opens and wipes the given disk in chunks of the given size
 *  @param {char*} disk - The path to the device file of the disk
 *  @param {ssize_t} [chunkSize=512] - The chunk size in bytes with which to write
 *  @return {bool} - returns true/1 on success, false/0 on error
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
    printf("\rBytes written: %ld", total);
    printf("\nWiping successful\n");

    // Close the given disk file and free the allocated memory
    close(chunk);
    free(zeroes);
 
    return EXIT_SUCCESS;
}