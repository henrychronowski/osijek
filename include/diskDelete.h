/**
 * @file diskDelete.h
 * @brief Function declarations for disk deletion library
 * 
 * @author Henry Chronowski
 * @date 21/12/2020
 * @credits   
 **/

#ifndef DISKDELETE_H
#define DISKDELETE_H

#include <stdio.h>
#include <sys/types.h>
#include <string>

// HTML wrapper for the log file
const std::string HTML_HEADER = "<doctype HTML>\n<html>\n<head> <title>Wipe Log</title>\n\t<style>h1{\n\t\tcolor:black;\n\t\tfont-size:20px;\n}\n\t</style>\n\t<style>h2{\n\t\tcolor:black;\n\t\tfont-size:15px;\n}\n\t</style>\n</head>\n";
const std::string HTML_FOOTER = "</html>";
const std::string HTML_BODY_START = "<body>";
const std::string HTML_BODY_CLOSE = "</body>\n";
const std::string HTML_1STYLE_OPEN = "<h1>";
const std::string HTML_1STYLE_CLOSE = "</h1>\n";
const std::string HTML_2STYLE_OPEN = "<h2>";
const std::string HTML_2STYLE_CLOSE = "</h2>\n";

struct wipeData
{
    int result;
    std::string disk;
    unsigned long long wiped;
    ushort passes;
    ssize_t chunkSize;
    std::string user;
};

int statDisk(const char* disk);
int wipeDisk(const char* disk, wipeData&data, ushort passes = 1, ssize_t chunkSize = 512);
int logWipe(wipeData data, std::string logFile);

#endif