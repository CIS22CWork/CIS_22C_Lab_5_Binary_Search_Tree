#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <iostream>
#include <fstream>
#include "NodeMain.h"
#include "List.h"

class FileIO
{
public:
	static bool strToFile (std::string str, std::string filePath);
	static bool fileToList (std::string filePath, List<NodeMain*>* listPtr);
};
#endif