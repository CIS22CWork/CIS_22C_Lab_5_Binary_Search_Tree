#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <iostream>
#include <fstream>

class FileIO
{
public:
	static bool strToFile (std::string str, std::string filePath);
};
#endif