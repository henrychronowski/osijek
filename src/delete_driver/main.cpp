/**
 * @file main.cpp
 * @brief Driver code to demonstrate disk deletion library
 * 
 * @author Henry Chronowski
 * @assignment Final Project
 * @date 07/12/2020
 * @credits  
 * https://www.boost.org/doc/libs/1_63_0/doc/html/program_options.html
 * 
 **/


#include "diskDelete.h"
#include <iostream>

#include <boost/program_options.hpp>

using namespace boost::program_options;
  
int main(int argc, const char *argv[])
{
    int result;// = EXIT_SUCCESS;

    options_description desc{"Options"};
    desc.add_options()
      ("help,h", "Help screen")
      ("log,l", value<std::string>()->default_value("log.txt"), "Log output file")
      ("disk,d", value<std::string>()->default_value("/dev/sda"), "Disk file");

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help"))
      std::cout << desc << '\n';
    else
    {
        const char* logFile = vm["log"].as<std::string>().c_str();
        const char* disk = vm["disk"].as<std::string>().c_str();

        result = stat(disk);
        // result = !checkForRoot(disk);
        // result = wipeDisk(disk, 3);
    }

    
    return result;
}