/*
Branden Lee and Alex Morfin
CIS 22C
Fall 2017
Lab 5

Used Microsoft Visual Studio 2017
Windows SDK Version: 10.0.16299.0
USE DOXYGEN COMPLIANT DOCUMENTATION
*/
#ifndef BST_H
#define BST_H

#include <iostream>
#include <sstream>

/**
@class TreeNode
Implement your BST as a link-based ADT - you may be able to reuse your Node classes from Labs 2 and 2b.
@param T The search tree data type
@param N The data node containing related data including data of type T
*/
template <class T, class N>
class TreeNode
{
private:
	N* value;
	TreeNode<T, N>* left;
	TreeNode<T, N>* right;
public:
	TreeNode ();
	TreeNode (N* val);
	TreeNode (N* val, TreeNode<T, N> left, TreeNode<T, N> right);
	~TreeNode ();
	N* getValue ();
	TreeNode<T, N>* getLeft ();
	TreeNode<T, N>* getRight ();
	void addLeft (TreeNode<T, N>* node);
	void addRight (TreeNode<T, N>* node);
	void addValue (N*);
};

/**
@class BST
constructor example:\n
BST<std::string, MyDataNode> *nameBST = new BST<std::string, MyDataNode> ();
@param T The search tree data type
@param N The data node containing related data including data of type T

*/

template <class T, class N>
class BST
{

private:
	TreeNode<T, N> *root;
	void addHelper (TreeNode<T, N> *root, NodeMain* val, T (*access)(N*));
	void visitLogPostorderHelper (TreeNode<T, N> *root, std::string (*visit)(N*), std::string &log);
	void visitLogInorderHelper (TreeNode<T, N> *root, std::string (*visit)(N*), std::string &log);
	void visitLogPreorderHelper (TreeNode<T, N> *root, std::string (*visit)(N*), std::string &log);
	void visitLogLevelHelper (TreeNode<T, N> *root, int level, std::string (*visit)(N*), std::string &log);
	int nodesCountHelper (TreeNode<T, N> *root);
	int heightHelper (TreeNode<T, N> *root);
	void printMaxPathHelper (TreeNode<T, N> *root);
	bool deleteValueHelper (TreeNode<T, N>* parent, TreeNode<T, N>* current, T value, T (*access)(N*));

public:
	BST ();
	BST (List<N*>* list, T (*access)(N* node));
	~BST ();

	/** adds data node N to the tree
	@pre None
	@post places data node N into the tree
	@param val the data node
	@param access the data node accessor method
	@return None */
	void add (N* val, T (*access)(N*));

	/** accesses data using a post-order traversal mechanism
	takes a visit method and logs it to a string
	@pre root node exists
	@post log filled with visits
	@param visit the data node accessor method
	@param log the string to append with visit data
	@return None */
	void visitLogPostorder (std::string (*visit)(N*), std::string &log);

	/** accesses data using a in-order traversal mechanism
	takes a visit method and logs it to a string
	@pre root node exists
	@post log filled with visits
	@param visit the data node accessor method
	@param log the string to append with visit data
	@return None */
	void visitLogInorder (std::string (*visit)(N*), std::string &log);

	/** accesses data using a pre-order traversal mechanism
	takes a visit method and logs it to a string
	@pre root node exists
	@post log filled with visits
	@param visit the data node accessor method
	@param log the string to append with visit data
	@return None */
	void visitLogPreorder (std::string (*visit)(N*), std::string &log);

	/** accesses data using a breadth-first traversal mechanism
	or level-order traversal
	takes a visit method and logs it to a string
	@pre root node exists
	@post log filled with visits
	@param visit the data node accessor method
	@param log the string to append with visit data
	@return None */
	void visitLogBreadthFirst (std::string (*visit)(N*), std::string &log);

	/** returns the nodes in the tree
	@pre root node exists
	@post None
	@return number of nodes in tree */
	int nodesCount ();

	/** returns the max height of the tree
	@pre root node exists
	@post None
	@return height of longest branch */
	int height ();

	/** prints the longest branch
	@pre root node exists
	@post prints branch to standard out
	@return None */
	void printMaxPath ();

	/** deletes the matching data node attribute
	@pre root node exists
	@post node removed from tree
	@param value the data node attribute of type T
	@param access the data node accessor method
	@return true on success, false on failure or not found */
	bool deleteValue (T value, T (*access)(N*));

	/** inserts a list into the BST
	@pre list is not empty
	@post list nodes added to BST
	@param list the list of data nodes
	@param access the data node accessor method
	@return true on success, false on failure or not found */
	bool insert (List<N*>* list, T (*access)(N* node));
};

//******************************************************
// TreeNode class implementation    
//******************************************************

template <class T, class N>
TreeNode<T, N>::TreeNode ()
{
}

template <class T, class N>
TreeNode<T, N>::TreeNode (N* val)
{
	value = val;
}

template <class T, class N>
TreeNode<T, N>::TreeNode (N* val, TreeNode<T, N> leftNode, TreeNode<T, N> rightNode)
{
	value = val;
	left = leftNode;
	right = rightNode;
}

template <class T, class N>
TreeNode<T, N>::~TreeNode ()
{
}

template <class T, class N>
N* TreeNode<T, N>::getValue ()
{
	return value;
}

template <class T, class N>
TreeNode<T, N>* TreeNode<T, N>::getLeft ()
{
	return left;
}

template <class T, class N>
TreeNode<T, N>* TreeNode<T, N>::getRight ()
{
	return right;
}
template <class T, class N>
void TreeNode<T, N>::addLeft (TreeNode<T, N>* node)
{
	left = node;
}
template <class T, class N>
void TreeNode<T, N>::addRight (TreeNode<T, N>* node)
{
	right = node;
}

template <class T, class N>
void TreeNode<T, N>::addValue (N* val)
{
	value = val;
}

//******************************************************
// BST class implementation    
// PRIVATE METHODS
//******************************************************

template <class T, class N>
void BST<T, N>::addHelper (TreeNode<T, N> *root, NodeMain* val, T (*access)(N*))
{
	if ((*access)(root->getValue ()) > (*access)(val))
	{
		if (!root->getLeft ()) root->addLeft (new TreeNode<T, N> (val));
		else addHelper (root->getLeft (), val, access);
	}
	else
	{
		if (!root->getRight ()) root->addRight (new TreeNode<T, N> (val));
		else addHelper (root->getRight (), val, access);
	}
}
template <class T, class N>
void BST<T, N>::visitLogPostorderHelper (TreeNode<T, N> *root, std::string (*visit)(N*), std::string &log)
{
	if (!root) return;
	visitLogPostorderHelper (root->getLeft (), visit, log);
	visitLogPostorderHelper (root->getRight (), visit, log);
	// call custom visit method and append output to log
	log += (*visit)(root->getValue ());
}

template <class T, class N>
void BST<T, N>::visitLogInorderHelper (TreeNode<T, N> *root, std::string (*visit)(N*), std::string &log)
{
	if (!root) return;
	visitLogInorderHelper (root->getLeft (), visit, log);
	// call custom visit method and append output to log
	log += (*visit)(root->getValue ());
	visitLogInorderHelper (root->getRight (), visit, log);
}

template <class T, class N>
void BST<T, N>::visitLogPreorderHelper (TreeNode<T, N> *root, std::string (*visit)(N*), std::string &log)
{
	if (!root) return;
	// call custom visit method and append output to log
	log += (*visit)(root->getValue ());
	visitLogPreorderHelper (root->getLeft (), visit, log);
	visitLogPreorderHelper (root->getRight (), visit, log);
}

template <class T, class N>
void BST<T, N>::visitLogLevelHelper (TreeNode<T, N> *root, int level, std::string (*visit)(N*), std::string &log)
{
	std::stringstream ss;
	if (!root)
		return;
	if (level == 1)
	{
		ss << (*visit)(root->getValue ());
		log += ss.str ();
	}
	else if (level > 1)
	{
		visitLogLevelHelper (root->getLeft (), level - 1, visit, log);
		visitLogLevelHelper (root->getRight (), level - 1, visit, log);
	}
}

template <class T, class N>
int BST<T, N>::nodesCountHelper (TreeNode<T, N> *root)
{
	if (!root) return 0;
	else return 1 + nodesCountHelper (root->getLeft ()) + nodesCountHelper (root->getRight ());
}
template <class T, class N>
int BST<T, N>::heightHelper (TreeNode<T, N> *root)
{
	if (!root) return 0;
	// removed max() method to remove <algorithm> dependency
	else return 1 + ((heightHelper (root->getLeft ()) > heightHelper (root->getRight ())) ? heightHelper (root->getLeft ()) : heightHelper (root->getRight ()));
}

template <class T, class N>
void BST<T, N>::printMaxPathHelper (TreeNode<T, N> *root)
{
	if (!root) return;
	cout << root->getValue () << ' ';
	if (heightHelper (root->getLeft ()) > heightHelper (root->getRight ()))
	{
		printMaxPathHelper (root->getLeft ());
	}
	else
	{
		printMaxPathHelper (root->getRight ());
	}
}
template <class T, class N>
bool BST<T, N>::deleteValueHelper (TreeNode<T, N>* parent, TreeNode<T, N>* current, T value, T (*access)(N*))
{
	if (!current) return false;
	if ((*access)(current->getValue ()) == value)
	{
		if (current->getLeft () == NULL || current->getRight () == NULL)
		{
			TreeNode<T, N>* temp = current->getLeft ();
			if (current->getRight ()) temp = current->getRight ();
			if (parent)
			{
				if (parent->getLeft () == current)
				{
					parent->addLeft (temp);
				}
				else
				{
					parent->addRight (temp);
				}
			}
			else
			{
				this->root = temp;
			}
		}
		else
		{
			TreeNode<T, N>* validSubs = current->getRight ();
			while (validSubs->getLeft ())
			{
				validSubs = validSubs->getLeft ();
			}
			T temp = current->getValue ();
			current->addValue (validSubs->getValue ());
			validSubs->addValue (temp);
			return deleteValueHelper (current, current->getRight (), temp, access);
		}
		delete current;
		return true;
	}
	return deleteValueHelper (current, current->getLeft (), value, access) ||
		deleteValueHelper (current, current->getRight (), value, access);
}

//******************************************************
// BST class implementation 
// PUBLIC METHODS
//******************************************************

template <class T, class N>
BST<T, N>::BST ()
{
}

template <class T, class N>
BST<T, N>::BST (List<N*>* list, T (*access)(N* node))
{
	insert (list, access);
}

template <class T, class N>
BST<T, N>::~BST ()
{
}

template <class T, class N>
void BST<T, N>::add (N* val, T (*access)(N*))
{
	if (root) this->addHelper (root, val, access);
	else root = new TreeNode<T, N> (val);
}

template <class T, class N>
void BST<T, N>::visitLogPostorder (std::string (*visit)(N*), std::string &log)
{
	visitLogPostorderHelper (this->root, visit, log);
}

template <class T, class N>
void BST<T, N>::visitLogInorder (std::string (*visit)(N*), std::string &log)
{
	visitLogInorderHelper (this->root, visit, log);
}

template <class T, class N>
void BST<T, N>::visitLogPreorder (std::string (*visit)(N*), std::string &log)
{
	visitLogPreorderHelper (this->root, visit, log);
}

template <class T, class N>
void BST<T, N>::visitLogBreadthFirst (std::string (*visit)(N*), std::string &log)
{
	int h = heightHelper (this->root);
	int i;
	for (i = 1; i <= h; i++)
		visitLogLevelHelper (this->root, i, visit, log);
}

template <class T, class N>
int BST<T, N>::nodesCount ()
{
	return nodesCountHelper (root);
}
template <class T, class N>
int BST<T, N>::height ()
{
	return heightHelper (this->root);
}
template <class T, class N>
void BST<T, N>::printMaxPath ()
{
	printMaxPathHelper (this->root);
}
template <class T, class N>
bool BST<T, N>::deleteValue (T value, T (*access)(N*))
{
	return this->deleteValueHelper (NULL, this->root, value, access);
}

template <class T, class N>
bool BST<T, N>::insert (List<N*>* list, T (*access)(N* node))
{
	bool flag = false;
	int n = list->size ();
	for (int i = 0; i < n; i++)
	{
		add ((*list)[i], access);
	}
	return flag;
}
#endif