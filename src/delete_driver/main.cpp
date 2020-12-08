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
    bool result;
    result = wipeDisk("/dev/sda");
    
    return result;
}