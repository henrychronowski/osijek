/**
 * @file diskDelete.h
 * @brief Function declarations for disk deletion library
 * 
 * @author Henry Chronowski
 * @assignment Final Project
 * @date 07/12/2020
 * @credits   
 **/

#ifndef DISKDELETE_H
#define DISKDELETE_H

#include <stdio.h>
#include <sys/types.h>          /// TODO: determine if this is necessary

//typedef unsigned short ushort;

bool checkForRoot(const char* disk);
bool wipeDisk(const char* disk, ushort passes = 1, ssize_t chunkSize = 512);
#endif