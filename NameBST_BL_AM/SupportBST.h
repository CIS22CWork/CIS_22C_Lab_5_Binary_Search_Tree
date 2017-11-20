#ifndef SUPPORT_BST_H
#define SUPPORT_BST_H

#include <string>
#include "List.h"
#include "NodeMain.h"
#include "BST.h"

class SupportBST
{
public:
	static bool nameInsert (List<NodeMain*>* list, BST<std::string>* BST);
	static bool birthdayInsert (List<NodeMain*>* list, BST<std::string>* BST);
};
#endif