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

/** menu entry point for the program
@pre None
@post menu
@return None */
void CommandLineUI::enterLoop ()
{
	// welcome and setup
	cout << "Welcome to the name BST! " << endl;
	BST<std::string, NodeMain> *firstLastNameBST = new BST<std::string, NodeMain> ();
	BST<std::string, NodeMain> *birthdayBST = new BST<std::string, NodeMain> ();
	List<NodeMain*> *mainList = new List<NodeMain*> ();
	std::string inputPath;
	// prompt for input file and parse as BST
	cout << "Enter the path for input file: " << endl;
	getline (cin, inputPath);
	bool flag0 = FileIO::fileToList (inputPath, mainList);
	if (flag0)
	{
		firstLastNameBST->insert (mainList, CommandLineUI::nameAccess);
		birthdayBST->insert (mainList, CommandLineUI::birthdayAccess);
		// log each BST traversal
		std::string firstLastNameLog = "";
		std::string birthdayLog = "";
		std::string firstLastNamePath, birthdayPath;
		firstLastNameBST->visitLogPostorder (CommandLineUI::visit, firstLastNameLog);
		birthdayBST->visitLogBreadthFirst (CommandLineUI::visit, birthdayLog);
		// prompt for output files
		cout << "Enter the path for the First and Last Name output file: " << endl;
		getline (cin, firstLastNamePath);
		cout << "Enter the path for the Birthday output file: " << endl;
		getline (cin, birthdayPath);
		bool flag1 = FileIO::strToFile (firstLastNameLog, firstLastNamePath);
		bool flag2 = FileIO::strToFile (birthdayLog, birthdayPath);
		if (flag1 && flag2)
		{
			// success!
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

std::string CommandLineUI::visit (NodeMain* node)
{
	std::stringstream ss;
	ss << node->getName () << " " << node->getBirthday () << std::endl;
	return ss.str ();
}

std::string CommandLineUI::nameAccess (NodeMain* node)
{
	std::stringstream ss;
	ss << node->getName ();
	return ss.str ();
}

std::string CommandLineUI::birthdayAccess (NodeMain* node)
{
	std::stringstream ss;
	ss << node->getBirthday ();
	return ss.str ();
}

//******************************************************
// operator<<        
//******************************************************
template <class T>
std::ostream& operator<< (std::ostream &foo, List<T> *ListPtr)
{

}