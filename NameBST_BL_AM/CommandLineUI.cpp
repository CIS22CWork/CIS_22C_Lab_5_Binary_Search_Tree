/*
Branden Lee and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#define LAB5 true
#define FIND_TEST false
#define OTHER_TEST false

#include "commandLineUI.h"

using namespace std;

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
		firstLastNameBST->visitLogPostorder (CommandLineUI::visit, firstLastNameLog);
		birthdayBST->visitLogBreadthFirst (CommandLineUI::visit, birthdayLog);
		// prompt for output files
#if LAB5
		std::string firstLastNamePath, birthdayPath;
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
#endif
#if FIND_TEST
		std::string NameSearchStr;
		List<NodeMain*> *resultList = new List<NodeMain*> ();
		int operations;
		cout << "Enter the name to search: " << endl;
		getline (cin, NameSearchStr);
		//bool flag1 = firstLastNameBST->find (NameSearchStr, resultList, CommandLineUI::nameAccess);
		// find and get efficiency
		bool flag1 = firstLastNameBST->find (NameSearchStr, resultList, CommandLineUI::nameAccess, operations);
		if (flag1)
		{
			// success!
			cout << "Found \"" << NameSearchStr << "\" in the tree!" << endl
				<< "Operations: " << operations << " resultList:" << endl << resultList;

		}
		else
		{
			if (!flag1) cout << "Did not find \"" << NameSearchStr << "\" in the tree!" << endl
				<< "Operations: " << operations << endl;
		}
#endif
#if OTHER_TEST
		std::string NameSearchStr;
		List<NodeMain*> *resultList = new List<NodeMain*> ();
		firstLastNameBST->MaxPathNodes (resultList);
		cout << "resultList:" << endl << resultList;
		firstLastNameBST->add (new NodeMain ("James", "Cooper", "2016-01-05"), CommandLineUI::nameAccess);
		firstLastNameBST->remove ("James Cooper", CommandLineUI::nameAccess);
		//firstLastNameBST->remove ("Kimberly Henley", CommandLineUI::nameAccess);
#endif
	}
	else
	{
		cout << "Error: input file \"" << inputPath << "\" not found!" << endl;
	}
}

std::string CommandLineUI::visit (NodeMain* nodePtr)
{
	// string stream would also work for non-string data
	std::stringstream ss;
	ss << nodePtr->getName () << " " << nodePtr->getBirthday () << std::endl;
	return ss.str ();
}

std::string CommandLineUI::nameAccess (NodeMain* nodePtr)
{
	std::stringstream ss;
	ss << nodePtr->getName ();
	return ss.str ();
}

std::string CommandLineUI::birthdayAccess (NodeMain* nodePtr)
{
	std::stringstream ss;
	ss << nodePtr->getBirthday ();
	return ss.str ();
}

//******************************************************
// operator<<        
//******************************************************
template <class T>
std::ostream& operator<< (std::ostream &foo, List<T> *ListPtr)
{
	int n = ListPtr->size ();
	for (int i = 0; i < n; i++)
	{
		foo << (*ListPtr)[i] << endl;
	}
	return foo;
}

std::ostream& operator<< (std::ostream &foo, NodeMain *NodePtr)
{
	foo << NodePtr->getName () << " " << NodePtr->getBirthday ();
	return foo;
}