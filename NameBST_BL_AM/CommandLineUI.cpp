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
	std::string inputPath;
	cout << "Enter the path for input file: " << endl;
	getline (cin, inputPath);
	bool flag0 = FileIO::fileToList (inputPath, mainList);
	if (flag0)
	{
		SupportBST::nameInsert (mainList, firstLastNameBST);
		SupportBST::birthdayInsert (mainList, birthdayBST);
		std::string firstLastNameLog = "";
		std::string birthdayLog = "";
		std::string firstLastNamePath, birthdayPath;
		firstLastNameBST->visitLogPostorder (CommandLineUI::visit, firstLastNameLog);
		birthdayBST->visitLogPostorder (CommandLineUI::visit, birthdayLog);
		cout << "Enter the path for the First and Last Name output file: " << endl;
		getline (cin, firstLastNamePath);
		cout << "Enter the path for the Birthday output file: " << endl;
		getline (cin, birthdayPath);
		bool flag1 = FileIO::strToFile (firstLastNameLog, firstLastNamePath);
		bool flag2 = FileIO::strToFile (birthdayLog, birthdayPath);
		if (flag1 && flag2)
		{
			cout << "Output files saved successfully to: " << endl
				<< firstLastNamePath << endl << birthdayPath << endl;
		}
		else
		{
			if (!flag1) cout << "Error: output file \"" << firstLastNamePath << "\" not found!" << endl;
			if (!flag2) cout << "Error: output file \"" << birthdayPath << "\" not found!" << endl;
		}
	}
	else
	{
		cout << "Error: input file \"" << inputPath << "\" not found!" << endl;
	}
}

//******************************************************
// operator<<        
//******************************************************


std::string CommandLineUI::visit (TreeNode<std::string>* node)
{
	return node->getValue () + "\n";
}