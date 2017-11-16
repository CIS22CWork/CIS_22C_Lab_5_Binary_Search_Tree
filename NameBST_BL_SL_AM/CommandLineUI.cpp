/*
Branden Lee, Stephen Lee, and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017

CommandLineUI class
contains the presentational and interactive interface in the command line for the user.
KEEP ALL COUT<< AND CIN>> HERE
*/

#include "commandLineUI.h"

using namespace std;

CommandLineUI::CommandLineUI ()
{
}

//******************************************************
// CommandLineUI::enterLoop  
//      
// the main menu UI loop
// Pre: None
// Post: None
// Purpose: Command Line to interact with the user
//******************************************************
void CommandLineUI::enterLoop ()
{
	cout << "Welcome to the name BST! " << endl;
	BST<int> *bst = new BST<int> ();
	bst->add (11);
	bst->add (1);
	bst->add (6);
	bst->add (-1);
	bst->add (-10);
	bst->add (100);
	bst->print ();
	cout << endl;
	cout << "Nodes count: " << bst->nodesCount ();
	cout << endl;
	cout << "Height: " << bst->height ();
	cout << endl;
	cout << "Max path: ";
	bst->printMaxPath ();
	cout << endl;
	bst->deleteValue (11);
	cout << "11 removed: ";
	bst->print ();
	cout << endl;
	cout << "1 removed: ";
	bst->deleteValue (1);
	bst->print ();
	cout << endl;
	cout << "-1 removed: ";
	bst->deleteValue (-1);
	bst->print ();
	cout << endl;
	cout << "6 removed: ";
	bst->deleteValue (6);
	bst->print ();
	cout << endl;
	cout << "-10 removed: ";
	bst->deleteValue (-10);
	bst->print ();
	cout << endl;
	cout << "100 removed: ";
	bst->deleteValue (100);
	bst->print ();
	cout << endl;
}

//******************************************************
// operator<<        
//******************************************************
