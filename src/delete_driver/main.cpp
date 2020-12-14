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
      ("log,l", value<std::string>()->default_value("log.html"), "Log output file")
      ("disk,d", value<std::string>()->default_value("/dev/sda"), "Disk file")
      ("passes,p", value<uint>()->default_value(1), "Number of passes")
      ("chunk,c", value<size_t>()->default_value(512), "Chunk size");

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help"))
      std::cout << desc << '\n';
    else
    {
        const char* logFile = vm["log"].as<std::string>().c_str();
        const char* disk = vm["disk"].as<std::string>().c_str();
        const uint passes = vm["passes"].as<uint>();
        const ssize_t chunkSize = static_cast<ssize_t>(vm["chunk"].as<size_t>());

        result = stat(disk);
        if(result != 1)
        {
          char c;
          std::cout << "Continue with wipe of " << disk << "? (Y/N) ";
          std::cin >> c;
          if(toupper(c) != 'Y')
            return EXIT_FAILURE + 1;
          
          wipeData data;
          result = wipeDisk(disk, data, passes, chunkSize);
          logWipe(data, logFile);
        }
    }

    
    return result;
}