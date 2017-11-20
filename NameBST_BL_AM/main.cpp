/*
Branden Lee and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017

main
loads name data from input.txt and writes
everyone's name to names.txt and birthdays 
to birthdays.txt
structures data internally as a binary searh tree
with linked lists
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