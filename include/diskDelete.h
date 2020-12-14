/**
 * @file diskDelete.h
 * @brief Function declarations for disk deletion library
 * 
 * @author Henry Chronowski
 * @assignment Final Project
 * @date 13/12/2020
 * @credits   
 **/

#ifndef DISKDELETE_H
#define DISKDELETE_H

#include <stdio.h>
#include <sys/types.h>
#include <string>

struct wipeData
{
    int result;
    std::string disk;
    unsigned long long wiped;
    ushort passes;
    ssize_t chunkSize;
};

int statDisk(const char* disk);
int wipeDisk(const char* disk, wipeData&data, ushort passes = 1, ssize_t chunkSize = 512);
int logWipe(wipeData data, std::string logFile);

#endif