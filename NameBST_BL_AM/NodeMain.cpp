/*
Branden Lee and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017

Node Main
*/

#include "NodeMain.h"

//******************************************************
// Default Constructor        
//******************************************************
NodeMain::NodeMain ()
{
	name = "FIRST LAST";
	birthday = "YYYY-MM-DD";
}

NodeMain::NodeMain (std::string nameFirstObj, std::string nameLastObj, std::string birthdayObj)
{
	std::string nameObj;
	std::stringstream nameSS;
	nameSS << nameFirstObj << " " << nameLastObj;
	name = nameSS.str ();
	birthday = birthdayObj;
}

//******************************************************
// Destructor          
//******************************************************
NodeMain::~NodeMain ()
{
}

std::string NodeMain::getName ()
{
	return name;
}
std::string NodeMain::getBirthday ()
{
	return birthday;
}