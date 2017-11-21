/*
Branden Lee and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/

/**
@mainpage Binary Search Tree Example
Prompts user for a file with names and birthdays delimitted by newlines.
For example:\n\n
Kimberly Henley 1971-06-12\n
Claudette Leflore 1959-07-12\n
Richard Boyd 1987-07-10\n\n
Uses a two different binary search trees for names and birthdays. 
After constructing the BST, the user is promted for the output file
for 
- listing of everyone by name using a post-order traversal mechanism.
- listing of everyone by birthday using a breadth-first traversal mechanism.
*/
#include <iostream>
#include "commandLineUI.h"

using namespace std;

int main ()
{
	CommandLineUI::enterLoop ();
	system ("pause");
	return 0;
}