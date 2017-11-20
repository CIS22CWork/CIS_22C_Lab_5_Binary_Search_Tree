/*
Branden Lee and Alex Morfin
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
	BST<string> *firstLastNameBST = new BST<string> ();
	BST<string> *birthdayBST = new BST<string> ();
	List<NodeMain*> *mainList = new List<NodeMain*> ();
	FileIO::fileToList ("input.txt", mainList);
	SupportBST::nameInsert (mainList, firstLastNameBST);
	SupportBST::birthdayInsert (mainList, birthdayBST);

	/*firstLastNameBST->add ("Kimberly Henley");
	firstLastNameBST->add ("Claudette Leflore");
	firstLastNameBST->add ("Richard Boyd");
	firstLastNameBST->add ("Kathleen Sears");
	firstLastNameBST->add ("Penny Dyke");
	firstLastNameBST->add ("David Davis");
	firstLastNameBST->print ();
	cout << endl;
	cout << "Nodes count: " << firstLastNameBST->nodesCount ();
	cout << endl;
	cout << "Height: " << firstLastNameBST->height ();
	cout << endl;
	cout << "Max path: ";
	firstLastNameBST->printMaxPath ();
	cout << endl;
	firstLastNameBST->deleteValue ("Kimberly Henley");
	cout << "Kimberly Henley removed: ";*/
	firstLastNameBST->print ();
	birthdayBST->print ();
	/*cout << endl;
	cout << "Claudette Leflore removed: ";
	firstLastNameBST->deleteValue ("Claudette Leflore");
	firstLastNameBST->print ();
	cout << endl;
	cout << "Richard Boyd removed: ";
	firstLastNameBST->deleteValue ("Richard Boyd");
	firstLastNameBST->print ();
	cout << endl;
	cout << "Kathleen Sears removed: ";
	firstLastNameBST->deleteValue ("Kathleen Sears");
	firstLastNameBST->print ();
	cout << endl;
	cout << "Penny Dyke removed: ";
	firstLastNameBST->deleteValue ("Penny Dyke");
	firstLastNameBST->print ();
	cout << endl;
	cout << "David Davis removed: ";
	firstLastNameBST->deleteValue ("David Davis");
	firstLastNameBST->print ();
	cout << endl;*/
}

//******************************************************
// operator<<        
//******************************************************
