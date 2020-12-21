# osijek
This repository contains a shared object library and associated driver code that is built to contain disk erasure functionality as well as logging of the erasing process. This was originally developed as the final project for CSI-230 at Champlain College and is under current development for use at the college's help desk.

## Dependencies
The driver code for this project utilizes the [Boost Program Options library](https://www.boost.org/doc/libs/1_63_0/doc/html/program_options.html). Having this library installed in your system and added to the include directories is necessary to build the driver code.

## Build Instructions
Utilizing the Makefile included in the repository, a simple 'make' command in the terminal will build the project provided the dependencies are installed, and then the binary driver will be built in the bin/ directory.

## Usage Instructions
Once the project is built the binary may be run using any of the flags detailed below in any combination. The program must be run with sudo privildges as it is necessary to write to the disk. The program will first output information about the given disk, provided it can be opened, and then asks the user if they wish to continue. If they continue, the program wipes the disk by writing zeroes to it for a specified number of passes (default 1) in a specified block size (default 512 bytes). Modern disks often use a block size of 4096 bytes but older disks use a block size of 512 bytes, which will also work on modern disks, which is why it is the default. The disk's block size is included in the initial information output so if the user would like to change the block size in response to learning the block size of the disk they may choose to quit and restart the wipe with that block size.

During the wipe the program will be unresponsive. This process could take any amount of time up to several hours depending on how large the disk is and a multitude of other factors. There is no output while the disk is wiping in order to maximize the speed of the wipe. Once the disk is completed wiping a message stating that a log has been saved to the specified log file (default log.html) will be printed to the console and the program will terminate. The log is by default saved to the project directory (where the program is being run from), and contains information about the disk wiped and the wiping process.

Returns a 0 on success, 1 on error, and 2 on user abort.

### Switches:
    -h [ --help ]                 Help screen

    -u [ --user ]                 Technician identification
  
    -l [ --log ] arg (=log.html)  Log output file
  
    -d [ --disk ] arg (=/dev/sda) Disk file
    
    -p [ --passes ] arg (=1)      Number of passes
  
    -c [ --chunk ] arg (=512)     Chunk size
