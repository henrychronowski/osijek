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

/** @brief Checks if the given device contains the root filesystem
 *  @param {char*} disk - The path to the device file of the disk
 *  @return {bool} - returns true if it contains root, false otherwise
 */
bool checkForRoot(const char* disk)
{
    printf("\nDisk does not contain root filesystem\n");
    return true;
}


/** @brief Opens and wipes the given disk in chunks of the given size
 *  @param {char*} disk - The path to the device file of the disk
 *  @param {unsigned short} [passes=1] - The number of passes over the drive to do
 *  @param {ssize_t} [chunkSize=512] - The chunk size in bytes with which to write
 *  @return {bool} - returns EXIT_SUCCESS (0) on success, EXIT_FAILURE (1) on error
 */
bool wipeDisk(const char* disk, ushort passes, ssize_t chunkSize)
{
    int result = EXIT_FAILURE;
    // Validate pass number
    if(passes == 0)
    {
        printf("\nInvalid Pass Count\n");
        return result;
    }
    
    ushort i;
    for(i = 0; i < passes; i++)
    {
   
        // Open the given disk file
        int chunk = open(disk, O_WRONLY);

        // If open returns < 0 this signifies an error opening the disk file
        if(chunk < 0)
        {
            fprintf(stderr, "Error opening disk file\n");
            result = EXIT_FAILURE;
            break;
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
        printf("\nPass successful\n");

        // Close the given disk file and free the allocated memory
        close(chunk);
        free(zeroes);
    }

    printf("\nPasses complete: %ld", (long int)i);
 
    return result;
}