/*
Branden Lee and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017

SupportBST class
contains methods to assist BST construction
*/

#include "SupportBST.h"
/* Writes a string to a file with group information headers
@pre None
@post Creates or overwrites file to filePath with content str
@param str contents of file
@param filePath file to write to
@return true on success and false on failure
*/
bool SupportBST::nameInsert (List<NodeMain*>* list, BST<std::string>* BST)
{
	bool flag = false;
	int n = list->size ();
	for (int i =0;i<n;i++)
	{
		BST->add ((*list)[i]->getName());
	}
	return flag;
}

bool SupportBST::birthdayInsert (List<NodeMain*>* list, BST<std::string>* BST)
{
	bool flag = false;
	int n = list->size ();
	for (int i = 0; i<n; i++)
	{
		BST->add ((*list)[i]->getBirthday());
	}
	return flag;
}