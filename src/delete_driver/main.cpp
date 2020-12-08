/**
 * @file main.cpp
 * @brief Driver code to demonstrate disk deletion library
 * 
 * @author Henry Chronowski
 * @assignment Final Project
 * @date 07/12/2020
 * @credits  
 * 
 **/


#include "diskDelete.h"
#include <iostream>
  
int main()
{
    const char* disk = "/dev/sda";
    bool result;
    checkForRoot(disk);
    result = wipeDisk(disk, 512);
    return result;
}