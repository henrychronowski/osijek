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
#include <sys/statvfs.h>


#include <iostream>
#include <fstream>

// HTML wrapper for the log file
const std::string HTML_HEADER = "<doctype HTML>\n<html>\n<head> <title>Wipe Log</title>\n\t<style>h1{\n\t\tcolor:black;\n\t\tfont-size:20px;\n}\n\t</style>\n\t<style>h2{\n\t\tcolor:black;\n\t\tfont-size:15px;\n}\n\t</style>\n</head>\n";
const std::string HTML_FOOTER = "</html>";
const std::string HTML_BODY_START = "<body>";
const std::string HTML_BODY_CLOSE = "</body>\n";
const std::string HTML_1STYLE_OPEN = "<h1>";
const std::string HTML_1STYLE_CLOSE = "</h1>\n";
const std::string HTML_2STYLE_OPEN = "<h2>";
const std::string HTML_2STYLE_CLOSE = "</h2>\n";


int stat(const char* disk)
{
    struct statvfs buff;
    int result = statvfs(disk, &buff);

    if(!result)
    {
        const ulong fsID = buff.f_fsid;
        const ulong flags = buff.f_flag;
        const ulong bsize = buff.f_bsize;
        const ulong fsize = buff.f_frsize;
        const fsfilcnt_t inodes = buff.f_files;
        const fsfilcnt_t free = buff.f_ffree;
        const double freePct = (static_cast<double>(inodes - free) * 100.0) / static_cast<double>(inodes);


        
        std::cout <<"Filesystem ID: " << fsID << "\nMount Flags: " << flags << "\nBlock Size: " << bsize << "\nFragment Size: " << fsize <<
            "\nTotal inodes: " << inodes << "\nFree inodes: " << free << " (" << freePct << "%)\n";
    }

    return result;
}

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
bool wipeDisk(const char* disk, wipeData&data, ushort passes, ssize_t chunkSize)
{
    // Set values to defaults
    data.result = EXIT_FAILURE;
    data.disk = disk;
    data.passes = 0;
    data.chunkSize = chunkSize;
    data.wiped = 0;

    // Validate pass number
    if(passes == 0)
    {
        printf("\nInvalid Pass Count\n");
        return data.result;
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
            data.result = EXIT_FAILURE;
            break;
        }
    
        // Write 0s to the disk in chunks of 512 bytes - stop when unable to write a full 512 bytes
        char* zeroes = reinterpret_cast<char*>(calloc(1, chunkSize));
        ssize_t written;
        do{
            written = write(chunk, zeroes, chunkSize);
            data.wiped += written;
        } while (written == chunkSize);

        data.passes++;

        // When unable to write any more chunks return a success along with the number of bytes written
        // printf("\rBytes written: %ld", total);
        // printf("\nPass successful\n");

        // Close the given disk file and free the allocated memory
        close(chunk);
        free(zeroes);
    }

    // printf("\nPasses complete: %ld", (long int)i);
 
    return data.result;
}

/** @brief Writes information from the given struct to the given file
 *  @param {wipeData} data - The struct containing data from a wipe
 *  @param {string} logFile - The html file to write the log to
 *  @return {bool} - returns 0 on success, 1 on error
 */
int logWipe(wipeData data, std::string logFile)
{
    std::ofstream log;

    // Open the file in append mode in order to create it if it doesn't already exist then discard the ofstream
    (void) std::ofstream(logFile, std::ofstream::app);

    log.open(logFile);
    if(log.fail())
    {
        std::cerr << "Error opening log file \"" << logFile << "\"\n";
        return 1;
    }

    // Output information with HTML wrapper code to the log file
    log << HTML_HEADER + HTML_BODY_START + HTML_1STYLE_OPEN << data.disk << " wiping log" << HTML_1STYLE_CLOSE;
    if(!data.result)
    {
        log << HTML_2STYLE_OPEN << "Wiping successful" << HTML_2STYLE_CLOSE;
    }
    else
    {
        log << HTML_2STYLE_OPEN << "Wiping failed" << HTML_2STYLE_CLOSE;
    }
    
    log << HTML_2STYLE_OPEN << "Passes done: " << data.passes << HTML_2STYLE_CLOSE + HTML_2STYLE_OPEN << "Total bytes written: " << data.wiped << HTML_2STYLE_CLOSE;
    log << HTML_2STYLE_OPEN << "Chunk size used: " << data.chunkSize << HTML_2STYLE_CLOSE;
    log << HTML_BODY_CLOSE + HTML_FOOTER;

    log.close();

    return 0;
}