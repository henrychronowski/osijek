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

bool checkForRoot(const char* disk);
bool wipeDisk(const char* disk, ssize_t chunkSize = 512);
#endif