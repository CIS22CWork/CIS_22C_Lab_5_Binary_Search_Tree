/*
Branden Lee and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

#ifndef NODE_MAIN_H
#define NODE_MAIN_H

#include <string>
#include <sstream>

/**
@class NodeMain
The main node to store name and birthday data
*/

class NodeMain
{
private:
	std::string name; //first last
	std::string birthday; //YYYY-MM-DD
public:
	NodeMain ();
	NodeMain (std::string nameFirstObj, std::string nameLastObj, std::string birthdayObj);
	~NodeMain ();
	std::string getName ();
	std::string getBirthday ();
};
#endif