/*
Branden Lee and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017

FileIO class
contains file writing methods.
*/
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
	/** writes the string to the file path
	@pre file path exists
	@post writes to file
	@param str data to write
	@param filePath file path
	@return true on success false on failure */
	static bool strToFile (std::string str, std::string filePath);

	/** parses the file as a list
	@pre file path exists
	@post list is appended to with new data
	@param filePath file path
	@param listPtr list to fill
	@return true on success false on failure */
	static bool fileToList (std::string filePath, List<NodeMain*>* listPtr);
};
#endif