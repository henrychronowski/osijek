/**
 * @file main.cpp
 * @brief Driver code for palindrome library
 * 
 * @author Henry Chronowski
 * @assignment Lab 12.1
 * @date 29/11/2020
 * @credits Lecture 12.1
 * https://www.boost.org/doc/libs/1_71_0/doc/html/chrono.html
 * https://www.boost.org/doc/libs/1_71_0/doc/html/program_options.html
 * 
 **/


//#include "pal.h"
#include "letterCheck.h"
#include <iostream>
 
using namespace std;
 
int main()
{
    while (1)
    {
        char buffer[64] = {0};
        cin.getline(buffer, 63);
 
        // if (isPalindrome(buffer))
        // {
        //     cout << "Word is a palindrome" << endl;
        // }
        // else
        // {
        //     cout << "Word is not a palindrome" << endl;
        // }

        cout << "Char " << buffer[0] << " occurs " << checkLetter(buffer) << " times.\n";
    }
 
    return 0;
}