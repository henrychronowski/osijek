/**
 * @file main.cpp
 * @brief Driver code to demonstrate disk deletion library
 * @return 0 on success, 1 on error, 2 on user abort
 * 
 * @author Henry Chronowski
 * @date 21/12/2020
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
    int result = EXIT_FAILURE;

    options_description desc{"Options"};
    desc.add_options()
      ("help,h", "Help screen")
      ("user,u", value<std::string>()->required(), "Name of operator")
      ("log,l", value<std::string>()->default_value("log.html"), "Log output file")
      ("disk,d", value<std::string>()->default_value("/dev/sda"), "Disk file")
      ("passes,p", value<uint>()->default_value(1), "Number of passes")
      ("chunk,c", value<size_t>()->default_value(512), "Chunk size");

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help"))
    {
      std::cout << desc << '\n';
      std::cout << "Returns a 0 on success, 1 on error, and 2 on user abort\n";
      return EXIT_FAILURE + 1;
    }
    else
    {
        const char* logFile = vm["log"].as<std::string>().c_str();
        const char* disk = vm["disk"].as<std::string>().c_str();
        const uint passes = vm["passes"].as<uint>();
        const ssize_t chunkSize = static_cast<ssize_t>(vm["chunk"].as<size_t>());

        result = statDisk(disk);
        if(result != 1)
        {
          char c;
          std::cout << "Continue with wipe of " << disk << "? (Y/N) ";
          std::cin >> c;
          if(toupper(c) != 'Y')
            return EXIT_FAILURE + 1;
          
          // wipeData data;
          // result = wipeDisk(disk, data, passes, chunkSize);
          // logWipe(data, logFile);
        }
    }

    
    return result;
}