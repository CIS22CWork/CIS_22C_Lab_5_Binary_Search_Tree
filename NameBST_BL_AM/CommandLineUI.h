#ifndef COMMAND_LINE_UI_H
#define COMMAND_LINE_UI_H

#include <iostream>
#include <sstream>
#include <limits>
#include "FileIO.h"
#include "List.h"
#include "NodeMain.h"
#include "BST.h"
#include "SupportBST.h"

class CommandLineUI
{
private:
public:
	CommandLineUI ();
	static void enterLoop ();
};

#endif