#ifndef COMMAND_LINE_UI_H
#define COMMAND_LINE_UI_H

#include <iostream>
#include <sstream>
#include <limits>
#include "FileIO.h"
#include "List.h"
#include "NodeMain.h"
#include "BST.h"

class CommandLineUI
{
private:
public:
	static void enterLoop ();
	static std::string CommandLineUI::visit (NodeMain* node);
	static std::string CommandLineUI::nameAccess (NodeMain* node);
	static std::string CommandLineUI::birthdayAccess (NodeMain* node);
};

#endif